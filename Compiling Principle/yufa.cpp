#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include <fstream>
#include <cassert>
using namespace std;
int index=0;
int len;
void E();			//E->TE'
void E1();			//E'->+E|-E|空
void T();			//T->FT'
void T1();			//T'->*T|/T|%T|空
void F();			//F->(E)|G|P
void G();			//G->d|c
void P();			//P->i
void B();			//B->DB'
void B1();			//B'->||B|空
void D();			//D->HD'
void D1();			//D'->&&D|空
void H();			//H->E|!B
void A();
void Q();
void S();
void SJ();
void KZ();
void FH();
void SJ();
void FZ();
void IJB();
void IJB1();
void YJB();
void YJ();
void IFJ1();
void SM();
void ZSM();
void IYJ();
void YJB1();
void CLS();
void BLS();
void CL();
void CLB();
void CLB1();
void BLT();
void BLSB();
void DBL();
void BLSB1();
void DBL1();
void XH();
void FYJ();
void WYJ();
void DWYJ();
void XHZX();
void XHFH();
void XHZH();
void XHYJB();
void XHYJB1();
void XHI();
void XHI1();
/*void HST();
void HSM();
void HSS();
void HST();
void HSX();
void HSX1();*/

//词法分析 
char x[1024],token[50];
char ch;
char str[1024];
int c=0;
int syn,i,m=0,n,row1,num=0;
char *rwtab[15]={"char","int","float","break","const","return","void","continue","do","while","if","else","for","void","main"};//关键字
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
			token[m++]=ch;
			ch=x[i++];
		}
		token[m++]='\0';
		i--;
		if(m>1)
		{
			syn=700;
			str[c++]='i';
		}
		else if(m==1)
		{
			syn=500;
			str[c++]='c';
		}
		for(n=0;n<15;n++)  //判断它们是否为关键字 
		{
			if(strcmp(token,rwtab[n])==0)
			{
				syn=101+n;
				if(strcmp(token,"void")==0)
				{
					c-=1;
					str[c++]='v';
					str[c++]='o';
					str[c++]='i';
					str[c++]='d';
				}
				if(strcmp(token,"main")==0)
				{
					c-=1;
					str[c++]='m';
					str[c++]='a';
					str[c++]='i';
					str[c++]='n';
				}
				if(syn==102)
				{
					c-=1;
					str[c++]='i';
					str[c++]='n';
					str[c++]='t';
				}
				else if(syn==103)
				{
					c-=1;
					str[c++]='f';
					str[c++]='l';
					str[c++]='o';
					str[c++]='a';
					str[c++]='t';
				}
				else if(syn==101)
				{
					c-=1;
					str[c++]='c';
					str[c++]='h';
					str[c++]='a';
					str[c++]='r';
				}
				else if(syn==109)
				{
					c-=1;
					str[c++]='d';
					str[c++]='o';
				}
				else if(syn==110)
				{
					c-=1;
					str[c++]='w';
					str[c++]='h';
					str[c++]='i';
					str[c++]='l';
					str[c++]='e';
				}
				else if(syn==105)
				{
					c-=1;
					str[c++]='c';
					str[c++]='o';
					str[c++]='n';
					str[c++]='s';
					str[c++]='t';
				}
				else if(syn==111)
				{
					c-=1;
					str[c++]='i';
					str[c++]='f';

				}
				else if(syn==112)
				{
					c-=1;
					str[c++]='e';
					str[c++]='l';
					str[c++]='s';
					str[c++]='e';
				}
				else if(syn==113)
				{
					c-=1;
					str[c++]='f';
					str[c++]='o';
					str[c++]='r';
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
				num=num*10+ch-'0';
				ch=x[i++];
			}
			i--;
		}
		syn=400;
		str[c++]='d';
		if(num==0)
		{
			c--;
			str[c++]='g';//表示0
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
	}else if(ch=='/')
	{
		if(x[i++]=='/')
		{
			i+=1;
			while(x[i]!='\0'&&x[i]!='\n')
				i+=1;
		}
	 } 
	else switch(ch)   //其他字符 
	{
		case'<':m=0;token[m++]=ch;
					ch=x[i++];str[c++]='<';
		if(ch=='='){			//<=符号
						syn=212;
						token[m++]=ch;
						str[c++]='=';
					
					}
		else{
				syn=211;
				i--;
			}break;
		case'>':m=0;token[m++]=ch;		
					ch=x[i++];str[c++]='>';
		if(ch=='='){//>=符号
					syn=214;
					token[m++]=ch;
					str[c++]='=';
			}
		else{
				syn=213;
				i--;
			}break;
		case'=':m=0;token[m++]=ch;		
					ch=x[i++];str[c++]='=';
		if(ch=='='){//==符号
					syn=215;
					token[m++]=ch;
					str[c++]='=';
			}
		else{
				syn=219;
				i--;
			}break;
		case'!':m=0;token[m++]=ch;		
					ch=x[i++];str[c++]='!';
		if(ch=='='){//!=符号
					syn=216;
					token[m++]=ch;
					str[c++]='=';
			}
		else{
				syn=205;
				i--;
			}break;
		case'|':m=0;token[m++]=ch;		
					ch=x[i++];str[c++]='|';
		if(ch=='|'){//||符号
					syn=218;
					token[m++]=ch;
					str[c++]='|';
			}
		else{
				i--;
			}break;
		case '&':m=0;token[m++]=ch;		
					ch=x[i++];str[c++]='&';
		if(ch=='&'){//&&符号
					syn=217;
					token[m++]=ch;	
					str[c++]='&';			
			}
		else{
				i--;
			}break;
		case'.':syn=220;token[0]=ch;break;
		case'*':syn=206;token[0]=ch;str[c++]='*';break;
		case'/':syn=207;token[0]=ch;str[c++]='/';break;
		case'+':syn=209;token[0]=ch;str[c++]='+';break;
		case'-':syn=210;token[0]=ch;str[c++]='-';break;
		case'(':syn=201;token[0]=ch;str[c++]='(';break;
		case')':syn=202;token[0]=ch;str[c++]=')';break;
		case'{':syn=301;token[0]=ch;str[c++]='{';break;
		case'}':syn=302;token[0]=ch;str[c++]='}';break;
		case';':syn=303;token[0]=ch;str[c++]=';';break;
		case',':syn=304;token[0]=ch;str[c++]=',';break;
		case'#':syn=1;token[0]=ch;break;
		case'$':syn=0;token[0]=ch;break;//结束符
		case'\n':syn=-2;break;//换行
		default: syn=-1;break;
	}
}

