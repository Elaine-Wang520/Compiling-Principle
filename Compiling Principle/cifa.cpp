#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include <fstream>
#include <cassert>
using namespace std;
//�ʷ����� 
char x[1024],token[50];
char ch;
char str[1024];
int c=0;
int syn,i,m=0,n,row1,num=0;
char *rwtab[14]={"char","int","float","break","const","return","void","continue","do","while","if","else","for","void"};//�ؼ���
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
		for(n=0;n<14;n++)  //�ж������Ƿ�Ϊ�ؼ��� 
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
void number()//�����Ƿ�������
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
			str[c++]='g';//��ʾ0
		}
}
void delte()
{
	i=i+1;
	
	
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
	else if(ch=='/')
	{
		if(x[i++]=='/')
		{
			i+=1;
			while(x[i]!='\0'&&x[i]!='\n')
				i+=1;
		}
		else if(x[i++]=='*')  //����ǡ�/*�����͵�ע��һֱi++ֱ������'*/'
		{
			i+=1;
			int flag1=0;
			while(x[i]!='$')
			{
				if(x[i]=='*')
				{
					i+=1;
					if(x[i]=='/')
					{
						i+=1;
						flag1=1;
						break;
					}
				else 
					i+=1;
				}		
			}
		}
	 } 
	else switch(ch)   //�����ַ� 
	{
		case'<':m=0;token[m++]=ch;
					ch=x[i++];str[c++]='<';
		if(ch=='='){			//<=����
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
		if(ch=='='){//>=����
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
		if(ch=='='){//==����
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
		if(ch=='='){//!=����
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
		if(ch=='|'){//||����
					syn=218;
					token[m++]=ch;
					str[c++]='|';
			}
		else{
				i--;
			}break;
		case '&':m=0;token[m++]=ch;		
					ch=x[i++];str[c++]='&';
		if(ch=='&'){//&&����
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
		case'$':syn=0;token[0]=ch;break;//������
		case'\n':syn=-2;break;//����
		default: syn=-1;break;
	}
}
int main()
{
	i=0;
	char y[1024];
    row1=1;
	ifstream infile("test.txt",ios::in); //�����뷽ʽ���ļ�  
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
 /*   i=0;
    int j=0;
	while(y[j]!='$')
	{
		if(x[j]!=' ')
		{
			x[i++]=x[j];		
		}	
		else 
			j++;
	} 
	i--;
	x[i]='$';*/
    infile.close();  
	i=0;
	printf("�ֱ���\t����\t���\n");
	fstream file("�ʷ�����.txt", ios::out);//����ļ����� 
    fstream oFile1; 
    oFile1.open("�ʷ�����.txt");
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
		return 0;
}

