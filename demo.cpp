////////////////////////////////////////////////////////////////
//** Author: ����
//** Date:[11/7/2016]
//** Version:1.0.0
//** Description:
/*
�ʷ�����
�﷨������LL(1)����
�������������Ԫʽ������
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

void sem_analysis();
#define MAX 100 
void s_SET_Mul_Div(int i, int m,bool flag);
void s_SET_Add_Sub(int j, int m,bool flag);
void s_print();
int s_m = 0;
int s_count = 0;
char s_tempvar = 'A';
int s_temp;
char s_string[MAX];//���ڴ�ű��ʽ


char  f1[10] = { "E->Te" };//1
char  f2[10] = { "e->WTe" };//2������Wִ��+����-
char  f3[10] = { "e->0" };//3
char  f4[10] = { "T->Ft" };//4
char  f5[10] = { "t->wFt" };//5������wִ��*����/
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
int p, m, syn;//syn�Ƕ�Ӧ��token �ؼ�����
char ch;
char huancun2[200];             //huancun2������ľ��ӵ�һ��������		����((Aa+Bb)*(78.3+2))#&����
char huancun3[30] = { "sdsd" }; //huancun3����Ӧ�����������ʽ�ľ��ӷ��ͣ�����((IWI)w(IWI))#����
char *now = huancun3;			//��ǰ��������

//stack<char> sem_stack;//����ջ������huancun3���ݽ��в�����Ȼ�����huancun2�õ����������

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

//�ʷ�����
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
//���ʷ������õ��Ľ��tokenת����Ӧ���ķ�����Vn����Vt;
void exchange()
{
	char *now1 = huancun3;//huancun3����Ӧ�ľ���
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
//���ôʷ�����������
void administrator()
{
	p = 0;
	int i = 0;
	while (syn != 100)
	{
		scanner();
		switch (syn) 
		{
		case 3://��������
			i++;
			while (i == 5)
			{
				cout << endl;
				i = 0;
			}
			cout << '(' << sum1 << '.' << sum2 << ',' << syn << ')' << "  "; break;
		default://����ؼ��ֺͱ�����
			i++;
			while (i == 5)//�����������ͻ���
			{
				cout << endl;
				i = 0;
			}
			cout << '(' << token << ',' << syn << ')' << "  "; break;
		}
	}
	return;
}

//�﷨������������
void action()
{
	if (mystack.top() == *now)//���ջ��==��ǰ��
	{
		cout << "��ջ\t" << mystack.top() << "\t��ǰ��=" << *now<<endl;
		mystack.pop();
		now++;//����һ������
		return;
	}
	else 
	{
		if ((decode(mystack.top(), *now)) == f9)
		{
			cout << "������﷨����ʧ��" << endl;
			cout << "��������������������������������������������" << endl;
			cout << endl;
			exit(-1);
			return;
		}
		else
		{
			string mystring(decode(mystack.top(), *now));  //���õ��Ķ�Ӧ����ʽ�Ҳ�����mystring;
			if (*(decode(mystack.top(), *now) + 3) == '0')//�������ʽΪ�գ�ֱ��ִ�е�ջ����
			{
				cout << "��ջ\t" << mystack.top() << "\t��ǰ��=" << *now<<endl;
				mystack.pop();
				return;
			}
			else 
			{
				user = decode(mystack.top(), *now);//���ݵ�ǰ�����Լ�ջ���õ��Ĳ���ʽ
				t = decode(mystack.top(), *now) + mystring.length() - 1;
				cout << "��ջ\t" << mystack.top() << endl;//�Ȱ�ջ������
				mystack.pop();
				cout << "ѹջ\t";
				int num_t = 0;
				while ((*t) != '>')//���Ҳ�����ʽ������ջ,'>'�Ƿֽ��
				{
					mystack.push(*t);
					t--;
					num_t++;
					cout << mystack.top();
				}
				if (num_t==3)
				{
					cout << "\t��ǰ��=" << *now << "\t���ʽ=" << user << endl;//�������������ʣ�µĵ�ǰ�����Լ�ǰ���Ӧ�����Ĳ���ʽ
				}
				else
				{
					cout << "\t��ǰ��=" << *now << "\t���ʽ=" << user<<endl ;//�������������ʣ�µĵ�ǰ�����Լ�ǰ���Ӧ�����Ĳ���ʽ
				}
				return;
			}
			return;
		}
	}
}
//���ݵ�ǰ�����Լ�ջ��Ԫ��ȷ����Ӧ�Ĳ���ʽ
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
//LL1��������������   
void first()
{
	mystack.push('#');
	mystack.push('E');
	cout << endl;
	cout << "���������������������﷨��������������������" << endl;
	cout << "\nջ����" << "\t" <<"Ԫ��\t" <<"��ǰ��" << " \t\t" << "���ʽ" << endl;
	char *now = huancun3;
	while ((mystack.top() != '#') && (*now != '#'))//ջ�����Ų�Ϊ#�ҵ�ǰ���Ų�����#
	{
		action();
	}
	cout << "������﷨�����ɹ�" << endl;
	return;
}


//�ļ���������
void File()
{
	ifstream infile;
	infile.open("E:\code.txt", ios::in);
	if (infile.fail())
	{
		cout << "ʧ��" << endl;
		return;
	}
	while (!infile.eof())
	{//�ļ�û�н����������ȡ.
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
	//infile.open("E:\code1.txt", ios::in);
	//infile.open("E:\code2.txt", ios::in);
	if (infile.fail())
	{
		cout << "�ļ���������" << endl;
		return 0;
	}
	int n = 0;
	while (!infile.eof())
	{//�ļ�û�н����������ȡ.
		infile.getline(huancun2, 300, '&');
		infile >> huancun2;
		huancun2[0] = 'a';
	}
	cout << "����������������������ľ��ӡ���������������" << endl;
	cout << huancun2<<endl;//���������
	cout << "���������������������ʷ���������������������" << endl;
	administrator();//���ôʷ�����������
	m = 0;
	p = 0;
	n = 0;
	exchange();//���ʷ������õ��Ľ��tokenת����Ӧ���ķ�����Vn����Vt;�õ����������ķ�������һ������
	cout << endl;
	cout<<"�õ��ľ���:"<<huancun3;//�����仯�õ��Ķ�Ӧ��һ������
	infile.close();
	sem_analysis();
	first();//LL1������ں���
	cout << "��������������������������������������������" << endl;
	cout << endl;
	return 0;
}


//�������
void sem_analysis()
{
	int s_p[MAX];//
	char s_ch;
	int s_c = -1, s_q = 0;
	cout << endl <<"�������������������������������������������" << endl;
	strcpy(s_string,huancun2);
	cout << s_string << endl;
	cout << "��Ԫʽ���У�" << endl;
	bool flag = false;
	while (s_string[s_m]!='#')
	{
		s_ch = s_string[s_m++];
		if (s_ch == '=' || s_ch == '+' || s_ch == '-' || s_ch == '*' || s_ch == '/')
			s_count++;
		else if (s_ch == '(')
		{
			s_p[++s_c] = s_m - 1;
			flag = false;
		}
		else if (s_ch == ')')
		{
			if (flag==true)
			{
				break;
			}
			s_q = s_m - 1;
			s_SET_Mul_Div(s_p[s_c], s_q,flag);//�������Ŵ��������ţ��ȳ˳�
			s_SET_Add_Sub(s_p[s_c], s_q,flag);//��Ӽ�
			s_temp = (int)s_tempvar - 1;
			s_tempvar = (char)s_temp;
			s_string[s_p[s_c]] = s_string[s_m - 1] = s_tempvar;
			s_c--;
			s_temp = (int)s_tempvar + 1;
			s_tempvar = (char)s_temp;
			flag = true;
		}
		
	}
	s_print();//�������������print�������������ȳ˳���Ӽ����ٸ�ֵ����
	if (s_count == 0 && s_string[s_m] == '#') //���е�ʽ�Ӷ�����������
		cout << "�������������ɹ�" << endl;
	else
		cout << "������������ʧ��" << endl;
	return;
}
//����˳����� ���������һ������������ݣ����������ţ�
void s_SET_Mul_Div(int i, int m,bool flag) 
{
	if (flag==true)
	{
		return;
	}
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
//����Ӽ����� ���������һ������������ݣ����������ţ�
void s_SET_Add_Sub(int j, int m,bool flag) 
{
	if (flag == true)
	{
		return;
	}
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

//������������ģ��ȳ˳���Ӽ��ٸ�ֵ
void s_print()
{
	int i;
	for (i = 0; i <= s_m - 1; i++)//����˳�����     
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
	for (j = 0; j <= s_m - 1; j++)//����Ӽ�����     
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
	for (k = 0; k <= s_m - 1; k++)  //����ֵ����    
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