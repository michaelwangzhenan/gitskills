/*
In the following multiplication formula each letter represents ONE number (0~9). The same letter represents the same number, different letters represent different numbers. For example:
ACD * BA = CDBE

Please try to program to determine the number combination that makes the entire equation. If there are multiple situations, please give all possible answers.

e.g.
The input of your program is 1 argument, the path of a text file, with the content as follow:
CCD * JC  = FJDHD

The output of your program is a stdout print as follow:
220 * 82 = 18040

NOTE: keep the spaces as orGinal fomula
 * */
#include <iostream>
#include <fstream>
#include <string.h>
#include <set>
#include <cmath>

#include "../inc/multiplication_formula.hpp"

using namespace std;

string line;

void readMulti(char * path)
{
	ifstream in(path);

	if(in)
	{
		getline(in, line);
	}
	else
	{
		cout <<"no such file" << endl;
	}
}

int numVar=0;
char var[10]={0};
int cal[10]={0};
int isStart[10]={0};

void getVar()
{
	int repeat=0;
	for (unsigned int l=0;l<line.length();l++)
	{
		repeat=0;
		if (line[l]>='A' &&line[l]<='Z')
		{
			if (numVar==0)
			{
				var[numVar]=line[l];
				numVar++;
			}
			else
			{
				for (int i=0;i<numVar;i++)
				{
					if (line[l]==var[i])
					{
						repeat=1;
						continue;
					}

				}
				if (repeat==0)
				{
					var[numVar]=line[l];
					numVar++;
				}
			}
		}
	}

#if 1
	for (int t=0;t<numVar;t++)
	{
		cout << var[t];
	}
	cout<<endl;
#endif
}

int num_mul1=0;
int num_mul2=0;
int num_ret=0;
int mul1[5]={0};
int mul2[5]={0};
int ret[5]={0};

void getElement()
{
	int flag=1;
	int start=1;
	for (unsigned int l=0;l<line.length();l++)
	{

		if (line[l]<'A' || line[l]>'Z')
		{
			if (line[l]=='*')
			{
				flag=2;
				start=1;
			}
			if (line[l]=='=')
			{
				flag=3;
				start=1;
			}
			continue;
		}

		for (int i=0;i<numVar;i++)
		{
			if (line[l]==var[i] && flag==1)
			{
				mul1[num_mul1]=i;
				num_mul1++;
				if (start==1)
				{
					isStart[i]=1;
					start = 0;
				}
				continue;
			}else if (line[l]==var[i] && flag==2)
			{
				mul2[num_mul2]=i;
				num_mul2++;
				if (start==1)
				{
					isStart[i]=1;
					start = 0;
				}
				continue;
			}else if (line[l]==var[i] && flag==3)
			{
				ret[num_ret]=i;
				num_ret++;
				if (start==1)
				{
					isStart[i]=1;
					start = 0;
				}
				continue;
			}
		}
	}

#if 1
	for (int t=0;t<num_mul1;t++)
	{
		cout << mul1[t];
	}
	cout << endl;
	for (int t=0;t<num_mul2;t++)
	{
		cout << mul2[t];
	}
	cout << endl;
	for (int t=0;t<num_ret;t++)
	{
		cout << ret[t];
	}
	cout << endl;

	for (int t=0;t<numVar;t++)
	{
		cout << isStart[t];
	}
	cout<<endl;
#endif
}


int getValue(int len, int *el)
{
	int value=0;
	for (int i=0; i<len; i++ )
	{
		value += cal[el[i]]*pow(10,len-i-1);
		cout << cal[el[i]] << " ";
	}
	cout << "->" <<value << endl;
	return value;
}

void printValue(int len, int *el)
{
	for (int i=0; i<len; i++ )
	{
		cout<< cal[el[i]];
	}
}

void printRet()
{
	printValue(num_mul1,mul1);
	cout << " * ";
	printValue(num_mul2,mul2);
	cout << " = ";
	printValue(num_ret,ret);
	cout <<endl;

}

void calc(int level)
{
	int init = isStart[level]==1?1:0;
	int skip=0;
	for (int i=init;i<10;i++)
	{
		skip=0;
      	for (int r=0;r<level;r++)
       {
         if (cal[r]==i)
         {
           skip =1;
           continue;
         }

       }
      	if (skip==1)
      	{
      		continue;
      	}

		cal[level]=i;
		if (level<numVar-1)
		{
			calc(level+1);
		}
		else
		{
			if (getValue(num_mul1,mul1)*getValue(num_mul2,mul2)==getValue(num_ret,ret))
			{
				printRet();
			}
		}
	}

}

void multiplication_f(char* path)
{
	readMulti(path);
	cout << line<<line.length()<<endl;
	getVar();
	getElement();

	cal[0]=2;
	cal[1]=2;
	cal[2]=2;
	cal[3]=2;
	cal[4]=2;
	getValue(num_ret,ret);

	//calc(0);
}
