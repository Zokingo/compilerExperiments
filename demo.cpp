////////////////////////////////////////////////////////////////
//** Author: 钟琴
//** Date:[11/7/2016]
//** Version:1.0.0
//** Description:
/*
语法分析：LL(1)方法
eg:
correct:
a=((b+c)*d-e/f)*2
q=((x*x)+w-(y/y-e))*r
x=(a+b)*(88.4-4)
wrong:
a=(sd*5)))
*/
////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stack>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int s_main();
#define MAX 100 
void s_SET_Mul_Div(int i, int m);
void s_SET_Add_Sub(int j, int m);
void s_print();
int s_m = 0;
int s_count = 0;
char s_tempvar = 'A';
int s_temp;
char s_string[MAX];//用于存放表达式


char  f1[10] = { "E->Te" };//1
char  f2[10] = { "e->WTe" };//2，遇到W执行+或者-
char  f3[10] = { "e->0" };//3
char  f4[10] = { "T->Ft" };//4
char  f5[10] = { "t->wFt" };//5，遇到w执行*或者/
char  f6[10] = { "t->0" };//6
char  f7[10] = { "F->I" };//7
char  f8[10] = { "F->(E)" };//8
char  f9[15] = { "WRONG" };//9




char			*t;
string			mystring;
stack<char>		mystack;

int				tool;
char			symbol = '#';
char			*user;

char *Map[] = { "int", "main", "void", "if", "else", "char" };
int p, m, syn;//syn是对应的token 关键数字
char ch;
char huancun2[200];             //huancun2是输入的句子的一个特例：		（“((Aa+Bb)*(78.3+2))#&”）
char huancun3[30] = { "sdsd" }; //huancun3是相应输入算术表达式的句子泛型：（“((IWI)w(IWI))#”）
char *now = huancun3;			//当前句子内容

//stack<char> sem_stack;//语义栈（根据huancun3内容进行操作，然后根据huancun2得到内容输出）

char token[8];
int sum1, sum2;
void exchange();
int scanner();
void administrator();
char* decode(char first, char next);
void action();
void first();
void File();
void exchange();
void sem_analysis();

//语义分析
/*void sem_analysis(char op)
{
	if (sem_stack.size()>=2)
	{
		//cout << "进入语义栈函数调用" << endl;
		char a = sem_stack.top();
		sem_stack.pop();
		char b = sem_stack.top();
		sem_stack.pop();
		char t = 'x';
		cout << "\t\t\t\t(" << op << "," << a << "," << b << "," << t << ")" << endl;
		sem_stack.push(t);//把新元素压栈
		return;
	}
	else
	{
		cout << "\t\t语义栈内的元素个数：" << sem_stack.size() << endl;
		return;
	}
}*/

