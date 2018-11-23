#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

//#include "../inc/machineStudy.hpp"
using namespace std;

#define MAX 26

int study[MAX][2] = {0};

void readNameGender(char* p)
{
	char seps[] = ",";
	char *token=NULL;
	token = strtok( p, seps );
	int i=0,index=0;

	while( token != NULL )
	{
		if (i==0)
		{
			index = token[0]-65;
			if (index<0 || index>=MAX)
				break;
		}
		else
		{
			if (strcmp(token,"male")==0)
			{
				study[index][0]++;
			}else{
				study[index][1]++;
			}

		}
		i++;
		token = strtok( NULL, seps );

	}
}

void printT()
{
	char s='A';
	for (int i=0;i<MAX;i++)
	{
		cout << s++ << ": ";
		for (int j=0;j<2;j++)
			cout << study[i][j]<< " ";
		cout << endl;
	}
}

void readPre(char* p)
{
	int index = p[0]-65;
	if (index<0 || index>=MAX)
		index = 0;
	cout << p<< ",";
	if (study[index][0]>study[index][1])
		cout << "male"<<endl;
	else
		cout << "female"<<endl;

}

void readTrainning(char *path,int flag)
{
	ifstream in(path);
	string line="";

	if(in)
	{
		while (getline(in, line))
		{
			char *p = (char *)line.c_str();
			if (flag ==0)
				readNameGender(p);
			else
				readPre(p);
		}
	}
	else
	{
		cout <<"no such file" << endl;
	}
}

void predict(char * path)
{
	readTrainning(path,1);
}

void machine(char *path)
{
	readTrainning(path,0);
	printT();
	predict("D:/sourceCode/mycode/codeJam/codeJam/src/test.csv");

}
