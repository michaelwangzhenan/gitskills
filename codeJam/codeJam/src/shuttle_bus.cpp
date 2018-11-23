/*
 * ?NOKIA Hangzhou TC is going to open a new super shuttle bus line with unlimited capacity. Its all possible stops can be considered as a M*N matrix(1 <= M, N <= 100)

stop(1, 1)  stop(2, 1)  ...  stop(M, 1)
stop(1, 2)  stop(2, 2)  ...  stop(M, 2)
... ...
stop(1, N)  stop(2, N)  ...  stop(M, N)

Now we know how many employees at each stop(there won't be more than 10 employees per stop, CMN=0)

C11, C21, C31, ... CM1,
C12, C22, C32...   CM2,
... ...
C1N, C2N, C3N, ... CMN,

Assuming the shuttle bus always starts from stop(1, 1) and ends at stop(M, N), and it can only go down or go right on the matrix map. The capacity of this shuttle bus is infinite.

Please calculate the maximum number of employees that the shuttle bus can carry in one trip.

Example
M=3£¬ N=2
the number of employees at each stop£º
C11=5£¬C21=2£¬C31=4
C12=1£¬C22=6£¬C32=0
The best route is (1,1)->(2,1)->(2,2)->(3,2), by which it can carry 5+2+6=13 employees

The range of parameters:
1 <= M, N <= 100
0 <= C11~CMN <= 10

The input of your program is 1 argument, the path of a CSV file, with the content as follow:
M, N
C11, C21, C31, ... CM1,
C12, C22, C32...   CM2,
... ...
C1N, C2N, C3N, ... CMN,

e.g.
3, 2
5, 2, 4
1, 6, 0

The output of your program is a stdout print as follow:
13
 * */
#include <iostream>
#include <fstream>
#include <queue>
#include <string.h>
#include <stdlib.h>
//#include "../inc/shuttle_bus.hpp"

using namespace std;
#define MAX 200

int map[MAX][MAX];
int mapStep[MAX][MAX];

struct node {
	int x;
	int y;
	int step;
	node(int _x = 0, int _y = 0, int _step = 0) : x(_x), y(_y), step(_step) {
	}
};

int trow=0;
int tcol=0;

node final = node(0,0,0);
node start = node(0,0,0);
int node_array[2][2] = {{0, 1},{1, 0}};

void initData()
{
	for (int i=0;i<MAX;i++)
	{
		for(int j=0;j<MAX;j++)
		{
			map[i][j]=0;
			mapStep[i][j]=0;
		}
	}
}

int find_map(int row, int col) {
	queue<node> queue_node;
	while (!queue_node.empty()) {
		queue_node.pop();
	}
	queue_node.push(start);
	node top = node(0,0,0);;

	int ret = 0;
	while (!queue_node.empty())
	{
		top = queue_node.front();
		queue_node.pop();
		if (top.x == final.x && top.y == final.y)
		{
			if (top.step > ret)
			{
				ret = top.step;
				continue;
			}
		}

		for (int i = 0; i != 2; i++)
		{
			int node_x = top.x + node_array[i][0];
			int node_y = top.y + node_array[i][1];
			if (node_x >= 0 && node_y >= 0 && node_x < MAX && node_y < MAX)
			{
				if (node_y < col && node_x < row)
				{
					node temp = node(node_x, node_y, top.step + map[node_x][node_y]);
					if (temp.step > mapStep[node_x][node_y])
					{
						mapStep[node_x][node_y] = temp.step;
						queue_node.push(temp);
					}
				}
			}
		}
	}

	cout << ret <<endl;
	return 0;
}

void readMapBus(char* p,int row)
{
	char seps[] = ", ";
	char *token = strtok( p, seps );
	int i=0;

	while(NULL != token)
	{
		if (row >= 0)
		{
			if (i <= MAX)
				map[row][i++] = atoi(token);
		}else{
			i++;
			if (1==i)
				tcol = atoi(token);
			else
				trow = atoi(token);
		}
		token = strtok(NULL, seps);
	}
}