//词法分析
int scanner()
{
	m = 0;
	sum1 = 0;
	sum2 = 0;
	for (int i = 0; i <= 7; i++)
	{
		token[i] = '\0';
	}
	ch = huancun2[p];
	p++;
	while (ch == '\n' || ch == ' ' || ch == ' ')
	{
		ch = huancun2[p++];
	}
	if (ch == '\'')
	{
		m = 0;
		ch = huancun2[p];
		p++;
		token[m] = ch;
		m++;
		ch = huancun2[p];
		if (ch == '\'')
		{
			p++;
			ch = huancun2[p];
		}
		token[m] = '\0';
		ch = huancun2[p];
		p++;
		syn = 1;
		return 0;
	}
	else if (ch == '\"')
	{
		m = 0;
		ch = huancun2[p];
		p++;
		token[m] = ch;
		m++;
		ch = huancun2[p];
		if (isalpha(ch) && (ch != '\"'))
		{
			ch = huancun2[p++];
			token[m++] = ch;
		}
		token[m] = '\0';
		ch = huancun2[p];
		p++;
		syn = 2;
		return 0;
	}
	else if ((isalpha(ch)) && (ch != '\"') && (ch != '\'')) 
	{
		while (isdigit(ch) || isalpha(ch))
		{
			token[m++] = ch;
			ch = huancun2[p++];
		}
		token[m++] = '\0';
		ch = huancun2[p--];
		syn = 0;
		for (int i = 0; i < 6; i++)
		{
			if (strcmp(token, Map[i]) == 0)
			{
				syn = i + 4;
				break;
			}
		}
		return 0;
	}
	else if (isdigit(ch))
	{
		while (isdigit(ch))
		{
			sum1 = sum1 * 10 + ch - '0';
			ch = huancun2[p++];
		}
		if (ch == '.')
		{
			ch = huancun2[p++];
			while (isdigit(ch)) 
			{
				sum2 = sum2 * 10 + ch - '0';
				ch = huancun2[p++];
			}
		}
		ch = huancun2[p--];
		syn = 3;
		return 0;
	}
	else  if (isalpha(ch)) 
	{
		while (isalpha(ch) && ch != ' '&&ch != '\0')
		{
			token[m++] = ch;
			ch = huancun2[p++];
		}
		token[m++] = '\0';
		ch = huancun2[p--];
		syn = 2;
		return 0;
	}
	else
		switch (ch)
	{
		case '<':
			m = 0;
			token[m++] = ch;
			ch = huancun2[p++];
			if (ch == '=')
			{
				syn = 11;
				token[m++] = ch;
			}
			else
			{
				syn = 15;
				ch = huancun2[p--];
			}
			break;
		case '>':
			m = 0;
			token[m++] = ch;
			ch = huancun2[p++];
			if (ch == '=')
			{
				syn = 14;
				token[m++] = ch;
			}
			else
			{
				syn = 10;
				ch = huancun2[p--];
			}
			break;
		case '=':
			m = 0;
			token[m++] = ch;
			ch = huancun2[p++];
			if (ch == '=')
			{
				syn = 12;
				token[m++] = ch;
			}
			else
			{
				syn = 13;
				ch = huancun2[p--];
			}
			break;
		case '*':
			m = 0;
			syn = 18;
			token[m] = ch;
			m++;
			break;
		case '+':
			m = 0;
			syn = 16;
			token[m++] = ch;
			break;
		case '-':
			m = 0;
			syn = 17;
			token[m++] = ch;
			break;
		case '/':
			m = 0;
			syn = 19;
			token[m++] = ch;
			break;
		case '(':
			m = 0;
			syn = 24;
			token[m] = ch;
			m++;
			break;
		case '[':
			m = 0;
			syn = 27;
			token[m++] = ch;
			break;
		case ']':
			m = 0;
			syn = 28;
			token[m++] = ch;
			break;
		case ',':
			m = 0;
			syn = 29;
			token[m++] = ch;
			break;
		case ')':
			m = 0;
			syn = 25;
			token[m++] = ch;
			break;
		case '{':
			m = 0;
			syn = 20;
			token[m++] = ch;
			break;
		case '}':
			m = 0;
			syn = 21;
			token[m++] = ch;
			break;
		case ';':
			m = 0;
			syn = 23;
			token[m++] = ch;
			break;
		case '#':
			m = 0;
			syn = 100;
			token[m++] = ch;
			break;
	}
	return 0;
}

//将词法分析得到的结果token转成相应的文法内容Vn或者Vt;
void exchange()
{
	char *now1 = huancun3;//huancun3是相应的句子
	int i = 0;
	int p;
	while (1)
	{
		p = scanner();
		if (syn == 0 || syn == 3)
		{
			huancun3[i] = 'I';
			i++;
		}
		else if (syn == 16 || syn == 17)
		{
			huancun3[i] = 'W';
			i++;
		}
		else if (syn == 18 || syn == 19)
		{
			huancun3[i] = 'w';
			i++;
		}
		else if (syn == 24)
		{
			huancun3[i] = '(';
			i++;

		}
		else if (syn == 25)
		{
			huancun3[i] = ')';
			i++;
		}
		else if (syn == 100)
		{
			huancun3[i] = '#';
			return;
		}
	}
	return;
}