FILE *IN,*fr; 
void E()
{
	fprintf(fr,"E中：%c \t E->TE' \n",str[index]);
	printf("E中：%c \t E->TE' \n",str[index]);
	T();
	E1();
}
void E1()
{
	fprintf(fr,"E1中：%c  E'->+E|-E|空 \n",str[index]);
	printf("E1中：%c  E'->+E|-E|空 \n",str[index]);
	if(str[index]=='+')
	{
		index++;
		if((str[index]=='d')||(str[index]=='i')||(str[index]=='c')||(str[index])=='(')
			E();
		else
		{
			fprintf(fr,"运算符后面没得操作数！\n");
			printf("运算符后面没得操作数！\n");
			exit(0);
		}
	}
	else if(str[index]=='-')
	{
		index++;
	//	printf("%c\n",str[index]);
		if((str[index]=='d')||(str[index]=='i')||(str[index]=='c'))
			E();
		else
		{
			fprintf(fr,"运算符后面没得操作数！\n");
			printf("运算符后面没得操作数！\n");
			exit(0);
		}
	}
}
void T()
{
	fprintf(fr,"T中：%c \t T->FT'\n",str[index]);
	printf("T中：%c \t T->FT'\n",str[index]);
	F();
	T1();
}
void T1()
{
	fprintf(fr,"T1中：%c  T'->*T|/T|%T|空\n",str[index]);
	printf("T1中：%c  T'->*T|/T|%T|空\n",str[index]);
	if(str[index]=='*')
	{
		index++;
		if((str[index]=='d')||(str[index]=='i')||(str[index]=='c')||(str[index]=='g'))
			T();
		else
		{
			fprintf(fr,"运算符后面没得操作数！\n");
			printf("运算符后面没得操作数！\n");
			exit(0);
		}
	}
	else if(str[index]=='/')
	{
		index++;
		if((str[index]=='d')||(str[index]=='i')||(str[index]=='c'))
			T();
		else if(str[index]=='g')
		{
			fprintf(fr,"除数不能为0！\n");
			printf("除数不能为0！\n");
			exit(0);
		}
		else
		{
			fprintf(fr,"运算符后面没得操作数！\n");
			printf("运算符后面没得操作数！\n");
			exit(0);
		}
	}
	else if(str[index]=='%')
	{
		index++;
		if((str[index]=='d')||(str[index]=='i')||(str[index]=='c'))
			T();
		else if(str[index]=='g')
		{
			fprintf(fr,"除数不能为0！\n");
			printf("除数不能为0！\n");
			exit(0);
		}
		else
		{
			fprintf(fr,"运算符后面没得操作数！\n");
			printf("运算符后面没得操作数！\n");
			exit(0);
		}
	}	
}
char FG[]={'d','c','g'};
char FP[]={'i'};
int panduan(char ch,char* data)
{
	for(int i=0;data[i]!='\0';i++)
	{
		if(ch==data[i])
			return 1;
	}
	return 0;
}
void F()
{
	fprintf(fr,"F中：%c \t F->(E)|G|i\n",str[index]);
	printf("F中：%c \t F->(E)|G|i\n",str[index]);
	if(str[index]=='(')
	{
		index++;
		E();
		if(str[index]==')')
			index++;
		else
		{
			fprintf(fr,"分析失败\n");
			printf("分析失败\n");
			exit(0);
		}
	}
	else if(panduan(str[index],FG))
		G();
	else if(panduan(str[index],FP))
		P();
}
void G()
{
	fprintf(fr,"G中：%c \t G->d|c\n",str[index]);
	printf("G中：%c \t G->d|c\n",str[index]);
	if(str[index]=='d'||str[index]=='g')
	{
		index++;
		if(str[index]=='d'||str[index]=='c'||str[index]=='i'||str[index]=='g')
		{
			fprintf(fr,"两个操作数之间没有操作符!\n");
			printf("两个操作数之间没有操作符!\n");exit(0);
		}
	}
	else if(str[index]=='c')
	{
		index++;
		if(str[index]=='d'||str[index]=='c'||str[index]=='i'||str[index]=='g')
		{
			fprintf(fr,"两个操作数之间没有操作符!\n");
			printf("两个操作数之间没有操作符!\n");exit(0);
		}
	}
	else
		{
			fprintf(fr,"分析失败！\n");
			printf("分析失败！\n");
		}
}
void P()
{
	printf("P中：%c \t P->i\n",str[index]);
	if(str[index]=='i')
	{
		index++;
		if(str[index]=='d'||str[index]=='c'||str[index]=='i'||str[index]=='g')
		{
			fprintf(fr,"两个操作数之间没有操作符!\n");
			printf("两个操作数之间没有操作符!\n");exit(0);
		}
	}
	else
		{
			fprintf(fr,"分析失败！\n");
			printf("分析失败！\n");
		}
}
void B()
{
	fprintf(fr,"B中：%c \t B->DB' \n",str[index]);
	printf("B中：%c \t B->DB' \n",str[index]);
	D();
	B1();	
}
void B1()
{
	fprintf(fr,"B1中：%c \t B'->||B|空 \n",str[index]);
	printf("B1中：%c \t B'->||B|空 \n",str[index]);
	if(str[index]=='|'&&str[index+1]=='|')
	{
		index+=2;
		B();
	}
	if((str[index]=='|'&&str[index+1]!='|')||(str[index]!='|'&&str[index+1]=='|'))
	{
		fprintf(fr,"分析失败，布尔运算符不完整!\n");
		printf("分析失败，布尔运算符不完整!\n");exit(0);
	}
}
void D()
{
	fprintf(fr,"D中：%c \t D->HD' \n",str[index]);
	printf("D中：%c \t D->HD' \n",str[index]);
	H();
	D1();
}
void D1()
{
	fprintf(fr,"D'中：%c \t D'->&&D|空 \n",str[index]);
	printf("D'中：%c \t D'->&&D|空 \n",str[index]);
	if(str[index]=='&'&&str[index+1]=='&')
	{
		index+=2;
		D();
	}
	if((str[index]=='&'&&str[index+1]!='&')||(str[index]!='&'&&str[index+1]=='&'))
	{
		fprintf(fr,"分析失败，布尔运算符不完整！\n");
		printf("分析失败，布尔运算符不完整！\n");exit(0);
	}
}
void A()
{
	E();
	Q();
	E();
}
void Q()
{	
	if(str[index]=='>'||str[index]=='<')
	{
		fprintf(fr,"在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
		printf("在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
		index++;
	}
	if(str[index]=='>')
	{
		fprintf(fr,"在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
		printf("在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
		index++;
		if(str[index]=='=')
		{
			fprintf(fr,"在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
			printf("在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
			index++;
		}	
	}
	if(str[index]=='<')
	{
		fprintf(fr,"在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
		printf("在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
		index++;
		if(str[index]=='=')
		{
			fprintf(fr,"在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
			printf("在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
			index++;
		}
		else if(str[index]=='<'||str[index]=='>')
		{
			fprintf(fr,"关系运算符错误！\n");
			printf("关系运算符错误！\n");
		}
	}
	if(str[index]=='=')
	{
		fprintf(fr,"在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
		printf("在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
		index++;
		if(str[index]=='=')
		{
			fprintf(fr,"在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
			printf("在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
			index++;
		}
		else if(str[index]=='<'||str[index]=='>')
		{
			fprintf(fr,"关系运算符错误！\n");
			printf("关系运算符错误！\n");
		}
	}
	if(str[index]=='!')
	{
		fprintf(fr,"在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
		printf("在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
		index++;
		if(str[index]=='=')
		{
			fprintf(fr,"在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
			printf("在Q中:%c Q->>|<|>=|<=|!=\n",str[index]);
			index++;
		}
		else if(str[index]=='<'||str[index]=='>')
		{
			fprintf(fr,"关系运算符错误！\n");
			printf("关系运算符错误！\n");
		}
	}
}
/*void H()
{
	fprintf(fr,"H中：%c \t H->A|!B \n",str[index]);
	printf("H中：%c \t H->A|!B \n",str[index]);
	if(str[index]=='!')
	{
		index++;
		B();
	}
	else
	{
		E();
		if(index<len)
			A();
	}
}*/
void H()
{
	fprintf(fr,"H中：%c \t H->A|!B \n",str[index]);
	printf("H中：%c \t H->A|!B \n",str[index]);
	if(str[index]=='!')
	{
		index++;
		B();
	}
	else
	{
		E();
		if(index<len)
			A();
	}
}
void C()
{
	fprintf(fr,"在C中：%c C->i=S;\n",str[index]);
	printf("在C中：%c C->i=S;\n",str[index]);
	if(str[index]=='i')
	{
		index++;
		if(str[index]=='=')
		{
			fprintf(fr,"在C中：%c C->i=S;\n",str[index]);
			printf("在C中：%c C->i=S;\n",str[index]);
			index++;
		}
	}
	S();	
	if(str[index]==';')
	{
		fprintf(fr,"在C中：%c C->i=S;\n",str[index]);
		printf("在C中：%c C->i=S;\n",str[index]);
		index++;
	}
	else
	{
		fprintf(fr,"赋值表达式结尾缺少;\n");
		printf("赋值表达式结尾缺少;\n");
	}
}
void S()
{
	if(str[index]!='e'&&str[index]!=';')
	{
		E();
		if(str[index]!=';'&&str[index]!='#')
		{
			B();
			if(str[index]!=';'&&str[index]!='#')
			C();
		}
	}
}
void ZX()
{
	if(str[index]=='i')
	{
		if(str[index+1]=='f')
		{
			KZ();
		}
		else
		{
			SJ();
		}
	}
	if((str[index]=='f'&&str[index+1]=='o')||(str[index]=='d'&&str[index+1]=='o')||(str[index]=='w'&&str[index+1]=='h'))
		KZ();
	if(str[index]=='{')
		FH();
}
void SJ()
{
	FZ();
}
void FZ()
{
	C();
}
void KZ()
{
	if(str[index]=='i'&&str[index+1]=='f')
		IYJ();
	else if(str[index]=='f'&&str[index+1]=='o')
		FYJ();
	else if(str[index]=='w'&&str[index+1]=='h')
		WYJ();
	else if(str[index]=='d'&&str[index+1]=='o')
		DWYJ();
}
void FH()
{
	fprintf(fr,"在FH中%c:FH->{YJB}\n",str[index]);
	printf("在FH中%c:FH->{YJB}\n",str[index]);
	if(str[index]=='{')
	{
		index++;
		fprintf(fr,"在FH中%c:FH->{YJB}\n",str[index]);
		printf("在FH中%c:FH->{YJB}\n",str[index]);
		YJB();
		if(str[index]='}')
		{
			fprintf(fr,"在FH中%c:FH->{YJB}\n",str[index]);
			printf("在FH中%c:FH->{YJB}\n",str[index]);
			index++;
		} 
	}
}
void YJB()
{
	YJ();
	if(str[index]=='{')
		YJB1();
}
void YJB1()
{
	YJB();
}
void S1()
{
//	if(str[index]!='e'&&str[index]!=';')
	if(str[index]!='e')
	{
		E();
		if(str[index]!='#')
		{
			B();
		}
	}
}
void IYJ()
{
	if(str[index]=='i'&&str[index+1]=='f')
	{
		fprintf(fr,"在IFY中%c%c:IFJ->if(S)YJ|if(S)YJelseYJ\n",str[index],str[index+1]);
		printf("在IFY中%c%c:IFJ->if(S)YJ|if(S)YJelseYJ\n",str[index],str[index+1]);
		index+=2;
		if(str[index]=='(')
		{
			fprintf(fr,"在IFY中%c:IFJ->if(S)YJ|if(S)YJelseYJ\n",str[index]);
			printf("在IFY中%c:IFJ->if(S)YJ|if(S)YJelseYJ\n",str[index]);
			index++;
			S1();
			if(str[index]==')')
			{
				fprintf(fr,"在IFY中%c:IFJ->if(S) YJ|if(S) YJ else YJ\n",str[index]);
				printf("在IFY中%c:IFJ->if(S) YJ|if(S) YJ else YJ\n",str[index]);
				index++;
				YJ();
				IFJ1();
			}
			else
			{
				fprintf(fr,"if语句不完整，缺少)\n");
				printf("if语句不完整，缺少)\n");exit(0);
			}
		}
	}
}
void IFJ1()
{
	if(str[index]=='e'&&str[index+1]=='l'&&str[index+2]=='s'&&str[index+3]=='e')
	{
		fprintf(fr,"在IFY1中else :IFY1->if(S) YJ|if(S) YJ else YJ\n");
		printf("在IFY1中else :IFY1->if(S) YJ|if(S) YJ else YJ\n");
		index+=4;
		YJ();
	}
}
void FYJ()
{
	if(str[index]=='f'&&str[index+1]=='o'&&str[index+2]=='r')
	{
		fprintf(fr,"在FYJ中%c%c%c:FYJ->for(S;S;S)XH\n",str[index],str[index+1],str[index+2]);
		printf("在FYJ中%c%c%c:FYJ->for(S;S;S)XH\n",str[index],str[index+1],str[index+2]);
		index+=3;
		if(str[index]=='(')
		{
			fprintf(fr,"在FYJ中%c:FYJ->for(S;S;S)XH\n",str[index]);
			printf("在FYJ中%c:FYJ->for(S;S;S)XH\n",str[index]);
			index++;
			S1();
			if(str[index]==';')
			{
				fprintf(fr,"在FYJ中%c:FYJ->for(S;S;S)XH\n",str[index]);
				printf("在FYJ中%c:FYJ->for(S;S;S)XH\n",str[index]);
				index++;
				S1();
				if(str[index]==';')
				{
					fprintf(fr,"在FYJ中%c:FYJ->for(S;S;S)XH\n",str[index]);
					printf("在FYJ中%c:FYJ->for(S;S;S)XH\n",str[index]);index++;
					S1();
					if(str[index]==')')
					{
						fprintf(fr,"在FYJ中%c:FYJ->for(S;S;S)XH\n",str[index]);
						printf("在FYJ中%c:FYJ->for(S;S;S)XH\n",str[index]);index++;
						XH();
					}
					else
					{
						fprintf(fr,"for语句不完整，缺少)\n");
						printf("for语句不完整，缺少)\n");exit(0);
					}
				}
				else
				{
					fprintf(fr,"for语句不完整，缺少循环往后的条件\n");
					printf("for语句不完整，缺少循环往后的条件\n");exit(0);
				}
			}
			else
			{
				fprintf(fr,"for语句不完整\n");
				printf("for语句不完整\n");exit(0);
			}
		}
	}
}
void WYJ()
{
	if(str[index]=='w'&&str[index+1]=='h'&&str[index+2]=='i'&&str[index+3]=='l'&&str[index+4]=='e')
	{
		fprintf(fr,"在WYJ中while :WYJ->while(s)XH\n");
		printf("在WYJ中while :WYJ->while(s)XH\n");
		index+=5;
		if(str[index]=='(')
		{
			fprintf(fr,"在WYJ中%c:WYJ->while(s)XH\n",str[index]);
			printf("在WYJ中%c:WYJ->while(s)XH\n",str[index]);
			index++;
			S1();
			if(str[index]==')')
			{
				fprintf(fr,"在WYJ中%c:WYJ->while(s)XH\n",str[index]);
				printf("在WYJ中%c:WYJ->while(s)XH\n",str[index]);
				index++;
				XH();
			}
			else
			{
				fprintf(fr,"while语句不完整，缺少)\n");
				printf("while语句不完整，缺少)\n");exit(0);
			}
		}
	}
}
void DWYJ()
{
	if(str[index]=='d'&&str[index+1]=='o')
	{
		fprintf(fr,"在DWYJ中do :DWYJ->doXHFHwhile(s);\n");
		printf("在DWYJ中do :DWYJ->doXHFHwhile(s);\n");
		index+=2;
		XHFH();
		if(str[index]=='w'&&str[index+1]=='h'&&str[index+2]=='i'&&str[index+3]=='l'&&str[index+4]=='e')
		{
			fprintf(fr,"在DWYJ中while :DWYJ->doXHFHwhile(s);");
			printf("在DWYJ中while :DWYJ->doXHFHwhile(s);");index+=5;
			if(str[index]=='(')
			{
				fprintf(fr,"在DWYJ中%c :DWYJ->doXHFHwhile(s);\n",str[index]);
				printf("在DWYJ中%c :DWYJ->doXHFHwhile(s);\n",str[index]);index++;
				S1();
				if(str[index]==')')
				{
					fprintf(fr,"在DWYJ中%c :DWYJ->doXHFHwhile(s);\n",str[index]);
					printf("在DWYJ中%c :DWYJ->doXHFHwhile(s);\n",str[index]);index++;
					if(str[index]==';')
					{
						fprintf(fr,"在DWYJ中%c :DWYJ->doXHFHwhile(s);\n",str[index]);
						printf("在DWYJ中%c :DWYJ->doXHFHwhile(s);\n",str[index]);index++;
					}
					else
					{
						fprintf(fr,"在dowhile循环中缺少;\n",str[index]);
						printf("在dowhile循环中缺少;\n",str[index]);exit(0);
					}
				}
				else
				{
					fprintf(fr,"do while语句不完整，缺少)\n");
					printf("do while语句不完整，缺少)\n");exit(0);
				}
			}
		}
	}
}
void XH()
{
	if(str[index]=='{')
		XHFH();
	else if((str[index]=='i'&&str[index+1]=='f')||(str[index]=='f'&&str[index+1]=='o')||(str[index]=='w'&&str[index+1]=='h')||(str[index]=='d'&&str[index+1]=='o'))
		XHZX();
	else
		SM();
}
void XHZX()
{
	if(str[index]=='i'&&str[index+1]=='f')
		XHI();
	else if(str[index]=='f'&&str[index+1]=='o')
		FYJ();
	else if(str[index]=='w'&&str[index+1]=='h')
		WYJ();
	else if(str[index]=='d'&&str[index+1]=='o')
		DWYJ();

}
void XHFH()
{
	if(str[index]=='{')
	{
		fprintf(fr,"在XHFH中%c:XHFH->{XHYJB}\n",str[index]);
		printf("在XHFH中%c:XHFH->{XHYJB}\n",str[index]);index++;
		XHYJB();
		if(str[index]=='}')
		{
			fprintf(fr,"在XHFH中%c:XHFH->{XHYJB}\n",str[index]);
			printf("在XHFH中%c:XHFH->{XHYJB}\n",str[index]);index++;
		}	
		else
		{
			fprintf(fr,"循环语句不完整，缺少}\n");
			printf("循环语句不完整，缺少}\n");exit(0);
		}
	}
}
void XHYJB()
{
	XH();
	if(str[index]!='}')
		XHYJB();
}
void XHI()
{
	if(str[index]=='i'&&str[index+1]=='f')
	{
		fprintf(fr,"在XHI中if :XHI->if(S)XHXHI'\n");
		printf("在XHI中if :XHI->if(S)XHXHI'\n");
		index+=2;
		if(str[index]=='(')
		{
			fprintf(fr,"在XHI中%c :XHI->if(S)XHXHI'\n",str[index]);
			printf("在XHI中%c :XHI->if(S)XHXHI'\n",str[index]);
			index++;
			S1();
			if(str[index]==')')
			{
				fprintf(fr,"在XHI中%c :XHI->if(S)XHXHI'\n",str[index]);
				printf("在XHI中%c :XHI->if(S)XHXHI'\n",str[index]);
				index++;
				XH();
				XHI1();
			}
		}
	}
}
void XHI1()
{
	if(str[index]=='e'&&str[index+1]=='l'&&str[index+2]=='s'&&str[index+3]=='e')
	{
		fprintf(fr,"在XHI'中else :XHI'->elseXH\n");
		printf("在XHI'中else :XHI'->elseXH\n");
		index+=4;
		XH();
	}
}

void YJ()
{
	if((str[index]=='c'&&str[index+1]=='o')||(str[index]=='i'&&str[index+1]=='n'))
	{
		SM();
		YJ();
	}
	else
	{
		ZX();		
	}
	
}
/*void SM()
{
	int flag=0;
	int k=index;
//	while(str[k]!=';')
	while(str[k]!=';')
	{
		if(str[k]=='=')
		{
			flag=1;
			break; 
		}
		k++;
	}
	if(str[index]=='c'&&str[index+1]=='o')
		ZSM();	
	if(flag==1)
		ZSM();	
	if(str[index]=='v'||flag==0)
		HSS();
}*/
void SM()
{
	
	ZSM();	
	
}
void ZSM()
{
//	printf("%c%c\n",str[index],str[index+1]);
	if(str[index]=='c'&&str[index+1]=='o')
		CLS();
	else
	{
		BLS();
	}	
}
void CLS()
{
	if(str[index]=='c'&&str[index+1]=='o'&&str[index+2]=='n'&&str[index+3]=='s'&&str[index+4]=='t')
	{
		fprintf(fr,"在CLS中%c%c%c%c%c: CLS->constCLCLB\n",str[index],str[index+1],str[index+2],str[index+3],str[index+4]);
		printf("在CLS中%c%c%c%c%c: CLS->constCLCLB\n",str[index],str[index+1],str[index+2],str[index+3],str[index+4]);
		index+=5;
		CL();
		CLB();
	}
	else
	{
		fprintf(fr,"常量声明const出错！\n");
		printf("常量声明const出错！\n");
	}
}
void CL()
{
	if(str[index]=='i'&&str[index+1]=='n'&&str[index+2]=='t')
	{
		fprintf(fr,"在CL中%c%c%c: CL->int|char|float\n",str[index],str[index+1],str[index+2]);
		printf("在CL中%c%c%c: CL->int|char|float\n",str[index],str[index+1],str[index+2]);
		index+=3;
	}
	if(str[index]=='c'&&str[index+1]=='h'&&str[index+2]=='a'&&str[index+3]=='r')
	{
		fprintf(fr,"在CL中%c%c%c%c: CL->int|char|float\n",str[index],str[index+1],str[index+2],str[index+3]);
		printf("在CL中%c%c%c%c: CL->int|char|float\n",str[index],str[index+1],str[index+2],str[index+3]);
		index+=4;
	}
	if(str[index]=='f'&&str[index+1]=='l'&&str[index+2]=='o'&&str[index+3]=='a'&&str[index+4]=='t')
	{
		fprintf(fr,"在CL中%c%c%c%c%c: CL->int|char|float\n",str[index],str[index+1],str[index+2],str[index+3],str[index+4]);
		printf("在CL中%c%c%c%c%c: CL->int|char|float\n",str[index],str[index+1],str[index+2],str[index+3],str[index+4]);
		index+=5;
	}
	else
	{
		fprintf(fr,"常量类型出错!\n");
		printf("常量类型出错!\n");
	}

}
void CLB()
{
	if(str[index]=='i')
	{
		fprintf(fr,"在CLB中%c  :CLB->i=dCLB'\n",str[index]);
		printf("在CLB中%c  :CLB->i=dCLB'\n",str[index]);
		index++;
		if(str[index]=='=')
		{
			fprintf(fr,"在CLB中%c  :CLB->i=dCLB'\n",str[index]);
			printf("在CLB中%c  :CLB->i=dCLB'\n",str[index]);
			index++;
			if(str[index]=='d')
			{
				fprintf(fr,"在CLB中%c  :CLB->i=dCLB'\n",str[index]);
				printf("在CLB中%c  :CLB->i=dCLB'\n",str[index]);
				index++;
				CLB1();
			}
			else
			{
				fprintf(fr,"标识符定义出错！\n");
				printf("标识符定义出错！\n");exit(0);
			}
		}
		else
		{
			fprintf(fr,"常量定义后面缺少赋值运算符:=！\n");
			printf("常量定义后面缺少赋值运算符:=！\n");
		}
	}
}
void CLB1()
{
	if(str[index]==';')
	{
		fprintf(fr,"在CLB'中%c:  CLB'->;|,CLB\n",str[index]);
		printf("在CLB'中%c:  CLB'->;|,CLB\n",str[index]);
		index++;
	}
	else if(str[index]==',')
	{
		fprintf(fr,"在CLB'中%c:  CLB'->;|,CLB\n",str[index]);
		printf("在CLB'中%c:  CLB'->;|,CLB\n",str[index]);
		index++;
		CLB();
	}
	else
	{
		fprintf(fr,"常量定义缺少结束字符;!\n");
		printf("常量定义缺少结束字符;!\n");
	}	
}
void BLS()
{
	if((str[index]=='i'&&str[index+1]=='n')||(str[index]=='c'&&str[index+1]=='h')||(str[index]=='f'&&str[index+1]=='l'))
	{
		BLT();
	}
	BLSB();
}
void BLSB()
{
	DBL();
	BLSB1();
}
void BLSB1()
{
//	printf("%c\n",str[index]);
	if(str[index]==';')
	{
		fprintf(fr,"在BLSB'中%c: BLSB'->;|,BLSB\n",str[index]);
		printf("在BLSB'中%c: BLSB'->;|,BLSB\n",str[index]);
		index++;
	}
	else if(str[index]==',')
	{
		fprintf(fr,"在BLSB'中%c: BLSB'->;|,BLSB\n",str[index]);
		printf("在BLSB'中%c: BLSB'->;|,BLSB\n",str[index]);
		index++;
		BLSB();
	}
/*	else
	{
		printf("变量定义缺少结束字符;!\n");
	}*/
}
/*void DBL()
{
	H();
	DBL1();
}
void DBL1()
{
	if(str[index]=='=')
	{
		fprintf(fr,"在DBL1'中%c: DBL1'->=S\n",str[index]);
		printf("在DBL1'中%c: DBL1'->=S\n",str[index]);
		index++;
	}
}*/
void DBL()
{
	if(str[index]=='i'&&str[index+1]!='n')
	{
		fprintf(fr,"在DBL中%c: DBL->i|i=S\n",str[index]);
		printf("在DBL中%c: DBL->i|i=S\n",str[index]);
		index+=1;
		if(str[index]=='=')
		{
			fprintf(fr,"在DBL中%c: DBL->i|i=S\n",str[index]);
			printf("在DBL中%c: DBL->i|i=S\n",str[index]);
			index+=1;
			S();	
		}
	 } 
}
void BLT()
{
	int flag=0;
	if(str[index]=='i'&&str[index+1]=='n'&&str[index+2]=='t')
	{
		flag=1;
		fprintf(fr,"在BLT中%c%c%c: BLT->int|char|float\n",str[index],str[index+1],str[index+2]);
		printf("在BLT中%c%c%c: BLT->int|char|float\n",str[index],str[index+1],str[index+2]);
		index+=3;
	}
	if(str[index]=='c'&&str[index+1]=='h'&&str[index+2]=='a'&&str[index+3]=='r')
	{
		flag=1;
		fprintf(fr,"在BLT中%c%c%c%c: BLT->int|char|float\n",str[index],str[index+1],str[index+2],str[index+3]);
		printf("在BLT中%c%c%c%c: BLT->int|char|float\n",str[index],str[index+1],str[index+2],str[index+3]);
		index+=4;
	}
	if(str[index]=='f'&&str[index+1]=='l'&&str[index+2]=='o'&&str[index+2]=='a'&&str[index+2]=='t')
	{
		flag=1;
		fprintf(fr,"在BLT中%c%c%c%c%c: BLT->int|char|float\n",str[index],str[index+1],str[index+2],str[index+3],str[index+4]);
		printf("在BLT中%c%c%c%c%c: BLT->int|char|float\n",str[index],str[index+1],str[index+2],str[index+3],str[index+4]);
		index+=5;
	}
	if(flag==0)
	{
		fprintf(fr,"变量类型出错！\n");
		printf("变量类型出错！\n");
	}
}

/*void HSS()
{
	HST();
	if(str[index]=='i')
	{
		fprintf(fr,"在HSS中%c: HSS->HSTi(HSM)i;\n",str[index]);
		printf("在HSS中%c: HSS->HSTi(HSM)i;\n",str[index]);
		index++;
		if(str[index]=='(')
		{
			fprintf(fr,"在HSS中%c: HSS->HSTi(HSM)i;\n",str[index]);
			printf("在HSS中%c: HSS->HSTi(HSM)i;\n",str[index]);
			index++;
			HSM();
			if(str[index]==')')
			{
				fprintf(fr,"在HSS中%c: HSS->HSTi(HSM)i;\n",str[index]);
				printf("在HSS中%c: HSS->HSTi(HSM)i;\n",str[index]);
				index++;
				if(str[index]==';')
				{
					fprintf(fr,"在HSS中%c: HSS->HSTi(HSM)i;\n",str[index]);
					printf("在HSS中%c: HSS->HSTi(HSM)i;\n",str[index]);
					index++;
				}
		}
	}
	}
}
void HST()
{
	if(str[index]=='i'&&str[index+1]=='n'&&str[index+2]=='t')
	{
		fprintf(fr,"在HST中%c%c%c: HSTL->int|char|float|void\n",str[index],str[index+1],str[index+2]);
		printf("在HST中%c%c%c: HSTL->int|char|float|void\n",str[index],str[index+1],str[index+2]);
		index+=3;
	}
	if(str[index]=='c'&&str[index+1]=='h'&&str[index+2]=='a'&&str[index+3]=='r')
	{
		fprintf(fr,"在HST中%c%c%c%c: HST->int|char|float|void\n",str[index],str[index+1],str[index+2],str[index+3]);
		printf("在HST中%c%c%c%c: HST->int|char|float|void\n",str[index],str[index+1],str[index+2],str[index+3]);
		index+=4;
	}
	if(str[index]=='f'&&str[index+1]=='l'&&str[index+2]=='o'&&str[index+2]=='a'&&str[index+2]=='t')
	{
		fprintf(fr,"在HST中%c%c%c%c%c: HST->int|char|float|void\n",str[index],str[index+1],str[index+2],str[index+3],str[index+4]);
		printf("在HST中%c%c%c%c%c: HST->int|char|float|void\n",str[index],str[index+1],str[index+2],str[index+3],str[index+4]);
		index+=5;
	}
	if(str[index]=='v'&&str[index+1]=='o'&&str[index+2]=='i'&&str[index+3]=='d')
	{
		fprintf(fr,"在HST中%c%c%c%c: HST->int|char|float|void\n",str[index],str[index+1],str[index+2],str[index+3]);
		printf("在HST中%c%c%c%c: HST->int|char|float|void\n",str[index],str[index+1],str[index+2],str[index+3]);
		index+=4;
	}
	else
	{
		printf("函数类型出错！\n");exit(0);
	}
}
void HSM()
{
	HSX();
}
void HSX()
{
	BLT();
	HSX1();
}
void HSX1()
{
	if(str[index]==',')
	{
		fprintf(fr,"在HSX中%c:HSX->BLT|BLT,HSX");
		printf("在HSX中%c:HSX->BLT|BLT,HSX");
		index++;
		HSX();
	}
}*/
int main()
{
	i=0;
    row1=1;
	ifstream infile("test.txt",ios::in); //以输入方式打开文件  
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
	fstream file("词法分析.txt", ios::out);//清空文件内容 
    fstream oFile1; 
    oFile1.open("词法分析.txt");
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
		printf("形成的语法句子为：%s\n",str);
		len=strlen(str);
		str[len]='#';
		printf("******************************\n");
		printf("语法分析过程如下：\n");
		//语法分析
		fr=fopen("语法分析.txt","w");
		if(str[index]=='+'||str[index]=='-'||str[index]=='*'||str[index]=='/'||str[index]=='%')
		{
				printf("操作符前面没有运算符！\n");
				exit(0);
		}
		if(str[index]=='v'&&str[index+1]=='o'&&str[index+2]=='i'&&str[index+3]=='d')
		{
			index+=4;
			if(str[index]=='m'&&str[index+1]=='a'&&str[index+2]=='i'&&str[index+3]=='n')
			{
				index+=4;
				if(str[index]=='('&&str[index+1]==')')
				{
					index+=2;
					if(str[index]=='{')
					{
						index+=1;
						YJ();
						if(str[index]=='}')
						{
							printf("语法分析结束\n");
						}
					}
				}
			}
		}
		return 0;
}

