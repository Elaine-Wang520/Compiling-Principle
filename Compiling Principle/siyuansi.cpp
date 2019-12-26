#include <iostream> 
#include <vector> 
#include <set> 
#include<stack> 
#include <iomanip> 
#include<string.h> 
#include <fstream> 
#include <string> 
#include<stdio.h> 
#include<sstream> 
#include <cassert>
using namespace std; 
char token[30];
int No,row=1,colum=1,Ncolum,Nrow;//���к�


//���ű�
enum{Int, Float, Char, Bool};
#define SIZE 211
#define SHIFT 4
int attendce=0;
static int hash(string key)
{ 
	int temp = 0;
	int i = 0;
	while (key[i]!='\0')
	{ 
		temp=((temp<<SHIFT)+key[i])%SIZE;
		++i;
	}
  return temp;
}
//����
typedef class List
{
	public:
	long memloc; //���
	string name; //������
    string type; //��������(1:int,2:char)
    string value; //������ֵ
    List * next;
} * BucketList;
static BucketList ListHash[SIZE];
void List_insert(long loc,string name, string type, string value)
{ 
	int h = hash(name);
	List *l;
	l = new List;
	l->memloc = loc;
	l->name = name;
	l->type = type;
	l->value = value;
	l->next = ListHash[h];
	ListHash[h] = l;
}
//�����Ĺ�ϣ���޸�

void List_delete(string name)
{
	int h = hash(name);
	ListHash[h] = NULL;
}
//�����Ĺ�ϣ�����
long List_find(string name)
{
	int h = hash(name);
	List *l;
	l = ListHash[h];
	return l->memloc;
}
//�������ű�Ĵ�ӡ
void printList()
{
	int i;
	cout << "�������ű�" << endl;
	cout << "���\t������\t����\tֵ" << endl;
	cout << "---------------------------------------------------" << endl;
	for(i=0; i<SIZE; i++)
	{
		if(ListHash[i] != NULL)
		{
			BucketList l = ListHash[i];
			while(l != NULL)
			{
				cout << l->memloc << setw(10) << l->name << setw(10) << l->type << setw(10) << l->value<<endl;
				l = l->next;
			}
		}
	}
}



 
//�ж��Ƿ�����ĸ 
bool isAlpha(char a) 
{ 
    if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||a=='_') 
        return true; 
    else 
		return false; 
} 
 //�ж��Ƿ��Ǳ�ʶ�� 
bool isAlnum(char a) 
{ 
    if((a>='0'&&a<='9')||(a>='a'&&a<='z')||(a>='A'&&a<='Z')||a=='_') 
        return true; 
    else 
		return false; 
} 
 
