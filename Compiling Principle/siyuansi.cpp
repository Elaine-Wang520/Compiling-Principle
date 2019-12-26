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
int No,row=1,colum=1,Ncolum,Nrow;//行列号


//符号表
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
//常量
typedef class List
{
	public:
	long memloc; //入口
	string name; //常量名
    string type; //常量类型(1:int,2:char)
    string value; //常量的值
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
//常量的哈希表修改

void List_delete(string name)
{
	int h = hash(name);
	ListHash[h] = NULL;
}
//常量的哈希表查找
long List_find(string name)
{
	int h = hash(name);
	List *l;
	l = ListHash[h];
	return l->memloc;
}
//常量符号表的打印
void printList()
{
	int i;
	cout << "变量符号表" << endl;
	cout << "入口\t常量名\t类型\t值" << endl;
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



 
//判断是否是字母 
bool isAlpha(char a) 
{ 
    if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||a=='_') 
        return true; 
    else 
		return false; 
} 
 //判断是否是标识符 
bool isAlnum(char a) 
{ 
    if((a>='0'&&a<='9')||(a>='a'&&a<='z')||(a>='A'&&a<='Z')||a=='_') 
        return true; 
    else 
		return false; 
} 
 
bool isDigit(char a) //判断是否是数字 
{ 
    if(a>='0'&&a<='9') 
        return true; 
    else 
		return false; 
} 
char name1[20]; 
int lookup(char a[]) // 查询关键字 
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
int scanner(FILE *infile) //扫描器 
{ 
    char c; 
    c = fgetc(infile); //读取字符 
    Ncolum = colum; //单词首字母列号 
    Nrow=row;       //单词首字母行号 
    if(c=='\n') //换行 
    { 
        row++; 
        colum=1; 
    } 
    else 
		colum++; 
    int i=1; 
    memset(token,0,sizeof(token)); //给token的内存赋值 
    //注释 
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
            //此形式注释 
        case '/': 
            fgets(s,1024,infile); //s:字符型指针，指向存储读入数据的缓冲区的地址。1024: 从流中读入1023-1个字符 infile ： 指向读取的流。
            fseek(infile,-1,1); //文件指针，向左偏移，移动1 
            colum--; 
            break; 
            /*此形式注释*/ 
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
                    break; //找到’/*‘ 
                } 
                else 
				flag=false; //确保*后紧接/ 
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
            return 7;   //并非注释，为‘/’ 
        } 
        return -1; 
 
    } 
    
// 标识符 
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
            c=fgetc(infile); //下一个字符 
            if(c=='\n') //换行 
            { 
                row++; 
                colum=1;  
            } 
            else //下一字符 
				colum++; 
        } 
        token[i]='\0'; 
        fseek(infile,-1,1); //左移一位 
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
        //无符号整数 
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
	// 运算符 
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
            if(c=='=') // 运算符‘==’ 
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
			if(c=='=') //运算符‘<=’ 
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
			if(c=='=') //运算符‘!=’ 
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
            if(c=='|') //运算符 ‘||’ 
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
            if(c=='&') //运算符 ‘&&’ 
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
            if(c=='=') //运算符 ‘>=’ 
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
	//	界符 
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


 
//语法分析器 (生成四元式)

int NXQ=0; //四元式编号 
int T=1; 
bool ana=false; //
bool Db=false; //
struct Gencode     //四元式表 
{ 
    string OP,arg1,arg2,result,arg3; 
} Q[10000]; 
 
struct Attr     //属性文法  
{ 
	public:
		string place;//地址 
		string type;//类型 
		string arg; //参数 
		int Start;//开始 
		int End; //结尾 
}; 
int DefN=0; //已被定义标识符个数 
string Def[10000]; 

void AddDef(string a) //添加已经被定义的表示符 
{ 
    Def[DefN]=a; 
    DefN++; 
} 
 
bool isDef(string A) //是否被定义 
{ 
    for(int i=0; i<DefN; i++) 
    { 
        if(Def[i]==A) 
            return true; 
    } 
    return false; 
} 
string itos(int int_temp) // 将数字转为string类型 
{ 
    string string_temp; 
    stringstream stream; 
    stream<<int_temp; 
    string_temp=stream.str(); 
    return string_temp; 
} 
 
Attr NewTemp() //生成临时变量 
{ 
    Attr ans ={"T",""};
    ans.place = ans.place+itos(T); 
    T++; 
    return ans; 
} 
 
void Gen(string OP,string arg1,string arg2,string result) 
{ 
    Q[NXQ]={OP,arg1,arg2,result}; //生成一条中间代码 
    NXQ++;  
} 


