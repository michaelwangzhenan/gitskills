/*
 * ?NOKIA will apply SAFe step by step from now on, all features and enablers together on each ART(Agile Release Train) are going to be planned on PI meeting together.

Let's assume that:
- All the factors, like the user business value, time criticality and risk deduction/opportunity enablement, are already unified as a single value, which represents profit or cost.
- All features are required by customers, who will pay for them, and they will bring profits to company.
- All enablers are not required by customers, and they will only cost money. But some features may depend on them, so they have to be done sometimes.
- All features and enablers could depend on each others

As the RTE/PO, you have to pick some features and enablers to guarantee NOKIA have the possible maximum profits.

Input: The 1st line is the total number of features and enablers (0<= n <=1000), and then each line represents a feature or enabler, in which the 1st number is the costs (negetive) or profits (positive) value (-1,000,000<= n <=1,000,000), and after it, the numbers are the indices of all the features and enablers on which this one depends. They are separated by spaces.

Output: The 1st line is the company's maximum profits, and then the list of all selected features/enablers, each line has a index of a feature/enabler. If there are multiple solutions for the maximum profits, then choose the one with the least number of items.

The input of your program is 1 argument, the path of a text file, with the content as follow:
item_num
item1_dependence_list
item2_dependence_list
...

e.g.
6
-4
1
2 2
-1 1 2
-3 3
5 3 4

The output of your program is a stdout print
Maximum_profits
selected_item_index1
selected_item_index2
...

e.g.
3
2
3

*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

//#include "../inc/safe.hpp"
using namespace std;

struct item
{
	int index;
	int profit;
	int num_depends;
	int depends[20];
	//int singleProfit;
};

int num_input = 0;
int cal_map[100] = {0};
int num_inc_map = 0;
int inc_map[100] = {0};
int final_map[100] = {0};
struct item input[100] = {0};

void readLine(char* p,int row)
{
	char seps[] = " ";
	char *token=NULL;
	token = strtok( p, seps );
	int i=0;

	while( token != NULL )
	{
		if (row >= 0)
		{
			i++;
			if (i==1)
			{
				input[row].index = row+1;
				input[row].profit= atoi(token);
			} else
			{
				input[row].depends[i-2]= atoi(token);
				input[row].num_depends = i-1;
			}
		}else{
			num_input = atoi(token);
		}
		token = strtok( NULL, seps );
	}
}


void readDataSafe(char *path)
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
				readLine(p,-1);
			}
			else
			{
				readLine(p,rowOfArray);
				rowOfArray++;
			}
		}
	}
	else
	{
		cout <<"no such file" << endl;
	}
}

void printRead()
{
	cout <<num_input <<endl;
	for (int i=0; i<num_input; i++ )
	{
		cout << input[i].index <<" ";
		cout << input[i].profit <<" ";
		cout << input[i].num_depends <<" [";

		for (int j=0; j<input[i].num_depends; j++)
		{
			cout << input[i].depends[j] <<" ";
		}
		cout << "]";
		//cout << input[i].singleProfit;
		cout << endl;
	}

}

#if 0
void cal_singleProfit()
{
	for (int i=0; i<num_input; i++ )
	{
		input[i].singleProfit = input[i].profit;
		for (int j=0; j<input[i].num_depends; j++)
		{
			input[i].singleProfit += input[input[i].depends[j]-1].profit;
		}d
	}
}

#endif

void resetCalMap()
{
	for (int i=0; i<num_input; i++ )
	{
		cal_map[i]=0;
	}
}

void resetIncMap()
{
	num_inc_map = 0;
	for (int i=0; i<num_input; i++ )
	{
		inc_map[i]=0;
	}
}

void getCalMap(int index)
{
	cal_map[index-1] = 1;
	for (int j=0; j<input[index-1].num_depends; j++)
	{
		cal_map[input[index-1].depends[j]-1]=1;
		getCalMap(input[index-1].depends[j]);
	}
}

void getIncMap(int index)
{
	for (int i=0; i<num_input; i++ )
	{
		if (input[i].index!=index)
		{
			for (int j=0; j<input[i].num_depends; j++)
			{
				if (input[i].depends[j]==index)
				{
					inc_map[num_inc_map]=input[i].index;
					num_inc_map++;
					break;
				}
			}
		}
	}

}

void printMap()
{
	cout << "inc_map:" <<endl;
	for (int i=0; i<num_input; i++ )
	{
		cout << inc_map[i] << " ";
	}
	cout << endl;

	cout << "cal_map:" <<endl;
	for (int i=0; i<num_input; i++ )
	{
		cout << cal_map[i] << " ";
	}
	cout << endl;

	cout << "final_map:" <<endl;
	for (int i=0; i<num_input; i++ )
	{
		cout << final_map[i] << " ";
	}
	cout << endl;
}

int cal_realProfit(int index)
{
	int realProfit = 0;

	resetCalMap();
	getCalMap(index);
	for (int i=0; i<num_input; i++ )
	{
		if (cal_map[i] == 1)
		{
			realProfit += input[i].profit;
		}
	}

	return realProfit;
}

void setFinalFromCal()
{
	for (int i=0; i<num_input; i++ )
	{
		if (cal_map[i] == 1)
		{
			final_map[i]=1;
		}
	}
}

void firstSelect()
{
	for (int i=num_input-1; i>=0; i-- )
	{
		if (final_map[i]!=1 && input[i].profit>0)
		{
			if (cal_realProfit(input[i].index) > 0)
			{
				setFinalFromCal();
			}
		}
	}
}

void secondSeclet()
{
	int tempProfit = 0;
	for (int i=0; i<num_input; i++)
	{
		tempProfit = 0;
		if (final_map[i]!=1)
		{
			resetIncMap();
			resetCalMap();
			getIncMap(input[i].index);
			for (int j=0;j<num_inc_map;j++)
			{
				getCalMap(inc_map[j]);
			}

			for (int i=0; i<num_input; i++ )
			{
				if (cal_map[i] == 1)
				{
					tempProfit += input[i].profit;
				}
			}

			if (tempProfit > 0)
			{
				setFinalFromCal();
			}
		}
	}
}

void printFinalRet()
{
	int finalProfit = 0;
	for (int i=0; i<num_input; i++ )
	{
		if (final_map[i] == 1)
		{
			finalProfit += input[i].profit;
		}
	}

	cout << finalProfit << endl;

	for (int i=0; i<num_input; i++ )
	{
		if (final_map[i] == 1)
		{
			cout << input[i].index <<endl;
		}
	}
}

void safe(char *path)
{
	readDataSafe(path);
	//printRead();
	firstSelect();
	secondSeclet();

	//printMap();
	printFinalRet();
}