int readDataBus(char *path)
{
	ifstream in(path);
	string line="";
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
				readMapBus(p,-1);
			}
			else
			{
				readMapBus(p,rowOfArray);
				rowOfArray++;
			}
		}
	}
	else
	{
		cout <<"no such file" << endl;
		return 1;
	}
	return 0;
}

void shuttleBus(char *path)
{
	initData();
	if (readDataBus(path)>0)
		return ;

	start.step=map[0][0];
	final.x = trow-1;
	final.y = tcol-1;
	find_map(trow,tcol);
}

#if 0
#include <iostream>
#include <fstream>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include "../inc/shuttle_bus.hpp"

using namespace std;


int map[50][50] = {0};
int mapStep[50][50] = {0};

struct node {
	int x;
	int y;
	int step;
	node(int _x = 0, int _y = 0, int _step = 0) : x(_x), y(_y), step(_step) {
	}
};

int countIn=0;
int countOut=0;
int trow=0;
int tcol=0;

node final = node();
node start = node();

int node_array[2][2] = {{0, 1},{1, 0}};

int find_map(int row, int col) {
	queue<node> queue_node;
	while (!queue_node.empty()) {
		queue_node.pop();
	}
	queue_node.push(start);
	node top;
	//visited[start.x][start.y] = 1;
	int ret = 0;
	while (!queue_node.empty())
	{
		top = queue_node.front();
		//cout <<"pop-out"<<"["<< top.x <<","<<top.y<<"]"<<"-->"<<top.step << endl;
		countOut++;
		queue_node.pop();
		if (top.x == final.x && top.y == final.y)
		{
			//cout << top.step << endl;
			if (top.step > ret)
			{
				ret = top.step;
				continue;
			}
		}
		for (int i = 0; i != 2; i++)
		{
			int node_x = top.x + node_array[i][0];
			int node_y = top.y + node_array[i][1];
			if (node_x >= 0 && node_y >= 0)
			{
				if (node_y < col && node_x < row)
				{
					node temp = node(node_x, node_y, top.step + map[node_x][node_y]);
					//visited[node_x][node_y] = 1;

					if (temp.step > mapStep[node_x][node_y])
					{
						mapStep[node_x][node_y] = temp.step;
						queue_node.push(temp);
						countIn++;
						cout <<"push-in:"<<"["<< temp.x <<","<<temp.y<<"]"<<"-->"<<temp.step<<":"<< map[node_x][node_y] << endl;
					}

				}
			}
		}
	}

	cout << "ret = " << ret <<",in="<<countIn<<",out="<<countOut<<endl;
	//cout << ret <<endl;
	return 0;
}

void readMapBus(char* p,int row)
{
	char seps[] = ", ";
	char *token=NULL;
	token = strtok( p, seps );
	int i=0;

	while( token != NULL )
	{
		if (row >= 0)
		{
			map[row][i++] = atoi(token);
		}else{
			i++;
			if (i==1)
				tcol = atoi(token);
			else
				trow = atoi(token);
		}
		token = strtok( NULL, seps );
	}
}

void readDataBus(char *path)
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
				readMapBus(p,-1);
			}
			else
			{
				readMapBus(p,rowOfArray);
				rowOfArray++;
			}
		}
	}
	else
	{
		cout <<"no such file" << endl;
	}
}

void printDataBus()
{
	for (int i=0;i<trow;i++)
	{
		for(int j=0;j<tcol;j++)
		{
			cout<<map[i][j]<<" ";
		}
		cout<<endl;
	}
}

void shuttleBus(char *path)
{
	readDataBus(path);
	//printDataBus();
	start.step=map[0][0];
	final.x = trow-1;
	final.y = tcol-1;
	find_map(trow,tcol);
}
#endif
