#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include <fstream>
#include <cassert>
using namespace std;
//词法分析 
char x[100],token[50];
char ch;
int sp,front; 
char stack[100];//存储文法产生式 
char queue[100];//存储输入串 
int c=0;
int syn,i,m=0,n,row1,num=0;
char *rwtab[15]={"char","int","float","break","const","return","void","continue","do","while","if","else","for","void","then"};//关键字
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
char arr_i[100];                    //字符管理 
int td[100];                         //输出产生式序列 
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
void CharacterString()//分析是否是标识符
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
		for(n=0;n<15;n++)  //判断它们是否为关键字 
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
void number()//分析是否是数字
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
		token[n]=NULL;//存放单词
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
	else switch(ch)   //其他字符 
	{
		case'<':m=0;token[m++]=ch;
					ch=x[i++];
		if(ch=='='){			//<=符号
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
		if(ch=='='){//>=符号
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
		if(ch=='='){//==符号
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
		if(ch=='='){//!=符号
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
		if(ch=='|'){//||符号
					syn=218;
					token[m++]=ch;			
			}
		else{
				i--;
			}break;
		case '&':m=0;token[m++]=ch;		
					ch=x[i++];
		if(ch=='&'){//&&符号
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
		case'$':syn=0;token[0]=ch;break;//结束符
		case'\n':syn=-2;break;//换行
		default: syn=-1;break;
	}
}

FILE *fp;
//出错管理选项 
void err(int n) 
{ 
	 if(n==1) 
	{
	  	fprintf(fp,"字符不匹配\n");
	  	cout<<"字符不匹配\n"<<endl;
	}
	 else if(n==2) 
	 {
	 	fprintf(fp,"字符没有出现在产生式终结符集VT中\n");
	 	cout<<"字符没有出现在产生式终结符集VT中"<<endl;	
	  } 
	 else if(n==3) 
	  {
	  	fprintf(fp,"没有找到合适的候选产生式来做进一步推导\n");
		cout<<"没有找到合适的候选产生式来做进一步推导"<<endl;
	 }
	 else  
	{
		fprintf(fp,"该句子是文法语言的句子！\n"); 
		cout<<"该句子是文法语言的句子！"<<endl;
	}
} 
 
int len(char str[]) //计算串长度 
{ 
	 int i=0; 
	 while(str[i]!='\0')
	 	i++; 
	 return i; 
} 
int index(char ch,char str[]) //找位置 
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
//打印分析结果 
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
//语法分析程序 
void syntax() 
{ 
	int n; 
	count++; //次数 
	print(); //打印结果 
	X=stack[sp]; //从文法语言中获取的字符 
	a=queue[front]; //输入串中的字符 
	while(queue[front]=='\0'&&X=='#')//消去输入串中的空，直到遇到# 
	{
		front++;
	}	
	if(X=='#'&&queue[front]=='#')//最终完成分析，##相匹配 
	{
		fprintf(fp,"acc\n");
		cout<<'\t'<<"acc"<<endl;
		f=4;	
	} 
	if((X<'A'||X>'Z')&&X!='#')      	//判断文法句中不是大写字母
	{ 
		if(X==a) 
	  	{ 
		   sp--; 				//出栈 
		   front++; 			//队列向前一位 
		   if(a!='i')        		//不与标识符匹配 
		   {  
		   	fprintf(fp,"\%c匹配\n",a);
	   		cout<<'\t'<<'\''<<a<<"匹配"<<endl;
		   } 
		   else 
		  	{  
		  		fprintf(fp,"\%c匹配\n",arr_i[r++]);
		   		cout<<'\t'<<'\''<<arr_i[r++]<<"匹配"<<endl;
		  	} 
	 	} 
	 	else 
		 	f=1;               //字符不匹配,转去出错处理 
		}
	else 					//X是非终结符中的一个 
	{ 
		 int tx=index(X,VN);	//{非终结符索引选择} 
		 int ta=index(a,VT);	//{终结符索引选择} 
		 n=M[tx][ta];       	//{产生式选择} 
		 td[t++]=M[tx][ta]; 	//{产生式选择} 
		 if(ta==-1) 			//没有找到对应的终结符 
		 { 
		 	if(a=='\0')
		 	{
		 		if(tx!=-1)
		 		{
		 			sp--; 
		 			fprintf(fp,"%c->空串\n",X);
		  			cout<<'\t'<<X<<"->"<<"空串"<<endl;
				 }
			}
			else{
				f=2;
				fprintf(fp,"%c\n",a);
		  		cout<<a<<endl; 
			}
		 }                     //字符没有出现在产生式终结符集VT中,转去出错处理 
		 else if(n==-1)
		 	f=3;  		 //没有找到合适的候选产生式来做进一步推导,转去出错处理 
		 else 			//用产生式M[tx][ta]来做进一步推导 
		 {  		 
		  	sp--; 
		  	fprintf(fp,"%c->",X);
		  	cout<<'\t'<<X<<"->";
		  	if(len(p[n])!=0) 
		  	{ 
		   		for(int i=len(p[n])-1;i>=0;i--) //反向输出产生式 
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
		  		fprintf(fp,"空串\n"); 
		  		cout<<"空串"<<endl;
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
	ifstream infile("LL(1)测试文件.txt",ios::in); //以输入方式打开文件  
        //判断是否打开成功  
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
	printf("种别码\t单词\t类别\n");
	fstream file("LL(1)语法分析.txt", ios::out);//清空文件内容 
    fstream oFile1; 
    oFile1.open("LL(1)语法分析.txt");
    oFile1<<"种别码  "<<"单词   "<<token<<" 类别  "<<endl;
	do{
		recognize();
		switch(syn)
		{
			case 400:cout<<"  "<<syn<<"  "<<num<<"    整数"<<endl;oFile1<<"  "<<syn<<"  "<<num<<"    整数"<<endl;break;   
			case -1: cout<<"无法识别!"<<endl;break;
			case -2: row1=row1++;break;//换行
			case 1:cout<<"#字符"<<endl;break;
			case 0:cout<<"分析结束"<<endl;break;
			default:
			if(300<syn&&syn<305)
			{
				cout<<"  "<<syn<<"  "<<token<<"    界符"<<endl;
				oFile1<<"  "<<syn<<"  "<<token<<"    界符"<<endl;
			} 
			if(200<syn&&syn<221)
			{
				cout<<"  "<<syn<<"  "<<token<<"    运算符"<<endl;
				oFile1<<"  "<<syn<<"  "<<token<<"    运算符"<<endl;
			 }
			if(syn==700)
			{
			  	cout<<"  "<<syn<<"  "<<token<<"    标识符"<<endl;
			  	oFile1<<"  "<<syn<<"  "<<token<<"    标识符"<<endl;
			}
			if(syn==500)
			{
				cout<<"  "<<syn<<"  "<<token<<"    字符"<<endl;
				oFile1<<"  "<<syn<<"  "<<token<<"    字符"<<endl;
			}
			if(100<syn&&syn<114) 	
			{
				cout<<"  "<<syn<<"  "<<token<<"    关键字"<<endl;
				oFile1<<"  "<<syn<<"  "<<token<<"    关键字"<<endl;
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
	 cout<<"LL(1)语法分析:"<<endl;
	 fp=fopen("LL(1)语法分析.txt","a");
	 syntax();//语法分析程序 
	 return 0;
}