bool isDigit(char a) //�ж��Ƿ������� 
{ 
    if(a>='0'&&a<='9') 
        return true; 
    else 
		return false; 
} 
char name1[20]; 
int lookup(char a[]) // ��ѯ�ؼ��� 
{ 
   char *b[20]= {"char","int","float","break","const","return","void","continue","do","while","if","else","for"};
    int i;
	for(i=0;i<sizeof(a);i++) 
    { 
        if(a[i]>='A'&&a[i]<='Z') 
            a[i]=a[i]+32; 
    }
    strcpy(name1,a);
    for(i=0; i<13; i++) 
    { 
        if(strcmp(a,b[i])==0) 
        { 
            return i; 
        } 
    } 
    return -1; 
} 
int scanner(FILE *infile) //ɨ���� 
{ 
    char c; 
    c = fgetc(infile); //��ȡ�ַ� 
    Ncolum = colum; //��������ĸ�к� 
    Nrow=row;       //��������ĸ�к� 
    if(c=='\n') //���� 
    { 
        row++; 
        colum=1; 
    } 
    else 
		colum++; 
    int i=1; 
    memset(token,0,sizeof(token)); //��token���ڴ渳ֵ 
    //ע�� 
    if(c=='/') 
    { 
        bool flag = false; 
        char s[1024]; 
        c=fgetc(infile); 
        if(c=='\n') 
        { 
            row++; 
            colum=1; 
        } 
        else colum++; 
        switch(c) 
        { 
            //����ʽע�� 
        case '/': 
            fgets(s,1024,infile); //s:�ַ���ָ�룬ָ��洢�������ݵĻ������ĵ�ַ��1024: �����ж���1023-1���ַ� infile �� ָ���ȡ������
            fseek(infile,-1,1); //�ļ�ָ�룬����ƫ�ƣ��ƶ�1 
            colum--; 
            break; 
            /*����ʽע��*/ 
        case '*': 
            c=fgetc(infile); 
            if(c=='\n') 
            { 
                row++; 
                colum=1; 
            } 
            else 
				colum++; 
            while(c!=EOF) 
            { 
                c=fgetc(infile); 
                if(c=='\n') 
                { 
                    row++; 
                    colum=1; 
                } 
                else colum++; 
                if(flag==true&&c=='/') 
                { 
 
                    flag = false; 
                    break; //�ҵ���/*�� 
                } 
                else 
				flag=false; //ȷ��*�����/ 
                if(c=='*') 
                { 
                    flag=true; 
                } 
            } 
            break; 
        default : 
            fseek(infile,-1,1); 
            colum--; 
            token[0]='/'; 
            return 7;   //����ע�ͣ�Ϊ��/�� 
        } 
        return -1; 
 
    } 
    
// ��ʶ�� 
    else  if(isAlpha(c)) 
    { 
        token[0]=c; 
        c=fgetc(infile); 
        if(c=='\n') 
        { 
            row++; 
            colum=1; 
        } 
        else 
			colum++; 
        while(isAlnum(c)) 
        { 
            token[i++]=c; 
            c=fgetc(infile); //��һ���ַ� 
            if(c=='\n') //���� 
            { 
                row++; 
                colum=1;  
            } 
            else //��һ�ַ� 
				colum++; 
        } 
        token[i]='\0'; 
        fseek(infile,-1,1); //����һλ 
        colum--; 
        if(i>20) 
            return 0; 
        if(lookup(token)!=-1) 
        { 
            No=lookup(token)+1; 
            return 1; 
        } 
        else return 2; 
    } 
    else 
        //�޷������� 
        if(isDigit(c)) 
        { 
            token[0]=c; 
            c=fgetc(infile); 
            if(c=='\n') 
            { 
                row++; 
                colum=1; 
            } 
            else colum++; 
            while(isDigit(c)) 
            { 
                token[i++]=c; 
                c=fgetc(infile); 
                if(c=='\n') 
                { 
                    row++; 
                    colum=1; 
                } 
                else colum++; 
            } 
            token[i]='\0'; 
            fseek(infile,-1,1); 
            colum--; 
            return 3; 
        } 
	// ����� 
        else if(c=='+') 
        { 
            token[0]=c; 
            token[1]='\0'; 
            return 4; 
        }
		else if(c=='-') 
        { 
            token[0]=c; 
            token[1]='\0'; 
            return 5; 
        } 
 
        else if(c=='*') 
        { 
            token[0]=c; 
            token[1]='\0'; 
            return 6; 
        } 
 
        else if(c=='/') 
        { 
            token[0]=c; 
            token[1]='\0'; 
            return 7; 
        }
		else if(c=='=') 
        { 
            token[0]='='; 
            c=fgetc(infile); 
            if(c=='\n') 
            { 
                row++; 
                colum=1; 
            } 
            else 
				colum++; 
            if(c=='=') // �������==�� 
            { 
                token[1]='='; 
                token[2]='\0'; 
                return 14; 
            }
			else 
            { 
                fseek(infile,-1,1); 
                colum--; 
                token[1]='\0'; 
                return 8; 
            } 
        } 
		else if(c=='<') 
        { 
            token[0]='<'; 
            c=fgetc(infile); 
            if(c=='\n') 
            { 
                row++; 
                colum=1; 
            } 
            else 
			colum++; 
			if(c=='=') //�������<=�� 
            { 
                token[1]='='; 
                token[2]='\0'; 
                return 11; 
            } 
        	else 
            { 
                fseek(infile,-1,1); 
                colum--; 
                token[1]='\0'; 
                return 9; 
            } 
        }
        else if(c=='!')
        {
			token[0]='!';
            c=fgetc(infile); 
            if(c=='\n') 
            { 
                row++; 
                colum=1; 
            } 
            else 
			colum++; 
			if(c=='=') //�������!=�� 
            { 
                token[1]='='; 
                token[2]='\0'; 
                return 22; 
            } 
			 else 
            { 
                fseek(infile,-1,1); 
                colum--; 
            return 21; 
			}	
		}
		
		else if(c=='|') 
        { 
            token[0]='|'; 
            token[1]='\0'; 
            c=fgetc(infile); 
            if(c=='\n') 
            { 
                row++; 
                colum=1; 
            } 
            else colum++; 
            if(c=='|') //����� ��||�� 
            { 
                token[1]='|'; 
                token[2]='\0'; 
                return 24; 
            } 
            else 
            { 
                fseek(infile,-1,1); 
                colum--; 
            } 
            return 23; 
        } 
		else if(c=='&') 
        { 
            token[0]='&'; 
            token[1]='\0'; 
            c=fgetc(infile); 
            if(c=='\n') 
            { 
                row++; 
                colum=26; 
            } 
            else colum++; 
            if(c=='&') //����� ��&&�� 
            { 
                token[1]='&'; 
                token[2]='\0'; 
                return 24; 
            } 
            else 
            { 
                fseek(infile,-1,1); 
                colum--; 
            } 
            return 25; 
        } 
		else if(c=='>') 
        { 
            token[0]='>'; 
            token[1]='\0'; 
            c=fgetc(infile); 
            if(c=='\n') 
            { 
                row++; 
                colum=1; 
            } 
            else colum++; 
            if(c=='=') //����� ��>=�� 
            { 
                token[1]='='; 
                token[2]='\0'; 
                return 12; 
            } 
            else 
            { 
                fseek(infile,-1,1); 
                colum--; 
            } 
            return 10; 
        } 
	//	��� 
        else if(c=='(') 
        { 
            token[0]=c; 
            token[1]='\0'; 
            return 15; 
        } 
        else if(c==')') 
        { 
            token[0]=c; 
            token[1]='\0'; 
            return 16; 
        } 
        else if(c==',') 
        { 
            token[0]=c; 
            token[1]='\0'; 
            return 17; 
        } 
        else if(c==';') 
        { 
            token[0]=c; 
            token[1]='\0'; 
            return 18; 
        } 
        else if(c=='{') 
        { 
            token[0]=c; 
            token[1]='\0'; 
            return 19; 
        } 
        else if(c=='}') 
        { 
            token[0]=c; 
            token[1]='\0'; 
            return 20; 
        } 
        else if(c=='\n'||c==' ') 
        { 
            return -1; 
        } 
        else 
        { 
            token[0]=c; 
            return 0; 
        } 
} 


 
//�﷨������ (������Ԫʽ)

int NXQ=0; //��Ԫʽ��� 
int T=1; 
bool ana=false; //
bool Db=false; //
struct Gencode     //��Ԫʽ�� 
{ 
    string OP,arg1,arg2,result,arg3; 
} Q[10000]; 
 
struct Attr     //�����ķ�  
{ 
	public:
		string place;//��ַ 
		string type;//���� 
		string arg; //���� 
		int Start;//��ʼ 
		int End; //��β 
}; 
int DefN=0; //�ѱ������ʶ������ 
string Def[10000]; 

void AddDef(string a) //����Ѿ�������ı�ʾ�� 
{ 
    Def[DefN]=a; 
    DefN++; 
} 
 
bool isDef(string A) //�Ƿ񱻶��� 
{ 
    for(int i=0; i<DefN; i++) 
    { 
        if(Def[i]==A) 
            return true; 
    } 
    return false; 
} 
string itos(int int_temp) // ������תΪstring���� 
{ 
    string string_temp; 
    stringstream stream; 
    stream<<int_temp; 
    string_temp=stream.str(); 
    return string_temp; 
} 
 
Attr NewTemp() //������ʱ���� 
{ 
    Attr ans ={"T",""};
    ans.place = ans.place+itos(T); 
    T++; 
    return ans; 
} 
 
void Gen(string OP,string arg1,string arg2,string result) 
{ 
    Q[NXQ]={OP,arg1,arg2,result}; //����һ���м���� 
    NXQ++;  
} 