//调用词法分析器函数
void administrator()
{
	p = 0;
	int i = 0;
	while (syn != 100)
	{
		scanner();
		switch (syn) 
		{
		case 3://处理常数表
			i++;
			while (i == 5)
			{
				cout << endl;
				i = 0;
			}
			cout << '(' << sum1 << '.' << sum2 << ',' << syn << ')' << "  "; break;
		default://处理关键字和变量表
			i++;
			while (i == 5)//输出超过五个就换行
			{
				cout << endl;
				i = 0;
			}
			cout << '(' << token << ',' << syn << ')' << "  "; break;
		}
	}
	return;
}
//函数调用部分
void action()
{
	if (mystack.top() == *now)//如果栈顶==当前符
	{
		cout << "出栈\t" << mystack.top() << "\t当前符=" << *now<<endl;
		mystack.pop();
		now++;//读下一个符号
		return;
	}
	else 
	{
		if ((decode(mystack.top(), *now)) == f9)
		{
			cout << "WRONG" << endl;
			exit(-1);
			return;
		}
		else
		{
			string mystring(decode(mystack.top(), *now));  //将得到的对应产生式右部赋给mystring;
			if (*(decode(mystack.top(), *now) + 3) == '0')//如果产生式为空，直接执行弹栈操作
			{
				cout << "出栈\t" << mystack.top() << "\t当前符=" << *now<<endl;
				mystack.pop();
				return;
			}
			else 
			{
				user = decode(mystack.top(), *now);//根据当前符号以及栈顶得到的产生式
				t = decode(mystack.top(), *now) + mystring.length() - 1;
				cout << "出栈\t" << mystack.top() << endl;//先把栈顶弹掉
				mystack.pop();
				cout << "压栈\t";
				int num_t = 0;
				while ((*t) != '>')//将右部产生式逆序入栈,'>'是分界符
				{
					mystack.push(*t);
					t--;
					num_t++;
					cout << mystack.top();
				}
				if (num_t==3)
				{
					cout << "\t当前符=" << *now << "\t表达式=" << user << endl;//输出这个操作完后剩下的当前符号以及前面对应操作的产生式
				}
				else
				{
					cout << "\t当前符=" << *now << "\t表达式=" << user<<endl ;//输出这个操作完后剩下的当前符号以及前面对应操作的产生式
				}
				return;
			}
			return;
		}
	}
}
//根据当前符号以及栈顶元素确定对应的产生式
char* decode(char first, char next)
{
	if (first == 'E')
	{
		if (next == 'I')
		{
			return f1;
		}
		else if (next == '(')
		{
			return f1;
		}
		else
			return f9;
	}
	else if (first == 'e')
	{
		if (next == 'W')
		{
			return f2;
		}
		else if (next == ')')
		{
			return f3;
		}
		else if (next == '#')
		{
			return f3;
		}
		else 
		{
			return f9;
		}
	}
	else if (first == 'T')
	{
		if (next == 'I')
		{
			return f4;
		}
		else if (next == '(')
		{
			return f4;
		}
		else
		{
			return f9;
		}

	}
	else if (first == 't')
	{
		if (next == 'W')
		{
			return f6;
		}
		else if (next == 'w')
		{
			return f5;
		}
		else if (next == ')') 
		{
			return f6;
		}
		else if (next == '#')
		{
			return f6;
		}
		else 
		{
			return f9;
		}
	}
	else if (first == 'F')
	{
		if (next == 'I')
		{
			return f7;
		}
		else if (next == '(')
		{
			return f8;
		}
		else
			return f9;
	}
	else
	{
		return f9;
	}
}
//LL1分析法主调函数   
void first()
{
	mystack.push('#');
	mystack.push('E');
	cout << "\n栈操作" << "\t" <<"元素\t" <<"当前符" << " \t\t" << "表达式" << endl;
	char *now = huancun3;
	while ((mystack.top() != '#') && (*now != '#'))//栈顶符号不为#且当前符号不等与#
	{
		action();
	}
	cout << "*******************************************" << endl;
	cout << "RIGHT" << endl;
	return;
}
//文件操作函数
void File()
{
	ifstream infile;
	infile.open("E:\code.txt", ios::in);
	if (infile.fail())
	{
		cout << "失败" << endl;
		return;
	}
	while (!infile.eof())
	{//文件没有结束则继续读取.
		infile.getline(huancun3, 200, '@');
		infile >> huancun3;
	}
	cout << huancun3 << endl;
	return;
}

