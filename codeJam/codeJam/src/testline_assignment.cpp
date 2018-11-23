/*
 *
NOKIA Hangzhou TC has many cloud test line, with index such as 1, 2, 3, ..., testlineNum; It also have many test engineers, with index such as 1, 2, ..., userNum.
Every test engineer can only use 1 test line at 1 time (1 <= userNum <= testlineNum).
Every test line can only be assigned to 1 engineer at 1 time.
Every engineer has different requirements for test line, so the list of test lines are different among engineers.
e.g.
Engineers1 can apply 1, 3, 4, 6, 7
Engineers2 can apply 2, 3, 4, 8, 9, 15

How many options can there be for every test engineer to have 1 test line?

Input range:
userNum <= testlineNum
1 <= userNum <= 10
1 <= testlineNum <= 20

The input of your program is 1 argument, the path of a CSV file, with the content as follow:
testline_num, user_num
user1_testline_list
user2_testline_list
...

e.g.
3, 2
1, 2
1, 2, 3

The output of your program is a stdout print
num_of_options

e.g.
4

Input:
9, 6
1, 5, 6, 8, 9
1, 6, 8
2, 8, 9
1, 5, 7, 8, 9
1, 2, 4, 6, 7, 8
1, 3, 4, 7, 8, 9
 * */

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

//#include "../inc/testline_assignment.hpp"

using namespace std;
int count=0;
int user=0, tLine=0;
int reqNum[50]={0};
int assigned[50]={0};

int user_testiline[50][50]={0};

void resetAssign(int userNo)
{
	for (int i=user-1;i>=userNo;i--)
	{
		assigned[i]=0;
	}
}

void printAssign()
{
	if (assigned[user-1]==0)
	{
		return;
	}

	for (int i=0;i<user;i++)
	{
		//cout << assigned[i] << " ";
	}
	//cout << endl;
	count++;
}

void assign(int userNo)
{
	int i=0,yes=1;
	for (int u=0;u<reqNum[userNo];u++)
	{
		yes=1;
		for ( i=0;i<userNo;i++)
		{
			if (user_testiline[userNo][u] == assigned[i])
			{
				yes=0;
				continue;
			}
		}
		if (yes==1)
		{
			assigned[userNo]=user_testiline[userNo][u];
			if (userNo==user-1)
			{
				printAssign();
				resetAssign(userNo);
			}else
			{
				assign(userNo+1);
			}
		}

	}
}

void readNum(char* p)
{
	char seps[] = ", ";
	char *token;
	token = strtok( p, seps );
	int i=0;

	while( token != NULL )
	{
		i++;
		if (i==1)
			tLine = atoi(token);
		else
			user = atoi(token);;

		token = strtok( NULL, seps );
	}
}


void readMap(char* p,int row)
{
	char seps[] = ", ";
	char *token;
	token = strtok( p, seps );
	int i=0;

	while( token != NULL )
	{
		user_testiline[row][i++] = atoi(token);;
		token = strtok( NULL, seps );
	}
}

void readData(char * path)
{
	ifstream in(path);
	string line;
	int numLine=0;
	int rowOfArray=0;

	if(in)
	{
		while (getline(in, line))
		{
			numLine++;
			char *p = (char *)line.c_str();
			if (numLine==1)
			{
				readNum(p);
			}
			else
			{
				readMap(p,rowOfArray);
				rowOfArray++;
			}
		}
	}
	else
	{
		cout <<"no such file" << endl;
	}
}

void printData()
{
	for (int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if (user_testiline[i][j]!=0)
				cout<<user_testiline[i][j]<<" ";
		}
		cout<<endl;
	}
}

void testline(char *path)
{
	readData(path);

	for(int u=0;u<user;u++)
	{
		for(int t=0;t<tLine;t++)
		{
			if (user_testiline[u][t]==0)
				continue;
			reqNum[u]++;
		}
		//cout << reqNum[u]<<endl;
	}

	for (int u1=0;u1<reqNum[0];u1++)
	{
		assigned[0]=user_testiline[0][u1];
		assign(1);
	}
	cout << count <<endl;
}