//��ʾ��Ԫʽ 
void show() 
{ 
    cout << "��Ԫʽ���£�"<<endl;
    for(int i=0; i<NXQ; i++) 
    {  
        cout << "("<<i+1<<")  ("<<Q[i].OP<<","<<Q[i].arg1<<","<<Q[i].arg2<<"," <<Q[i].result<<")"<<endl;
	} 
	 cout << "����չʾ"<<endl;
}
void LinkT(int start ,int End)  // ��Ԫʽ���б��Start-End����������ת��Ԫʽ��result������ 
{ 
    string s=itos(End+1); 
    for(int i=End-1; i>=start; i--) 
    { 
        if(Q[i].OP!="j")
        { 
            if(Q[i].result[0]!='T'&&Q[i].result=="0")
            {  	
                Q[i].result=s; 
                s=itos(i); 
            } 
        } 
    } 
    if(Db) 
        show(); 
} 
void LinkF(int start,int End) // ��Ԫʽ���б��Start-End����������ת��Ԫʽ��result������ 
{ 
    string s=itos(End+1); 
    for(int i=End-1; i>=start; i--) 
    { 
        if(Q[i].OP=="j")
        { 
            Q[i].result=s; 
        } 
    } 
    if(Db) 
        show(); 
} 
void BackPatchT(int start,int End) //��Ԫʽ���б��Start-End����������ת��Ԫʽresultδ��䲿��ȫ��ΪEnd+1 
{ 
    string s=itos(End+1); 
    for(int i=start;i<End; i++) 
    { 
        if(Q[i].OP!="j")
        { 
            if(Q[i].result[0]!='T'&&Q[i].result=="0")
            { 
                Q[i].result=s; 
            } 
        } 
    } 
    if(Db) 
        show(); 
} 
 void BackPatchF(int start,int End)// ��Ԫʽ���б��Start-End����������ת��Ԫʽresultδ��䲿��ȫ��ΪEnd+1 
{ 
    string s=itos(End+1); 
    for(int i=start; i<End; i++) 
    { 
        if(Q[i].OP=="j"&&Q[i].result=="0")
        { 
            Q[i].result=s; 
        } 
    } 
    if(Db) 
        show(); 
}

Gencode EmpQ= {"","",""};
Attr EmpA= {"",""};
string LEX; //�зֺõĵ��� 
string IDF; //��ʶ�� 
bool flag=false; 
int WRcount=0; //��¼����ĸ��� 
void getNext(FILE *IN) // ������һ���ַ� 
{ 
LABLE1: 
    int c; 
    if((c=fgetc(IN))!=EOF) 
    { 
        fseek(IN,-1,1); 
        int Num = scanner(IN); 
        LEX = token; 
        IDF=LEX; 
        if(ana) 
            cout << "����"<<LEX<<endl;
        if(Num>=-1&&Num<=40) 
        { 
            if(Num==-1) 
            { 
                goto LABLE1; 
            } 
            else if(Num==0) 
            { 
                if(LEX!=".")
                { 
           //         cout<<"("<<Nrow<<","<<Ncolum<<"���󣨲���ʶ����ַ�����"<<LEX<<endl;
           //         WRcount++; 
                    getNext(IN); 
                } 
            } 
            else if(Num==2) // ʶ�𵽱�ʶ�� 
            { 
                IDF=LEX; 
                LEX ="ID";
            } 
            else if(Num==3) // ʶ���޷������� 
            { 
                 IDF=LEX; 
				 LEX ="UNINT";
            }
        } 
    } 
    else 
    { 
        flag=true; 
        Gen("ret","","","0");//���� 
    } 
}
void Program(FILE*IN); 
void Program1(FILE*IN); 
void Block(FILE*IN); 
void SentenList(FILE*IN); 
void SentenList1(FILE*IN); 
void SentenList2(FILE*IN); 
Attr Senten(FILE*IN,Attr self); 
Attr IntSenten(FILE*IN,Attr self); 
Attr IntSenten1(FILE*IN,Attr self); 
Attr AssignSenten(FILE*IN,Attr self); 
Attr ConSenten(FILE*IN,Attr self); 
Attr ConSenten1(FILE*IN,Attr self); 
Attr WhileSenten(FILE*IN,Attr self); 
Attr DoWhileSenten(FILE*IN,Attr self);
Attr ForSenten(FILE*IN,Attr self); 
Attr ProSenten(FILE*IN,Attr self);
Attr ComSenten(FILE*IN,Attr self); 
Attr RelaExp(FILE*IN,Attr self); 
Attr Expr(FILE*IN,Attr self); 
Attr Expr1(FILE*IN,Attr self); 
Attr Term(FILE*IN,Attr self); 
Attr Term1(FILE*IN,Attr self); 
Attr Factor(FILE*IN,Attr self); 
Attr ConExp(FILE*IN,Attr self); 
Attr ConExp1(FILE*IN,Attr self); 
Attr RelaID(FILE*IN,Attr self); 