int main()
{
	m = 0;
	p = 0;
	ifstream infile;
	infile.open("E:\code.txt", ios::in);
	if (infile.fail())
	{
		cout << "文件解析出错" << endl;
		return 0;
	}
	int n = 0;
	while (!infile.eof())
	{//文件没有结束则继续读取.
		infile.getline(huancun2, 300, '&');
		infile >> huancun2;
		//strcpy(s_string, huancun2);
		huancun2[0] = '(';
	}
	cout << huancun2<<endl;//输入的例子


	administrator();//调用词法分析器函数
	m = 0;
	p = 0;
	n = 0;
	exchange();//将词法分析得到的结果token转成相应的文法内容Vn或者Vt;得到的内容是文法产生的一个句子
	cout << endl<<huancun3;//经过变化得到的对应的一个句子
	infile.close();
	sem_analysis();

	first();//LL1分析入口函数
	return 0;
}
//语义分析
int s_main()
{
	int s_p[MAX];//
	char s_ch;
	int s_c = -1, s_q = 0;
	printf("enter expression:");
	while ((s_ch = getchar()) != '\n')
	{
		s_string[s_m++] = s_ch;
		if (s_ch == '=' || s_ch == '+' || s_ch == '-' || s_ch == '*' || s_ch == '/')
			s_count++;
		else if (s_ch == '(')
		{
			s_p[++s_c] = s_m - 1;
		}
		else if (s_ch == ')')
		{
			s_q = s_m - 1;
			s_SET_Mul_Div(s_p[s_c], s_q);//从左括号处理到右括号，先乘除
			s_SET_Add_Sub(s_p[s_c], s_q);//后加减
			s_temp = (int)s_tempvar - 1;
			s_tempvar = (char)s_temp;
			s_string[s_p[s_c]] = s_string[s_m - 1] = s_tempvar;
			s_c--;
			s_temp = (int)s_tempvar + 1;
			s_tempvar = (char)s_temp;
		}
	}
	/********调用生成四元式的函数********/
	s_print();//不在括号里的用print操作处理，依旧先乘除后加减，再赋值操作
	/*********判断是否成功**********/
	if (s_count == 0) //所有的式子都分析出来了
		printf("successful\n");
	else
		printf("failed\n");
	return 0;
}
void sem_analysis()
{
	int s_p[MAX];//
	char s_ch;
	int s_c = -1, s_q = 0;
	cout << endl <<"——————————四元式生成序列————————" << endl;
	strcpy(s_string,huancun2);
	//cin >> s_string;
	cout << s_string << endl;
	//s_string 赋值有问题
	while (s_string[s_m]!='#')
	{
		s_ch = s_string[s_m++];
		if (s_ch == '=' || s_ch == '+' || s_ch == '-' || s_ch == '*' || s_ch == '/')
			s_count++;
		else if (s_ch == '(')
		{
			s_p[++s_c] = s_m - 1;
		}
		else if (s_ch == ')')
		{
			s_q = s_m - 1;
			s_SET_Mul_Div(s_p[s_c], s_q);//从左括号处理到右括号，先乘除
			s_SET_Add_Sub(s_p[s_c], s_q);//后加减
			s_temp = (int)s_tempvar - 1;
			s_tempvar = (char)s_temp;
			s_string[s_p[s_c]] = s_string[s_m - 1] = s_tempvar;
			s_c--;
			s_temp = (int)s_tempvar + 1;
			s_tempvar = (char)s_temp;
		}
		
	}
	//while ((s_ch = getchar()) != '\n')
	//{
	//	s_string[s_m++] = s_ch;
	//	if (s_ch == '=' || s_ch == '+' || s_ch == '-' || s_ch == '*' || s_ch == '/')
	//		s_count++;
	//	else if (s_ch == '(')
	//	{
	//		s_p[++s_c] = s_m - 1;
	//	}
	//	else if (s_ch == ')')
	//	{
	//		s_q = s_m - 1;
	//		s_SET_Mul_Div(s_p[s_c], s_q);//从左括号处理到右括号，先乘除
	//		s_SET_Add_Sub(s_p[s_c], s_q);//后加减
	//		s_temp = (int)s_tempvar - 1;
	//		s_tempvar = (char)s_temp;
	//		s_string[s_p[s_c]] = s_string[s_m - 1] = s_tempvar;
	//		s_c--;
	//		s_temp = (int)s_tempvar + 1;
	//		s_tempvar = (char)s_temp;
	//	}
	//}
	/********调用生成四元式的函数********/
	s_print();//不在括号里的用print操作处理，依旧先乘除后加减，再赋值操作
	/*********判断是否成功**********/
	if (s_count == 0) //所有的式子都分析出来了
		printf("successful\n");
	else
		printf("failed\n");
	return;
}
//处理乘除运算 （处理的是一个括号里的内容，不包括括号）
void s_SET_Mul_Div(int i, int m) 
{
	for (i++; i <= m - 1; i++)
	{
		if (s_string[i] == '*' || s_string[i] == '/')
		{
			cout << "(" << s_string[i] << "  " << s_string[i - 1] << "  " << s_string[i + 1] << "  " << s_tempvar << ")"<<endl;
			//printf("(%c  %c  %c  %c)\n", s_string[i], s_string[i - 1], s_string[i + 1], s_tempvar);
			s_string[i - 1] = s_string[i] = s_string[i + 1] = s_tempvar;
			s_count--;
			s_temp = (int)s_tempvar + 1;
			s_tempvar = (char)s_temp;
		}
	}
}
//处理加减运算 （处理的是一个括号里的内容，不包括括号）
void s_SET_Add_Sub(int j, int m) 
{
	j++;
	for (; j <= m - 1; j++)
	{
		if (s_string[j] == '+' || s_string[j] == '-')
		{
			printf("(%c  %c  %c  %c)\n", s_string[j], s_string[j - 1], s_string[j + 1], s_tempvar);
			s_string[j - 1] = s_string[j] = s_string[j + 1] = s_tempvar;
			s_count--;
			s_temp = (int)s_tempvar + 1;
			s_tempvar = (char)s_temp;
		}
	}
}

