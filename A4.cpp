/*
 * a.cpp
 *
 *  Created on: Jan 13, 2020
 *      Author: se
 */
/*There are flight paths between cities. If there is a flight between city A and city B
then there is an edge between the cities. The cost of the edge can be the time that
flight takes to reach city B from A, or the amount of fuel used for the journey.
Represent this as a graph. The node can be represented by airport name or name
of the city. Use adjacency list representation of the graph. (Operation to be
performed adding and deleting edge, adding and deleting vertices, calculated in-
degree and out-degree for directed graph. Use any traversal to traverse graph)*/
#include<iostream>
using namespace std;
class Path{
public:
	string dest;
	int dist;
	Path* next;
	Path(string v, int w)
	{
		dest=v;
		dist=w;
		next=NULL;
	}
};
class Node{
public:
	string city;
	Node* down;
	Path* right;
	Node(string s)
	{
		city=s;
		down=NULL;
		right=NULL;
	}

};
class Graph{
	Node* start;
public:
	Graph()
	{
		string s;
		start=NULL;
		cout<<"start entering city names"<<endl;
		cout<<"Enter city"<<endl;
		getline(cin, s);
		start= new Node(s);
		Node* p=start;
		while(1)
		{
			cout<<"Enter city"<<endl;
			getline(cin, s);
			if(s!= "-1")
			{
				p->down = new Node(s);
				p=p->down;
			}
			else
				break;
		}
	}
	void initial_path()
	{
		string u, v;
		int w;
		int c;
		cout<<"Enter the paths between the cities"<<endl;
		cout<<"Enter -1 -1 -1 to stop"<<endl;
		while(1)
		{
			cin>>u>>v;
			cin>>w;
			if(w==-1)
				break;
			c=check(u, v);
			cout<<"Returned value from function is "<<c<<endl;
			Node* p= start;
			if(c==2)
			{
				while(p->city!=u)
					p=p->down;
				add_at_end(p, v, w);
			}
			else if(c==1)
			{
				// first add dest to the main list and the to path list
				while(p->down!=NULL)
					p=p->down;
				p->down= new Node(v);
				p= start;
				while(p->city!=u)
					p=p->down;
				add_at_end(p, v, w);
			}
			else if(c==0)
			{
				// first add source to main list and then to path list
				while(p->down!=NULL)
					p=p->down;
				p->down = new Node(u);
				p=p->down;
				add_at_end(p, v, w);
			}
			else
			{
				// add both cities to the main list first
				while(p->down!=NULL)
					p=p->down;
				p->down= new Node(v);
				p=p->down;
				p->down = new Node(u);
				p=p->down;
				add_at_end(p, v, w);
			}

		}
	}
	void add_at_end(Node* p, string v, int w)
	{
		if(p->right==NULL)
			p->right=new Path(v, w);
		else
		{
			Path* q=p->right;
			while(q->next!=NULL)
				q=q->next;
			q->next= new Path(v, w);
		}
	}
	int check(string u, string v)
	{
		Node* p=start;
		int l, r;
		l=r=0;
		while(p!=NULL)
		{
			if(p->city==u)
				l++;
			if(p->city==v)
				r++;
			p=p->down;
		}
		if(l==1 && r==1)	// both cities present
			return 2;
		else if(l==1 && r==0)	// source present
			return 1;
		else if(l==0 && r==1)	// destination present
			return 0;
		else					// none present
			return -1;
	}
	void show()
	{
		Node* p= start;
		while(p!=NULL)
		{
			cout<<p->city<<" : ";
			Path* q=p->right;
			while(q!=NULL)
			{
				cout<<q->dest<<" ";
				q=q->next;
			}
			cout<<"\n";
			p=p->down;
		}
	}
	void add_city()
	{
		cin.ignore(1);
		string u;
		cout<<"Enter the city to be added"<<endl;
		getline(cin, u);
		Node* p=start;
		while(p->down!=NULL)
			p=p->down;
		p->down= new Node(u);
	}

	void delete_path()
	{
		string u, v;
		cout<<"Enter path to be deleted"<<endl;
		cin>>u>>v;
		cin.ignore();
		int c= check(u, v);
		if(c!=2)
		{
			cout<<"No such path exists!!!!!"<<endl;
			return;
		}
		else
		{
			Node* p=start;
			while(p->city!=u)
				p=p->down;
			Path* q=p->right;
			Path* r=NULL;
			if(q==NULL)
			{
				cout<<"path not found"<<endl;
				return;
			}
			if(p->right->dest==v)	// path found at 1st place
			{
				p->right=q->next;
				delete q;
				cout<<"path deleted"<<endl;
				return;
			}
			else
			{
				while(q!=NULL)
				{
					if(q->dest==v)
					{
						r->next=q->next;
						delete q;
						cout<<" path deleted "<<endl;
						return;
					}
					r=q;
					q=q->next;
				}

			}
		}
		cout<<"Path not found"<<endl;
	}
	void delete_city()
	{
		string u;
		cout<<"Enter city to be deleted"<<endl;
		getline(cin, u);
		int c=check(u, u);
		cout<<"returned value from function is "<<c<<endl;
		if(c!=2)	// city not present
		{
			//cout<<"city not present..so cannot delete"<<endl;
			return;
		}
		// delete the paths first and the delete city link
		Node* p= start;
		while(p!=NULL)
		{
			Path *q=p->right;
			Path*r=NULL;
			while(q!=NULL)
			{
				if(p->right->dest==u)	// delete at 1st occurrence
				{
					p->right=q->next;
					delete q;
					q=p->right;
				}
				else if(q->dest==u)
				{
					r->next=q->next;
					delete q;
					q=r->next;
				}
				else
				{
					r=q;
					q=q->next;
				}
			}
			p=p->down;
		}
		// now delete the main city links
		p=start;
		Node* z=NULL;
		while(p!=NULL)
		{
			if(start->city==u)
			{
				start=start->down;
				delete p;
				cout<<"finally deleted"<<endl;
				return;
			}
			else if(p->city==u)
			{
				z->down=p->down;
				delete p;
				cout<<"Finally deleted"<<endl;
				return;
			}
			else
			{
				z=p;
				p=p->down;
			}
		}

	}
	void DFS()
	{
		string source;
		cout<<"Enter starting vertex"<<endl;
		getline(cin, source);
	}
};
int main()
{
	Graph G;
	G.initial_path();
	G.show();
	G.add_city();
	G.show();
	G.delete_path();
	G.show();
	/*G.delete_path();
	G.show();
	G.delete_path();
	G.show();
	G.delete_path();
	G.show();
	G.delete_path();
	G.show();
	G.delete_path();
	G.show();
	G.delete_path();
	G.show();
	G.delete_path();
	G.show();*/
	G.delete_city();
	G.show();
	G.delete_city();
	G.show();
	return 0;
}