void Program(FILE*IN) 
{ 
	 if(LEX=="void")
	    { 
	        Block(IN); 
	        Program1(IN); 
	        return ; 
	    } 
} 
 void Program1(FILE*IN) 
{ 
    if(flag) 
    { 
        cout << "������ɣ�"<<endl;
        return ; 
    } 
  if(LEX=="void")
    { 
        Block(IN); 
        Program1(IN); 
        return ; 
    } 
    else 
    { 
        cout << "error program"<<endl;
        return ; 
    } 
} 
 void Block(FILE*IN) //�����﷨ 
{ 
    if(flag) 
    { 
        cout << "Over"<<endl;
        return ; 
    } 
	if(LEX=="void")
    { 
        getNext(IN); 
        if(LEX=="ID")
        { 
        	Gen("main","","","");
            getNext(IN); 		
            if(LEX=="(")
            { 
                getNext(IN); 
               if(LEX==")")
           		{ 
               	 	getNext(IN); 
                	if(LEX=="{")
                	{ 
	                    getNext(IN); 
	                    SentenList(IN); 
	              //      cout<<LEX<<endl;
	                    if(LEX=="}")
	                    { 
	                    	Gen("ret","","","0");
	                    	Gen("sys","","","");
	                    } 
                	}    
            	}
            } 
        } 
    } 
    else 
    { 
        cout << "error block"<<endl;
    } 
} 
void SentenList(FILE*IN) //�����б� ,�ҳ��������־��� 
{ 
   if(LEX=="ID"||LEX=="{"||LEX=="int"||LEX=="if"||LEX=="while"||LEX=="char"||LEX=="float"||LEX=="do"||LEX=="for")
    { 
        Senten(IN,EmpA); 
        SentenList1(IN); 
    } 
    else if(LEX=="}")
    { 
        return ; 
    } 
    else 
    { 
        cout << "error block"<<endl;
        return ; 
    } 
}
Attr Senten(FILE*IN,Attr self) 
{ 
    if(LEX=="ID")//����Ǳ�ʶ�� 
    { 
        AssignSenten(IN,self); 
        self.End=NXQ; 
        return self; 
    } 
    else if(LEX=="for")//����do while 
    {
    	ForSenten(IN,self);  
		self.End=NXQ; 
        return self; 
	} 
    else if(LEX=="if")//����if 
    { 
        ConSenten(IN,self); 
        self.End=NXQ; 
        return self; 
    } 
    else if(LEX=="{")
    { 
        ComSenten(IN,self); 
        self.End=NXQ; 
        return self; 
    } 
    else if(LEX=="while")//����while 
    { 
        WhileSenten(IN,self); 
        self.End=NXQ; 
        return self; 
    } 
    else if(LEX=="do")//����do while 
    {
    	DoWhileSenten(IN,self); 
		self.End=NXQ; 
        return self; 
	} 
 	else if(LEX=="int"||LEX=="char"||LEX=="float")
    { 
        IntSenten(IN,self); 
        self.End=NXQ; 
        return self; 
    } 
    else if(LEX=="else"||LEX=="}"||LEX==";")
    { 
        self.End=NXQ; 
        return EmpA; 
    } 
    else 
    { 
        cout << "error senten"<<endl;
        return EmpA; 
    } 
} 
 void SentenList1(FILE*IN) 
{ 
    if(LEX==";")
    { 
        getNext(IN); 
        Senten(IN,EmpA); 
        SentenList1(IN); 
    } 
    else if(LEX=="}"||LEX=="else")
    { 
        return ; 
    } 
    else if(LEX=="do")
    {
    	Senten(IN,EmpA);
    	getNext(IN); 
	}
	else if(LEX=="for")
	{
		Senten(IN,EmpA);
	}
    else 
    { 
        cout << "error sentenlist"<<endl;
        return ; 
    } 
} 
Attr IntSenten(FILE*IN,Attr self) //ȷ����ʶ�������� 
{ 
  if(LEX=="int"||LEX=="char"||LEX=="float")
    { 
        getNext(IN); 
        if(LEX=="ID")
        { 
            AddDef(IDF); //�����ʶ�� 
       //   getNext(IN); 
            self.place=IDF;  
        //   IntSenten1(IN,self); 
        	AssignSenten(IN,self);
            return self; 
        } 
    } 
    else 
    { 
        cout << "error IntSenten"<<endl;
        return EmpA; 
    } 
} 
 
/*Attr IntSenten1(FILE*IN,Attr self) //int a,b,c;���������ֵ 
{ 
    if(LEX==",")
    { 
        getNext(IN); 
        if(LEX=="ID")
        { 
            AddDef(IDF); 
            getNext(IN); 
            self.place=IDF; 
            IntSenten1(IN,self); 
            return self; 
        } 
    } 
    else if(LEX==";"||LEX=="else"||LEX=="}")
    { 
        return self; 
    } 
    else 
    { 
        cout << "error IntSenten1"<<endl;
    } 
} */

Attr AssignSenten(FILE*IN,Attr self) //��ֵ��� 
{ 
    if(LEX=="ID")
    { 
        if(!isDef(IDF)) 
        { 
            cout <<"("<<row<<","<<colum<<")"<<"����δ�������:"<<IDF<<endl;
            WRcount++; 
        } 
        string Mark=IDF; 
        getNext(IN); 
        if(LEX=="=")
        { 
            getNext(IN); 
            Attr s1=Expr(IN,EmpA); 
            Gen("=",s1.place,"",Mark);//�����������ʽ����Ԫʽ 
        //    List_insert(attendce,name1,"int",s1.place);
        	List_insert(attendce,Mark,"int",s1.place);
            attendce+=1;
            return EmpA; 
        } 
    } 
    else 
    { 
        cout << "error AssignSenten"<<endl;
        return EmpA; 
    } 
} 
 //�������ʽ����Ԫ���ʽ 
Attr Expr(FILE*IN,Attr self)
{ 
    if(LEX=="("||LEX=="ID"||LEX=="UNINT")//��*/��+- 
    { 
        Attr temp1=Term(IN,EmpA); 
        Attr temp2=Expr1(IN,temp1); 
        if(temp2.place=="")
        { 
            return temp1; 
        } 
        else 
			return temp2; 
    } 
    else 
    { 
        cout << "error Expr"<<endl;
        return EmpA; 
    } 
} 
 
Attr Expr1(FILE*IN,Attr self) //����-���� 
{ 
    if(LEX=="+"||LEX=="-")
    { 
        string Mark=LEX; 
        getNext(IN); 
        Attr temp1=Term(IN,EmpA); 
        Attr temp2=NewTemp(); 
        Gen(Mark,self.place,temp1.place,temp2.place); //������Ԫ���ʽ  
        Attr temp3=Expr1(IN,temp2); 
        if(temp3.place=="")
            return temp2; 
        else 
			return temp3; 
    } 
     else if(LEX==";"||LEX==")"||LEX=="<"||LEX=="do"||LEX=="<="||LEX=="!="||LEX=="=="||LEX==">"||LEX=="for"||LEX==">="||LEX=="&&"||LEX=="else"||LEX=="||"||LEX=="}")
	{ 
        if(ana) 
            cout << "Expr1���ؿ�"<<endl;
        return EmpA; 
    } 
    else 
        cout << "error Expr1"<<endl;
    return EmpA; 
} 
 
Attr Term(FILE*IN,Attr self) 
{ 
    if(LEX=="("||LEX=="ID"||LEX=="UNINT")
    { 
        Attr temp1 = Factor(IN,EmpA); 
        Attr temp2 = Term1(IN,temp1); 
        if(temp2.place=="")
        { 
            return temp1; 
        } 
        else 
			return temp2; 
    } 
    else cout << "error Term"<<endl;
    return EmpA; 
} 
 