//显示四元式 
void show() 
{ 
    cout << "四元式如下："<<endl;
    for(int i=0; i<NXQ; i++) 
    {  
        cout << "("<<i+1<<")  ("<<Q[i].OP<<","<<Q[i].arg1<<","<<Q[i].arg2<<"," <<Q[i].result<<")"<<endl;
	} 
	 cout << "结束展示"<<endl;
}
void LinkT(int start ,int End)  // 四元式序列标号Start-End的有条件跳转四元式的result连成链 
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
void LinkF(int start,int End) // 四元式序列标号Start-End的无条件跳转四元式的result连成链 
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
void BackPatchT(int start,int End) //四元式序列标号Start-End的有条件跳转四元式result未填充部分全填为End+1 
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
 void BackPatchF(int start,int End)// 四元式序列标号Start-End的无条件跳转四元式result未填充部分全填为End+1 
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
string LEX; //切分好的单词 
string IDF; //标识符 
bool flag=false; 
int WRcount=0; //记录错误的个数 
void getNext(FILE *IN) // 读入下一个字符 
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
            cout << "读入"<<LEX<<endl;
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
           //         cout<<"("<<Nrow<<","<<Ncolum<<"错误（不能识别的字符）："<<LEX<<endl;
           //         WRcount++; 
                    getNext(IN); 
                } 
            } 
            else if(Num==2) // 识别到标识符 
            { 
                IDF=LEX; 
                LEX ="ID";
            } 
            else if(Num==3) // 识别到无符号整数 
            { 
                 IDF=LEX; 
				 LEX ="UNINT";
            }
        } 
    } 
    else 
    { 
        flag=true; 
        Gen("ret","","","0");//结束 
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
        cout << "分析完成！"<<endl;
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
 void Block(FILE*IN) //分析语法 
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
void SentenList(FILE*IN) //句子列表 ,找出进入那种句型 
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
    if(LEX=="ID")//如果是标识符 
    { 
        AssignSenten(IN,self); 
        self.End=NXQ; 
        return self; 
    } 
    else if(LEX=="for")//进入do while 
    {
    	ForSenten(IN,self);  
		self.End=NXQ; 
        return self; 
	} 
    else if(LEX=="if")//进入if 
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
    else if(LEX=="while")//进入while 
    { 
        WhileSenten(IN,self); 
        self.End=NXQ; 
        return self; 
    } 
    else if(LEX=="do")//进入do while 
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
Attr IntSenten(FILE*IN,Attr self) //确定标识符的类型 
{ 
  if(LEX=="int"||LEX=="char"||LEX=="float")
    { 
        getNext(IN); 
        if(LEX=="ID")
        { 
            AddDef(IDF); //加入标识符 
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
 
/*Attr IntSenten1(FILE*IN,Attr self) //int a,b,c;这种情况赋值 
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

Attr AssignSenten(FILE*IN,Attr self) //赋值语句 
{ 
    if(LEX=="ID")
    { 
        if(!isDef(IDF)) 
        { 
            cout <<"("<<row<<","<<colum<<")"<<"出现未定义变量:"<<IDF<<endl;
            WRcount++; 
        } 
        string Mark=IDF; 
        getNext(IN); 
        if(LEX=="=")
        { 
            getNext(IN); 
            Attr s1=Expr(IN,EmpA); 
            Gen("=",s1.place,"",Mark);//生成算术表达式的四元式 
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
 //算术表达式的四元表达式 
Attr Expr(FILE*IN,Attr self)
{ 
    if(LEX=="("||LEX=="ID"||LEX=="UNINT")//先*/后+- 
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
 
Attr Expr1(FILE*IN,Attr self) //＋、-运算 
{ 
    if(LEX=="+"||LEX=="-")
    { 
        string Mark=LEX; 
        getNext(IN); 
        Attr temp1=Term(IN,EmpA); 
        Attr temp2=NewTemp(); 
        Gen(Mark,self.place,temp1.place,temp2.place); //生成四元表达式  
        Attr temp3=Expr1(IN,temp2); 
        if(temp3.place=="")
            return temp2; 
        else 
			return temp3; 
    } 
     else if(LEX==";"||LEX==")"||LEX=="<"||LEX=="do"||LEX=="<="||LEX=="!="||LEX=="=="||LEX==">"||LEX=="for"||LEX==">="||LEX=="&&"||LEX=="else"||LEX=="||"||LEX=="}")
	{ 
        if(ana) 
            cout << "Expr1返回空"<<endl;
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
 
Attr Term1(FILE*IN,Attr self) //进行*、/、%运算的四元表达式 
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
            cout <<"("<<row<<","<<colum<<")"<<"出现未定义变量:"<<IDF<<endl;
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
 
Attr ConSenten(FILE*IN,Attr self) //进入if条件句生成四元式 
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
                    BackPatchT(temp1.Start,NXQ); //回填有条件跳转链 
                    Senten(IN,EmpA);  
                    ConSenten1(IN,temp1); //进入else 
                    return EmpA; 
                } 
            } 
        } 
    } 
    else 
        cout << "error ConSenten"<<endl;
} 
 //else语句 
Attr ConSenten1(FILE*IN,Attr self) 
{ 
    if(LEX=="else")
    { 
        int Mark=NXQ; 
        Gen("j","","","?");
        BackPatchF(self.End,NXQ); //回填无条件跳转链 
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
 
Attr ConExp(FILE*IN,Attr self) //if(....) 括号内的内容 ，即判断条件 
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
 
Attr ConExp1(FILE*IN,Attr self) //遇到&& || ）时   if中.....)
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
        self.place = temp1.place; //确定变量存放的位置
        Attr temp2 =RelaID(IN,EmpA); 
        self.type = temp2.type; //确定跳转类型<,>,>=,<=.... 
        Attr temp3 = Expr(IN,EmpA); 
        self.arg = temp3.place; //确定参数 
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
        self.type="j"+LEX;//跳转类型 
        getNext(IN); 
        return self; 
    } 
    else 
        cout << "error RelaID"<<endl;
    return EmpA; 
} 
 
 
Attr ComSenten(FILE*IN,Attr self) //处理{}中的内容 
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
 
void Wunify(int M) //确定跳转的位置 
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
Attr WhileSenten(FILE*IN,Attr self) //进入while 
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
                    BackPatchT(temp1.Start,NXQ); //回填真链 
                    Senten(IN,EmpA); //确定句型 
                    BackPatchF(temp1.End,NXQ+1); //回填假链 
                    Gen("j","","",Mark);//跳转 
                    Wunify(M);//重新回到while循环（） 中 ，跳转 
                    return EmpA; 
            	} 
        	} 
    	} 
    else 
        cout <<"error WhileSenten"<<endl; 
    return EmpA; 
	} 
}
Attr DoWhileSenten(FILE*IN,Attr self) //进入dowhile 
{ 
    if(LEX=="do")
    { 
        getNext(IN); 
        if(LEX=="{")
	    { 
	        getNext(IN); 
	        string Mark=itos(NXQ+1); //Mark确定跳转的位置 
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

void Wunify1(int M) //确定跳转的位置 
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
Attr ForSenten(FILE*IN,Attr self) //进入for语句 
{ 
    if(LEX=="for")
    { 
        getNext(IN); 
        if(LEX=="(")
        { 
        	getNext(IN);
        	AssignSenten(IN,EmpA);//赋值语句 
        	if(LEX==";")
        	{
        		int M=NXQ+1;
        		string Mark=itos(NXQ+1); //Mark确定跳转的位置 
		        getNext(IN);  
		        Attr temp1=ConExp(IN,EmpA); //条件判断语句 
	        	{ 
	        		if(LEX==";")
			        {		
						string Mark2=itos(NXQ+1); //Mark确定跳转的位置 	        		
						getNext(IN);			     	
		                Expr(IN,EmpA); //算术表达式语句 
		                Gen("j","","",Mark); 
						Wunify(M);
						int m2=NXQ+1;		            
						if(LEX==")")
		                {
	                    	getNext(IN);
	                    	BackPatchT(temp1.Start,NXQ); //回填真链 
	                    	if(LEX=="{")
							{								
								getNext(IN);
								SentenList(IN);
								if(LEX=="}")
								{
									Gen("j","","",Mark2);
									Wunify1(m2);
									getNext(IN);
									BackPatchF(temp1.End,NXQ); //回填假链 
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


//生成目标代码 (汇编)
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
	fp=fopen("目标代码.txt","w");
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
	//遍历四元式，输出对应的汇编代码
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
    fstream file("中间代码.txt", ios::out);//清空文件内容 
    fstream oFile ; 
    oFile.open("中间代码.txt");
    for(int i=0; i<NXQ; i++) 
    { 
        oFile << "("<<i+1 << ")  ("<<Q[i].OP<<","<<Q[i].arg1<<","<<Q[i].arg2<<","<<Q[i].result<<")"<<endl;
    } 
    cout << "四元式输出完成！"<<endl;
    testCode();//目标代码 
	printList();
 	return 0;
} 
