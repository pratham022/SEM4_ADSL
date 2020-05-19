/*
 * a.cpp
 *
 *  Created on: Jan 20, 2020
 *      Author: se
 */
/*You have a business with several offices; you want to lease phone lines to
connect them up with each other; and the phone company charges different
amounts of money to connect different pairs of cities. You want a set of lines that
connects all your offices with a minimum total cost. Solve the problem by Prims
or Kruskal using adjacency matrix.*/
#include<iostream>
using namespace std;
class Edge{
public:
	int u, v, w;
};
class Graph{
	int G[20][20];
	string city[20];
	int n;
public:
	Graph()
	{
		string str;
		cout<<"Enter the number of offices"<<endl;
		cin>>n;
		cin.ignore(1);
		cout<<"start entering names of offices "<<endl;
		for(int i=0;i<n;i++)
		{
			getline(cin, str);
			city[i]=str;
		}
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				G[i][j]=0;
			}
		}
	}
	void create_graph()
	{
//		int i, j, x;
//		cout<<"Enter the cost of telephone lines"<<endl;
//		for(i=0;i<n;i++)
//		{
//			for(j=0;j<n;j++)
//			{
//				if(i!=j)
//				{
//					cout<<city[i]<<" -> "<<city[j]<<endl;
//					cin>>x;
//					G[i][j]=x;
//				}
//			}
//		}
		cout<<"Enter adjacency matrix"<<endl;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				cin>>G[i][j];
			}
		}
	}
	void Kruskal()
	{
		Edge list1[400];
		Edge list2[20];
		int component[20];
		int i, j, k;
		int cu, cv;
		int u, v;
		k=0;
		for(i=0;i<n;i++)
		{
			component[i]=i;
		}
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				if(G[i][j]!=0)
				{
					list1[k].u=i;
					list1[k].v=j;
					list1[k].w=G[i][j];
					k++;
				}
			}
		}
		for(i=0;i<k;i++)
		{
			cout<<list1[i].u<<"\t"<<list1[i].v<<"\t"<<list1[i].w<<endl;
		}
		// k contains the number of edges added
		int ne=k;
		for(i=0;i<ne;i++)
		{
			for(j=0;j<ne;j++)
			{
				if(list1[j].w>list1[i].w)
					swap(list1[i], list1[j]);
			}

		}
		i=0;
		k=0;
		int min_wt=0;
		while(k!=n-1)
		{
			u=list1[i].u;
			v=list1[i].v;
			cu=component[u];
			cv=component[v];
			if(cu!=cv)
			{
				list2[k] = list1[i];
				cout<<city[u]<<"--"<<city[v]<<" added"<<endl;
				min_wt += list2[k].w;
				for(int j=0;j<n;j++)
				{
					if(component[j]==cu)
						component[j]=cv;
				}
				k++;
			}
			i++;
		}
		cout<<"minimum wt of spanning tree is: "<<min_wt<<endl;
	}
};
int main()
{
	Graph G;
	G.create_graph();
	G.Kruskal();
	return 0;
}