Attr Term1(FILE*IN,Attr self) //����*��/��%�������Ԫ���ʽ 
{ 
    if(LEX=="*"||LEX=="/"||LEX=="%")
    { 
        string Mark=LEX; 
        getNext(IN); 
        Attr temp1=Factor(IN,EmpA); 
        Attr temp2=NewTemp(); 
        Gen(Mark,self.place,temp1.place,temp2.place); 
        Attr temp3=Term1(IN,temp2); 
        if(temp3.place=="")
            return temp2; 
        else 
            return temp3; 
    } 
    else if(LEX==";"||LEX==")"||LEX=="<"||LEX=="do"||LEX=="<="||LEX=="!="||LEX=="=="||LEX==">"||LEX=="for"||LEX==">="||LEX=="&&"||LEX=="else"||LEX=="||"||LEX=="}")
	{ 
        return EmpA; 
    } 
    return EmpA; 
} 
 
Attr Factor(FILE*IN,Attr self) 
{ 
    if(LEX=="ID")
    { 
        Attr temp1= {IDF,""};
        if(!isDef(IDF)) 
        { 
            cout <<"("<<row<<","<<colum<<")"<<"����δ�������:"<<IDF<<endl;
            WRcount++; 
        } 
        getNext(IN); 
        return temp1; 
 
    } 
    else if(LEX=="UNINT")
    { 
        Attr temp1= {IDF,""};
        getNext(IN); 
        return temp1; 
    } 
    else if(LEX=="(")
    { 
        getNext(IN); 
        Attr temp1=Expr(IN,EmpA); 
        if(LEX==")")
        { 
            getNext(IN); 
            return temp1; 
        } 
        else 
            cout << "error Factor"<<endl;
    } 
    else 
        cout <<"error Factor"<<endl; 
    return EmpA; 
} 
 
Attr ConSenten(FILE*IN,Attr self) //����if������������Ԫʽ 
{ 
    if(LEX=="if")
    { 
        getNext(IN); 
        { 
            if(LEX=="(")
            { 
                getNext(IN); 
                Attr temp1=ConExp(IN,EmpA); 
                if(LEX==")")
                { 
                    getNext(IN); 
                    BackPatchT(temp1.Start,NXQ); //������������ת�� 
                    Senten(IN,EmpA);  
                    ConSenten1(IN,temp1); //����else 
                    return EmpA; 
                } 
            } 
        } 
    } 
    else 
        cout << "error ConSenten"<<endl;
} 
 //else��� 
Attr ConSenten1(FILE*IN,Attr self) 
{ 
    if(LEX=="else")
    { 
        int Mark=NXQ; 
        Gen("j","","","?");
        BackPatchF(self.End,NXQ); //������������ת�� 
        getNext(IN); 
        Senten(IN,EmpA); 
        string Mark1=itos(NXQ+1); 
        Q[Mark].result=Mark1; 
        return self; 
    } 
    else if(LEX==";"||LEX=="}")
    { 
        BackPatchF(self.End,NXQ); 
        return EmpA; 
    } 
    else 
        cout <<  "error ConSenten1"<<endl;
    return EmpA; 
} 
 
Attr ConExp(FILE*IN,Attr self) //if(....) �����ڵ����� �����ж����� 
{ 
    if(LEX=="("||LEX=="ID"||LEX=="UNINT")
    { 
        self.Start=NXQ; 
        self.End=NXQ+1; 
        Attr temp1=RelaExp(IN,self); 
        Gen(temp1.type,temp1.place,temp1.arg,"0");
        Gen("j","","","0");
        ConExp1(IN,temp1); 
        return self; 
    } 
    else 
        cout <<"error ConExp"<<endl; 
    return EmpA; 
} 
 
Attr ConExp1(FILE*IN,Attr self) //����&& || ��ʱ   if��.....)
{ 
	if(LEX=="&&")
	{ 
       	LinkT(self.Start,NXQ); 
        self.Start=NXQ; 
        getNext(IN); 
        Attr temp1=RelaExp(IN,self); 
        Gen(temp1.type,temp1.place,temp1.arg,"0");
        Gen("j","","","0");
        self=ConExp1(IN,temp1); 
        return self; 
	} 
	else if(LEX=="||")
	{ 
    	LinkF(self.End,NXQ); 
        self.End=NXQ; 
        getNext(IN); 
        Attr temp1=RelaExp(IN,self); 
        Gen(temp1.type,temp1.place,temp1.arg,"0");
        Gen("j","","","0");
        self=ConExp1(IN,temp1); 
        return self; 
	} 
	else if(LEX==")")
	{ 
	    return self; 
	} 
	else 
	    cout << "error ConExp1"<<endl;
	return EmpA; 
} 
 
Attr RelaExp(FILE*IN,Attr self) 
{ 
    if(LEX=="("||LEX=="ID"||LEX=="UNINT")
    { 
        Attr temp1=Expr(IN,EmpA); 
        self.place = temp1.place; //ȷ��������ŵ�λ��
        Attr temp2 =RelaID(IN,EmpA); 
        self.type = temp2.type; //ȷ����ת����<,>,>=,<=.... 
        Attr temp3 = Expr(IN,EmpA); 
        self.arg = temp3.place; //ȷ������ 
        return self; 
    } 
    else 
        cout << "error RelaExp"<<endl;
    return EmpA;  
} 
 
Attr RelaID(FILE*IN,Attr self) 
{ 
  if(LEX=="<"||LEX=="<="||LEX=="!="||LEX=="=="||LEX==">"||LEX==">=")
    { 
        self.type="j"+LEX;//��ת���� 
        getNext(IN); 
        return self; 
    } 
    else 
        cout << "error RelaID"<<endl;
    return EmpA; 
} 
 
 
Attr ComSenten(FILE*IN,Attr self) //����{}�е����� 
{ 
    if(LEX=="{")
    { 
        getNext(IN); 
        SentenList(IN); 
        if(LEX=="}")
        { 
            getNext(IN); 
            return self; 
        } 
    } 
    else 
        cout << "error ComSenten"<<endl;
    return EmpA; 
} 
 
