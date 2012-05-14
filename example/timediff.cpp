#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;

const int num_nodes = 30;
int main()
{

	long int times[num_nodes][2];
	char buffer[1024];
	ifstream input;
	input.open("jointimes.txt",ios::in);
	for(int i=0;i<num_nodes;i++)
	{
		for(int j=0;j<2;j++)
		{
			input>>buffer;
			times[i][j]=atol(buffer);
			cout<<buffer<<"\t";		
		}
		cout<<"\n";
	}
cout<<"\n\nTimes of joining";	
	ofstream timediffs;
	timediffs.open("timediffs.log",ios::trunc|ios::out);
	for(int i = 0;i<num_nodes;i++)
	{
		if(times[i][0]==times[i+1][0])
			timediffs<<i+1<<"\t"<<(times[i+1][1]-times[i][1])<<"\n";
		else
			timediffs<<i+1<<"\t"<<((times[i+1][0]-times[i][0])*1000000 + ((1000000-times[i][1])+times[i+1][1]))<<"\n";
	}
		
}