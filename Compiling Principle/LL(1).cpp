#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include <fstream>
#include <cassert>
using namespace std;
//�ʷ����� 
char x[100],token[50];
char ch;
int sp,front; 
char stack[100];//�洢�ķ�����ʽ 
char queue[100];//�洢���봮 
int c=0;
int syn,i,m=0,n,row1,num=0;
char *rwtab[15]={"char","int","float","break","const","return","void","continue","do","while","if","else","for","void","then"};//�ؼ���
char X,a; 
char VN[11]={'E','G','T','R','F','C','D','I','J','K','\0'};
char VT[20]={'i','+','-','*','/','%','(',')','>','<','@','~','?','^','=','f','e',';','\0'};
char p[26][10]={"TG\0","+E\0","-E\0","\0","FR\0","*T\0","/T\0","%T\0","\0","(E)\0","i\0","EDE\0",">\0","<\0","@\0","~\0","?\0","^\0","=\0","f\0","e\0","i=E\0","f(C)IK\0","eI\0","\0",";\0"};
int M[10][18]={{0,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,1,2,-1,-1,-1,-1,3,3,3,3,3,3,3,-1,-1,24,25},
			{4,-1,-1,-1,-1,-1,4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,8,8,5,6,7,-1,8,8,8,8,8,8,8,-1,-1,24,25},
			{10,-1,-1,-1,-1,-1,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{11,-1,-1,-1,-1,-1,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,12,13,14,15,16,17,-1,-1,-1,-1},
			{21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,22,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,-1}
};
int f=0; 
int count=0; 
char arr_i[100];                    //�ַ����� 
int td[100];                         //�������ʽ���� 
int t=0; 
int id=0;  
int h=0,r=0;
int isletter(char ch)
{
	if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
		return 1;
	else
		return 0;

}
int isdigit(char ch)
{
	if('0'<=ch&&ch<='9')
		return 1;
	else
		return 0;

}
void CharacterString()//�����Ƿ��Ǳ�ʶ��
{
		m=0;
		int flag=0;
		while(isdigit(ch)||isletter(ch)||ch=='_')
		{
			arr_i[h++]=ch;
			token[m++]=ch;
			ch=x[i++];
		}
		token[m++]='\0';
		i--;
		if(m>1)
		{
			syn=700;
			queue[c++]='i';
		}
		else if(m==1)
		{
			syn=500;
			queue[c++]='i';			
		}
		for(n=0;n<15;n++)  //�ж������Ƿ�Ϊ�ؼ��� 
		{
			if(strcmp(token,rwtab[n])==0)
			{
				syn=101+n;
				if(strcmp(token,"void")==0)
				{
					c-=1;
					queue[c++]='v';//void->v
				}
				if(strcmp(token,"then")==0)
				{
					c-=1;
					queue[c++]='t';//then->t
				}
				if(syn==102)
				{
					c-=1;
				queue[c++]='n';//int->n
				}
				else if(syn==103)
				{
					c-=1;
					queue[c++]='l';//float->l	
				}
				else if(syn==101)
				{
					c-=1;
					queue[c++]='c';//char->c
				}
				else if(syn==109)
				{
					c-=1;
					queue[c++]='o';//do->o
				}
				else if(syn==110)
				{
					c-=1;
					queue[c++]='w';//while->w			
				}
				else if(syn==105)
				{
					c-=1;
				   queue[c++]='c';//const->c
				}
				else if(syn==111)
				{
					c-=1;
					queue[c++]='f';//if->f
				}
				else if(syn==112)
				{
					c-=1;
					queue[c++]='e';//else->e			
				}
				else if(syn==113)
				{
					c-=1;
					queue[c++]='r';//for->r
				}
				break;
			}
		}
}
void number()//�����Ƿ�������
{
		num=0;
		if(ch!=0)
		{
			while(isdigit(ch))
			{
				arr_i[h++]=ch;
				num=num*10+ch-'0';
				ch=x[i++];	
			}
			i--;
		}
		syn=400;
		queue[c++]='i';
		if(num==0)
		{
			c--;
			queue[c++]='i';
		}
}
void recognize()
{
	for(n=0;n<8;n++) 
	{
		token[n]=NULL;//��ŵ���
	}
	ch=x[i++];
	while(ch==' ')
	{
		ch=x[i++];
	}
	if(isletter(ch)||ch=='_') 
	{
		CharacterString();
	}
	else if(isdigit(ch))  
	{
		 number();
	}
	else switch(ch)   //�����ַ� 
	{
		case'<':m=0;token[m++]=ch;
					ch=x[i++];
		if(ch=='='){			//<=����
						syn=212;
						token[m++]=ch;
						queue[c++]='~';						
					}
		else{
				queue[c++]='<';
				syn=211;
				i--;
			}break;
		case'>':m=0;token[m++]=ch;		
					ch=x[i++];
		if(ch=='='){//>=����
					syn=214;
					token[m++]=ch;
					queue[c++]='@';	
			}
		else{
				queue[c++]='>';
				syn=213;
				i--;
			}break;
		case'=':m=0;token[m++]=ch;		
					ch=x[i++];
		if(ch=='='){//==����
					syn=215;
					token[m++]=ch;
					queue[c++]='?';
			}
		else{
			    queue[c++]='=';
				syn=219;
				i--;
			}break;
		case'!':m=0;token[m++]=ch;	
					ch=x[i++];
		if(ch=='='){//!=����
					syn=216;
					token[m++]=ch;
					queue[c++]='^';					
			}
		else{
				queue[c++]='!';
				syn=205;
				i--;
			}break;
		case'|':m=0;token[m++]=ch;		
					ch=x[i++];queue[c++]='|';
		if(ch=='|'){//||����
					syn=218;
					token[m++]=ch;			
			}
		else{
				i--;
			}break;
		case '&':m=0;token[m++]=ch;		
					ch=x[i++];
		if(ch=='&'){//&&����
					syn=217;
					token[m++]=ch;	
					queue[c++]='&';		
			}
		else{
				i--;
			}break;
		case'.':syn=220;token[0]=ch;break;
		case'*':syn=206;token[0]=ch;queue[c++]='*';break;
		case'/':syn=207;token[0]=ch;queue[c++]='/';break;
		case'+':syn=209;token[0]=ch;queue[c++]='+';break;
		case'-':syn=210;token[0]=ch;queue[c++]='-';break;
		case'(':syn=201;token[0]=ch;queue[c++]='(';break;
		case')':syn=202;token[0]=ch;queue[c++]=')';break;
		case'{':syn=301;token[0]=ch;queue[c++]='{';break;
		case'}':syn=302;token[0]=ch;queue[c++]='}';break;
		case';':syn=303;token[0]=ch;queue[c++]=';';break;
		case',':syn=304;token[0]=ch;queue[c++]=',';break;
		case'#':syn=1;token[0]=ch;break;
		case'$':syn=0;token[0]=ch;break;//������
		case'\n':syn=-2;break;//����
		default: syn=-1;break;
	}
}

FILE *fp;
//�������ѡ�� 
void err(int n) 
{ 
	 if(n==1) 
	{
	  	fprintf(fp,"�ַ���ƥ��\n");
	  	cout<<"�ַ���ƥ��\n"<<endl;
	}
	 else if(n==2) 
	 {
	 	fprintf(fp,"�ַ�û�г����ڲ���ʽ�ս����VT��\n");
	 	cout<<"�ַ�û�г����ڲ���ʽ�ս����VT��"<<endl;	
	  } 
	 else if(n==3) 
	  {
	  	fprintf(fp,"û���ҵ����ʵĺ�ѡ����ʽ������һ���Ƶ�\n");
		cout<<"û���ҵ����ʵĺ�ѡ����ʽ������һ���Ƶ�"<<endl;
	 }
	 else  
	{
		fprintf(fp,"�þ������ķ����Եľ��ӣ�\n"); 
		cout<<"�þ������ķ����Եľ��ӣ�"<<endl;
	}
} 
 
int len(char str[]) //���㴮���� 
{ 
	 int i=0; 
	 while(str[i]!='\0')
	 	i++; 
	 return i; 
} 
int index(char ch,char str[]) //��λ�� 
{ 
	 int i=0; 
	 while(str[i]!='\0') 
	 { 
	  if(ch!=str[i])
	  	i++; 
	  else 
	  	break; 
	 } 
	 if(str[i]=='\0')
	 	return -1; 
	return i; 
} 
//��ӡ������� 
void print() 
{ 
	fprintf(fp,"(%d)",count);
	 cout<<"("<<count<<")";
	 int i; 
	 for(i=0;i<=sp;i++)
	 {
	 	fprintf(fp,"%c",stack[i]);
	 	cout<<stack[i]; 
	 }	
	 for(;i<=20;i++)
	 {
	 	fprintf(fp," ");
	 	cout<<" ";
	 }
	 for(i=0;i<front;i++)
	 {
	 	fprintf(fp," ");
	 	cout<<" ";
	 }	
	 for(;queue[i]!='#'&&queue[i]!='\0';i++)
	 {
	 	fprintf(fp,"%c",queue[i]);
	 	cout<<queue[i]; 
	 }	
	fprintf(fp,"#");	
	cout<<"#";
	 for(;i<=25;i++)
	 {
	 	fprintf(fp," ");
	 	cout<<" ";
	}	
} 
//�﷨�������� 
void syntax() 
{ 
	int n; 
	count++; //���� 
	print(); //��ӡ��� 
	X=stack[sp]; //���ķ������л�ȡ���ַ� 
	a=queue[front]; //���봮�е��ַ� 
	while(queue[front]=='\0'&&X=='#')//��ȥ���봮�еĿգ�ֱ������# 
	{
		front++;
	}	
	if(X=='#'&&queue[front]=='#')//������ɷ�����##��ƥ�� 
	{
		fprintf(fp,"acc\n");
		cout<<'\t'<<"acc"<<endl;
		f=4;	
	} 
	if((X<'A'||X>'Z')&&X!='#')      	//�ж��ķ����в��Ǵ�д��ĸ
	{ 
		if(X==a) 
	  	{ 
		   sp--; 				//��ջ 
		   front++; 			//������ǰһλ 
		   if(a!='i')        		//�����ʶ��ƥ�� 
		   {  
		   	fprintf(fp,"\%cƥ��\n",a);
	   		cout<<'\t'<<'\''<<a<<"ƥ��"<<endl;
		   } 
		   else 
		  	{  
		  		fprintf(fp,"\%cƥ��\n",arr_i[r++]);
		   		cout<<'\t'<<'\''<<arr_i[r++]<<"ƥ��"<<endl;
		  	} 
	 	} 
	 	else 
		 	f=1;               //�ַ���ƥ��,תȥ������ 
		}
	else 					//X�Ƿ��ս���е�һ�� 
	{ 
		 int tx=index(X,VN);	//{���ս������ѡ��} 
		 int ta=index(a,VT);	//{�ս������ѡ��} 
		 n=M[tx][ta];       	//{����ʽѡ��} 
		 td[t++]=M[tx][ta]; 	//{����ʽѡ��} 
		 if(ta==-1) 			//û���ҵ���Ӧ���ս�� 
		 { 
		 	if(a=='\0')
		 	{
		 		if(tx!=-1)
		 		{
		 			sp--; 
		 			fprintf(fp,"%c->�մ�\n",X);
		  			cout<<'\t'<<X<<"->"<<"�մ�"<<endl;
				 }
			}
			else{
				f=2;
				fprintf(fp,"%c\n",a);
		  		cout<<a<<endl; 
			}
		 }                     //�ַ�û�г����ڲ���ʽ�ս����VT��,תȥ������ 
		 else if(n==-1)
		 	f=3;  		 //û���ҵ����ʵĺ�ѡ����ʽ������һ���Ƶ�,תȥ������ 
		 else 			//�ò���ʽM[tx][ta]������һ���Ƶ� 
		 {  		 
		  	sp--; 
		  	fprintf(fp,"%c->",X);
		  	cout<<'\t'<<X<<"->";
		  	if(len(p[n])!=0) 
		  	{ 
		   		for(int i=len(p[n])-1;i>=0;i--) //�����������ʽ 
		   		{ 
		     		stack[++sp]=p[n][i]; 
		     		fprintf(fp,"%c",p[n][len(p[n])-1-i]);
		     		cout<<p[n][len(p[n])-1-i]; 
		   		} 
		   		fprintf(fp,"\n"); 
		   		cout<<endl; 
		  	} 
		  	else 
		  	{
		  		fprintf(fp,"�մ�\n"); 
		  		cout<<"�մ�"<<endl;
			  }	
		 } 
	}	 
	if(f==0)
 		syntax(); 
	else  
 	{ 
	  	td[t]='-1'; 
	  	err(f); 
 	} 
} 
int main()
{
	i=0;
    row1=1;
	ifstream infile("LL(1)�����ļ�.txt",ios::in); //�����뷽ʽ���ļ�  
        //�ж��Ƿ�򿪳ɹ�  
        if(!infile) {  
        cerr<<"open error!"<<endl;  
        exit(1);  
    }   
    char c;  
    infile>>noskipws;  
    while(!infile.eof()){  
        infile>>c; 
		x[i++]=c; 
    }  
    i--;
    x[i]='$'; 
    infile.close();  
	i=0;
	printf("�ֱ���\t����\t���\n");
	fstream file("LL(1)�﷨����.txt", ios::out);//����ļ����� 
    fstream oFile1; 
    oFile1.open("LL(1)�﷨����.txt");
    oFile1<<"�ֱ���  "<<"����   "<<token<<" ���  "<<endl;
	do{
		recognize();
		switch(syn)
		{
			case 400:cout<<"  "<<syn<<"  "<<num<<"    ����"<<endl;oFile1<<"  "<<syn<<"  "<<num<<"    ����"<<endl;break;   
			case -1: cout<<"�޷�ʶ��!"<<endl;break;
			case -2: row1=row1++;break;//����
			case 1:cout<<"#�ַ�"<<endl;break;
			case 0:cout<<"��������"<<endl;break;
			default:
			if(300<syn&&syn<305)
			{
				cout<<"  "<<syn<<"  "<<token<<"    ���"<<endl;
				oFile1<<"  "<<syn<<"  "<<token<<"    ���"<<endl;
			} 
			if(200<syn&&syn<221)
			{
				cout<<"  "<<syn<<"  "<<token<<"    �����"<<endl;
				oFile1<<"  "<<syn<<"  "<<token<<"    �����"<<endl;
			 }
			if(syn==700)
			{
			  	cout<<"  "<<syn<<"  "<<token<<"    ��ʶ��"<<endl;
			  	oFile1<<"  "<<syn<<"  "<<token<<"    ��ʶ��"<<endl;
			}
			if(syn==500)
			{
				cout<<"  "<<syn<<"  "<<token<<"    �ַ�"<<endl;
				oFile1<<"  "<<syn<<"  "<<token<<"    �ַ�"<<endl;
			}
			if(100<syn&&syn<114) 	
			{
				cout<<"  "<<syn<<"  "<<token<<"    �ؼ���"<<endl;
				oFile1<<"  "<<syn<<"  "<<token<<"    �ؼ���"<<endl;
			}
			break;
		}
	}while(syn!=0);
	queue[c]='#';
//	cout<<len(queue)<<endl; 
	for(i=0;queue[i]!='#';i++)
 		cout<<queue[i]; 
 	cout<<endl; 
 	char S='J'; 
	 sp=front=0; 
	 stack[0]='#'; 
	 sp++; 
	 stack[1]='J'; 
	 cout<<"LL(1)�﷨����:"<<endl;
	 fp=fopen("LL(1)�﷨����.txt","a");
	 syntax();//�﷨�������� 
	 return 0;
}