void Wunify(int M) //ȷ����ת��λ�� 
{ 
    string Mark=itos(NXQ); 
    for(int i=M; i<NXQ; i++) 
    { 
        if(Q[i].result==Mark) 
        { 
            Q[i].result=Q[NXQ-1].result; 
        } 
    } 
} 
Attr WhileSenten(FILE*IN,Attr self) //����while 
{ 
    if(LEX=="while")
    { 
        getNext(IN); 
        if(LEX=="(")
        { 
            string Mark=itos(NXQ+1); 
            int M=NXQ+1; 
            getNext(IN); 
            Attr temp1=ConExp(IN,EmpA); 
            { 
                if(LEX==")")
                { 
                    getNext(IN); 
                    BackPatchT(temp1.Start,NXQ); //�������� 
                    Senten(IN,EmpA); //ȷ������ 
                    BackPatchF(temp1.End,NXQ+1); //������� 
                    Gen("j","","",Mark);//��ת 
                    Wunify(M);//���»ص�whileѭ������ �� ����ת 
                    return EmpA; 
            	} 
        	} 
    	} 
    else 
        cout <<"error WhileSenten"<<endl; 
    return EmpA; 
	} 
}
Attr DoWhileSenten(FILE*IN,Attr self) //����dowhile 
{ 
    if(LEX=="do")
    { 
        getNext(IN); 
        if(LEX=="{")
	    { 
	        getNext(IN); 
	        string Mark=itos(NXQ+1); //Markȷ����ת��λ�� 
	        SentenList(IN); 
	        if(LEX=="}")
	        { 
	         getNext(IN);
	         if(LEX=="while")
	         {
	         	getNext(IN);
	         	if(LEX=="(")
	         	{
		            int M=NXQ+1; 
		            getNext(IN); 
		            Attr temp1=ConExp(IN,EmpA); 
		            { 
		                if(LEX==")")
		                { 
		                    getNext(IN); 
		                    if(LEX==";")
		                  	{
			                  	BackPatchT(temp1.Start,NXQ); 
			                    Senten(IN,EmpA); 
			                    BackPatchF(temp1.End,NXQ+1); 
			                    Gen("j","","",Mark);
			                    Wunify(M);
			                    return EmpA; 
							}  
		                } 
	            	} 
				 }
			 }
	        } 
	    } 
    } 
    else 
        cout <<"error DoWhileSenten"<<endl; 
    return EmpA; 
} 

void Wunify1(int M) //ȷ����ת��λ�� 
{  
	string Mark2=itos(NXQ); 
    for(int i=M; i<NXQ; i++) 
    { 
        if(Q[i].result==Mark2) 
        { 
            Q[i].result=Q[NXQ-1].result; 
        } 
    } 
} 
Attr ForSenten(FILE*IN,Attr self) //����for��� 
{ 
    if(LEX=="for")
    { 
        getNext(IN); 
        if(LEX=="(")
        { 
        	getNext(IN);
        	AssignSenten(IN,EmpA);//��ֵ��� 
        	if(LEX==";")
        	{
        		int M=NXQ+1;
        		string Mark=itos(NXQ+1); //Markȷ����ת��λ�� 
		        getNext(IN);  
		        Attr temp1=ConExp(IN,EmpA); //�����ж���� 
	        	{ 
	        		if(LEX==";")
			        {		
						string Mark2=itos(NXQ+1); //Markȷ����ת��λ�� 	        		
						getNext(IN);			     	
		                Expr(IN,EmpA); //�������ʽ��� 
		                Gen("j","","",Mark); 
						Wunify(M);
						int m2=NXQ+1;		            
						if(LEX==")")
		                {
	                    	getNext(IN);
	                    	BackPatchT(temp1.Start,NXQ); //�������� 
	                    	if(LEX=="{")
							{								
								getNext(IN);
								SentenList(IN);
								if(LEX=="}")
								{
									Gen("j","","",Mark2);
									Wunify1(m2);
									getNext(IN);
									BackPatchF(temp1.End,NXQ); //������� 
									return EmpA;
								 } 
							}
						}
					} 
				}		    
		    } 
	    } 
	}	
    else
        cout <<"error ForSenten"<<endl; 
    return EmpA; 	 
}