//处理不在括号里的，先乘除后加减再赋值
void s_print()
{
	int i;
	for (i = 0; i <= s_m - 1; i++)//处理乘除运算     
	{
		if (s_string[i] == '*' || s_string[i] == '/')
		{
			printf("(%c  %c  %c  %c)\n", s_string[i], s_string[i - 1], s_string[i + 1], s_tempvar);
			s_string[i - 1] = s_string[i] = s_string[i + 1] = s_tempvar;
			s_count--;
			s_temp = (int)s_tempvar + 1;
			s_tempvar = (char)s_temp;
		}
	}
	int j;
	for (j = 0; j <= s_m - 1; j++)//处理加减运算     
	{
		if (s_string[j] == '+' || s_string[j] == '-')
		{
			printf("(%c  %c  %c  %c)\n", s_string[j], s_string[j - 1], s_string[j + 1], s_tempvar);
			s_string[j - 1] = s_string[j] = s_string[j + 1] = s_tempvar;
			s_count--;
			s_temp = (int)s_tempvar + 1;
			s_tempvar = (char)s_temp;
		}
	}
	int k;
	for (k = 0; k <= s_m - 1; k++)  //处理赋值运算    
	{
		if (s_string[k] == '=')
		{
			s_temp = (int)--s_tempvar;
			s_tempvar = (char)s_temp;
			printf("(%c  %c     %c)\n", s_string[k], s_tempvar, s_string[k - 1]);
			s_count--;
			s_string[k - 1] = s_tempvar;
		}
	}
}