//����Ŀ����� (���)
FILE *fp;  
int temp=0;
void print_code(int i)
{
	if(Q[i].OP=="=")
	{
		temp+=1;
		fprintf(fp,"_%d:",temp);
		if(Q[i].arg1[0]>='0'&&Q[i].arg1[0]<='9')
		{
			fprintf(fp,"mov ax, %s\n",Q[i].arg1.c_str()); 
			fprintf(fp,"mov ds:[_%s],ax\n",Q[i].result.c_str());
		}
		else
		{
			fprintf(fp,"mov ax,ds:[_%s]\n",Q[i].arg1.c_str());
			fprintf(fp,"mov ds:[_%s],ax\n",Q[i].result.c_str());
		}
	//	fprintf(fp,"		MOV  AX,%s\n",Q[i].result.c_str());
	//	fprintf(fp,"		MOV  DX,AX\n");
	}
	else if(Q[i].OP == "+"){
		temp+=1;
		fprintf(fp,"_%d:",temp);
		if(Q[i].arg1[0]>='0'&&Q[i].arg1[0]<='9')
		{
			fprintf(fp,"mov ax, %s\n",Q[i].arg1.c_str()); 
		}
		else
		{
			fprintf(fp,"mov ax,[_%s]\n",Q[i].arg1.c_str());
		}
		if(Q[i].arg2[0]>='0' && Q[i].arg2[0]<='9')
		{
				fprintf(fp,"add ax,%s\n",Q[i].arg2.c_str());
		}
		else
		{
				fprintf(fp,"add ax,[_%s]\n",Q[i].arg2.c_str());
		}
		fprintf(fp,"mov [_%s],ax\n",Q[i].result.c_str());
	/*	fprintf(fp,"		MOV  AX,%s\n",Q[i].arg1.c_str());
		fprintf(fp,"		ADD  AX,%s\n",Q[i].arg2.c_str());
		fprintf(fp,"		MOV  %s,AX\n",Q[i].result.c_str());
		cout<<"		MOV  "<<"AX,"<<Q[i].arg1<<endl;
		cout<<"		ADD  "<<"AX,"<<Q[i].arg2<<endl;
		cout<<"		MOV  "<<Q[i].result<<",AX"<<endl;*/
		
	}else if(Q[i].OP =="-"){
		temp+=1;
		fprintf(fp,"_%d:",temp);
		fprintf(fp,"_%d:",temp++);
		if(Q[i].arg1[0]>='0'&&Q[i].arg1[0]<='9')
		{
			fprintf(fp,"mov ax, %s\n",Q[i].arg1.c_str()); 
		}
		else
		{
			fprintf(fp,"mov ax,[_%s]\n",Q[i].arg1.c_str());
		}
		if(Q[i].arg2[0]>='0' && Q[i].arg2[0]<='9')
		{
				fprintf(fp,"sub ax,%s\n",Q[i].arg2.c_str());
		}
		else
		{
				fprintf(fp,"sub ax,[_%s]\n",Q[i].arg2.c_str());
		}
		fprintf(fp,"mov [_%s],ax\n",Q[i].result.c_str());	
	}
	else if(Q[i].OP =="*"){
		temp+=1;
		fprintf(fp,"_%d:",temp);
		if(Q[i].arg1[0]>='0'&&Q[i].arg1[0]<='9')
		{
			fprintf(fp,"mov ax,%s\n",Q[i].arg1.c_str());
		}
		else
		{
			fprintf(fp,"mov ax,[_%s]\n",Q[i].arg1.c_str());
		}
		if(Q[i].arg2[0]>='0'&&Q[i].arg2[0]<='9')
		{
			fprintf(fp,"mov bx,%s\n",Q[i].arg2.c_str());
		}
		else
		{
			fprintf(fp,"mov bx,[_%s]\n",Q[i].arg2.c_str());
		}
		fprintf(fp,"mul bx\n");
		fprintf(fp,"mov [_%s],ax\n",Q[i].result.c_str());
	}else if(Q[i].OP == "/"){
		temp+=1;
		fprintf(fp,"_%d:",temp);
		fprintf(fp,"MOV  AX,%s\n",Q[i].arg1.c_str());
		fprintf(fp,"MOV  DX,0\n");
		fprintf(fp,"MOV  AX,%s\n",Q[i].arg2.c_str());
		fprintf(fp,"DIV  BX\n");
		fprintf(fp,"MOV  %s,DX\n",Q[i].result.c_str());
	}else if(Q[i].OP == "%"){
		temp+=1;
		fprintf(fp,"_%d:",temp);
		fprintf(fp,"MOV  AX,%s\n",Q[i].arg1.c_str());
		fprintf(fp,"MOV  DX,0\n");
		fprintf(fp,"MOV  AX,%s\n",Q[i].arg2.c_str());
		fprintf(fp,"DIV  BX\n");
		fprintf(fp,"MOV  %s,DX\n",Q[i].result.c_str());
	}else if(Q[i].OP == "j<"){
		temp+=1;
		fprintf(fp,"_%d:",temp);
		fprintf(fp,"MOV DX,1\n");
		fprintf(fp,"MOV  AX,%s\n",Q[i].arg1.c_str());
		fprintf(fp,"CMP	 AX,%s\n",Q[i].arg2.c_str());
		fprintf(fp,"JB_LT\n");
		fprintf(fp,"MOV  DX,0\n");
//		fprintf(fp,"	_LT:MOV  %s,DX\n",Q[i].result.c_str());
		fprintf(fp,"	_LT:MOV  M,DX\n");
		fprintf(fp,"	MOV AX,M\n");
		fprintf(fp,"	CMP AX,0\n");
		fprintf(fp,"	JE_EZ\n");
		fprintf(fp,"	JMP far ptr  %s\n",Q[i].result.c_str());
		fprintf(fp,"	_EZ:NOP\n");
	}else if(Q[i].OP == "j>="){
		temp+=1;
		fprintf(fp,"_%d:",temp);
		fprintf(fp,"mov dx,1\n");
		if(Q[i].arg1[0]>='0'&&Q[i].arg1[0]<='9')
		{
			fprintf(fp,"mov ax,%s\n",Q[i].arg1.c_str());
		}
		else
		{
			fprintf(fp,"mov bx,ds:[_%s]\n",Q[i].arg1.c_str());
		}
		if(Q[i].arg2[0]>='0'&&Q[i].arg2[0]<='9')
		{
			fprintf(fp,"cmp ax,%s\n",Q[i].arg2.c_str());
		}
		else
		{
			fprintf(fp,"cmp ax,[_%s]\n",Q[i].arg2.c_str());
		}
	//	temp+=1;
		fprintf(fp,"jnb _%d_n\n",temp);
		
		fprintf(fp,"mov dx,0\n");
	//	temp+=1;
		fprintf(fp,"_%d_n:mov es:[4],dx\n",temp);
		
		temp+=1;
		fprintf(fp,"_%d:mov ax,es:[4]\n",temp);
		fprintf(fp,"cmp ax,0\n");
	//	fprintf(fp,"jne_%d_n\n",temp);
		fprintf(fp,"jne n\n",temp);
		
		fprintf(fp,"jmp far ptr _%s\n",Q[i].result.c_str());
	//	fprintf(fp,"_%d_n:nop\n",temp);
		fprintf(fp,"n:nop\n",temp);
	}else if(Q[i].OP == "j>"){
		fprintf(fp,"MOV DX,1\n");
		fprintf(fp,"MOV  AX,%s\n",Q[i].arg1.c_str());
		fprintf(fp,"CMP  AX,%s\n",Q[i].arg2.c_str());
		fprintf(fp,"JA_GT\n");
		fprintf(fp,"MOV  DX,0\n");
	//	fprintf(fp,"	_GT:MOV  %s,DX\n",Q[i].result.c_str());
		fprintf(fp,"_GT:MOV  M,DX\n");
		fprintf(fp,"MOV AX,M\n");
		fprintf(fp,"CMP AX,0\n");
		fprintf(fp,"JE_EZ\n");
		fprintf(fp,"JMP far ptr  %s\n",Q[i].result.c_str());
		fprintf(fp,"_EZ:NOP\n");
	}else if(Q[i].OP == "j<="){
		fprintf(fp,"MOV DX,1\n");
		fprintf(fp,"MOV  AX,%s\n",Q[i].arg1.c_str());
		fprintf(fp,"CMP  AX,%s\n",Q[i].arg2.c_str());
		fprintf(fp,"JNA_LE\n");
		fprintf(fp,"MOV  DX,0\n");
	//	fprintf(fp,"	_LE:MOV  %s,DX\n",Q[i].result.c_str());
		fprintf(fp,"_LE:MOV  M,DX\n");
		fprintf(fp,"MOV AX,M\n");
		fprintf(fp,"CMP AX,0\n");
		fprintf(fp,"JE_EZ\n");
		fprintf(fp,"JMP far ptr  %s\n",Q[i].result.c_str());
		fprintf(fp,"_EZ:NOP\n");
	}else if(Q[i].OP == "j=="){
		fprintf(fp,"MOV DX,1\n");
		fprintf(fp,"MOV  AX,%s\n",Q[i].arg1.c_str());
		fprintf(fp,"CMP  AX,%s\n",Q[i].arg2.c_str());
		fprintf(fp,"JE_EQ\n");
		fprintf(fp,"MOV  DX,0\n");
	//	fprintf(fp,"	_EQ:MOV  %s,DX\n",Q[i].result.c_str());
		fprintf(fp,"_EQ:MOV  M,DX\n");
		fprintf(fp,"MOV AX,M\n");
		fprintf(fp,"CMP AX,0\n");
		fprintf(fp,"JE_EZ\n");
		fprintf(fp,"JMP far ptr  %s\n",Q[i].result.c_str());
		fprintf(fp,"_EZ:NOP\n");
	}else if(Q[i].OP == "j!="){
		fprintf(fp,"MOV DX,1\n");
		fprintf(fp,"MOV  AX,%s\n",Q[i].arg1.c_str());
		fprintf(fp,"CMP  AX,%s\n",Q[i].arg2.c_str());
		fprintf(fp,"JNE_NE\n");
		fprintf(fp,"MOV  DX,0\n");
	//	fprintf(fp,"	_NE:MOV  %s,DX\n",Q[i].result.c_str());
		fprintf(fp,"_NE:MOV  M,DX\n");
		fprintf(fp,"MOV AX,M\n");
		fprintf(fp,"CMP AX,0\n");
		fprintf(fp,"JE_EZ\n");
		fprintf(fp,"JMP far ptr  %s\n",Q[i].result.c_str());
		fprintf(fp,"_EZ:NOP\n");
	}else if(Q[i].OP == "j"){
	/*	fprintf(fp,"	MOV DX,1\n");
		fprintf(fp,"	MOV  AX,%s\n",Q[i].arg1.c_str());
		fprintf(fp,"	CMP  AX,0\n");
		fprintf(fp,"	JE_NOT\n");
		fprintf(fp,"	MOV  DX,0\n");
		fprintf(fp,"	_NOT:MOV  %s,DX\n",Q[i].result.c_str());
		cout<<"		MOV  "<<"DX,1"<<endl;
		cout<<"		MOV  "<<"AX,"<<Q[i].arg1<<endl;
		cout<<"		CMP  AX,0"<<endl;
		cout<<"		JE_NOT"<<endl;
		cout<<"		MOV  "<<"DX,0"<<endl;
		cout<<"		_NOT:MOV  "<<Q[i].result<<",DX"<<endl; */
	//	fprintf(fp,"JMP far ptr %s\n",Q[i].result.c_str()); 
//	fprintf(fp,"jmp far ptr_%s\n",Q[i].result.c_str());
	}else if(Q[i].OP == "ret"){
		fprintf(fp,"MOV  SP,BP\n");
		fprintf(fp,"POP  BP\n");
		fprintf(fp,"RET\n");
	}
	
}

void testCode()
{
	fp=fopen("Ŀ�����.txt","w");
	fprintf(fp,"assume cs:code,ds:data,ss:stack,es:extended\n");
	fprintf(fp,"extended segment\n");
	fprintf(fp,"	db 1024 dup (0)\n");
	fprintf(fp,"extended ends\n");
	fprintf(fp,"stack segment\n");
	fprintf(fp,"	db 1024 dup (0)\n");
	fprintf(fp,"stack ends\n");
	fprintf(fp,"data segment\n");
	fprintf(fp,"	_buff_p db 256 dup (24h)\n");
	fprintf(fp,"	_buff_s db 256 dup (0)\n");
	fprintf(fp,"	_msg_p db 0ah,'Output:',0\n");
	fprintf(fp,"	_msg_s db 0ah,'Input:',0\n");
	fprintf(fp,"	_a dw 0\n");
	fprintf(fp,"	_T1 dw 0\n");
	fprintf(fp,"	_T2 dw 0\n");
	fprintf(fp,"data ends\n");
	fprintf(fp,"code segment\n");
	fprintf(fp,"start:mov ax,extended\n");
	fprintf(fp,"		mov es,ax\n");
	fprintf(fp,"		mov ax,stack\n");
	fprintf(fp,"		mov ss,ax\n");
	fprintf(fp,"		mov sp,1024\n");
	fprintf(fp,"		mov bp,sp\n");
	fprintf(fp,"		mov ax,data\n");
	fprintf(fp,"		mov ds,ax\n");
	fprintf(fp,"		\n");
	//������Ԫʽ�������Ӧ�Ļ�����
	for(int i=0; i<NXQ; i++) 
    {  
        print_code(i);
	} 
	fprintf(fp,"\n");
	fprintf(fp,"code ends\n");
	fprintf(fp,"end start");
}

int main() 
{ 
    FILE *IN; 
    IN=fopen("test.txt","r");
    getNext(IN); 
    Program(IN); 
    show(); 
    fstream file("�м����.txt", ios::out);//����ļ����� 
    fstream oFile ; 
    oFile.open("�м����.txt");
    for(int i=0; i<NXQ; i++) 
    { 
        oFile << "("<<i+1 << ")  ("<<Q[i].OP<<","<<Q[i].arg1<<","<<Q[i].arg2<<","<<Q[i].result<<")"<<endl;
    } 
    cout << "��Ԫʽ�����ɣ�"<<endl;
    testCode();//Ŀ����� 
	printList();
 	return 0;
} 
