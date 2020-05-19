/*
 * a.cpp
 *
 *  Created on: Dec 30, 2019
 *      Author: se
 */
/*A Dictionary stores keywords & its meanings. Provide facility for adding new
keywords, deleting keywords, updating values of any entry, assign a given tree
into another tree (=). Provide facility to display whole data sorted in ascending/
Descending order. Also find how many maximum comparisons may require for
finding any keyword. Use Binary Search Tree for implementation.*/
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class Word{
public:
	string keyword, meaning;
};string keyword, meaning;
class Node{
public:
	Node *left, *right;
	Word W;
	Node(string a, string b)
	{
		W.keyword=a;
		W.meaning=b;
		left=right=NULL;
	}

};
class BST{
	Node* root;
public:
	BST()
	{
		root=NULL;
	}
	void create();
	Node* insert(Node* t, string a, string b);
	void show_asc();
	void inorder(Node* t);
	void add_new(string a, string b);
	void Del(string a);
	Node* Delete(Node* t, string a);
	void update(string a, string b);
	void update1(Node* t,string a, string b);
	Node* copy(Node* t);
	void operator=(BST);
	void show_des();
	void des(Node*);
	int max_cnt();
	int max_comp(Node* t);
};
int main()
{
	BST obj, var;
	string a, b;
	int choice;
	obj.create();
	/*var=obj;
	var.show_asc();
	var.show_des();
	cout<<"\n";
	cout<<var.max_cnt()<<endl;*/

	/*cout<<"Enter new keyword and meaning"<<endl;
	getline(cin,a);
	getline(cin,b);
	obj.add_new(a,b);
	cout<<"tree after addition is"<<endl;
	obj.show();
	cout<<"Enter the keyword to be deleted"<<endl;
	getline(cin,a);
	obj.Del(a);
	cout<<"Enter the keyword whose meaning you want to update"<<endl;
	getline(cin, a);
	cout<<"Enter the updated meaning"<<endl;
	getline(cin, b);
	obj.update(a,b);
	obj.show();*/
	do{
		cout<<"\nEnter choice:\n1-add new keyword\n";
		cout<<"2-deleting a keyword\n3-updating meaning of a keyword\n";
		cout<<"4-assign one tree to another\n5-display data in ascending order";
		cout<<"6-display data in descending order\n";
		cout<<"7-maximum comparisons needed to search an element\n";
		cout<<"-1 to exit"<<endl;
		cin>>choice;
		cin.ignore(1);
		switch(choice)
		{
		case 1:
			cout<<"Enter new keyword and meaning"<<endl;
			getline(cin,a);
			getline(cin,b);
			obj.add_new(a,b);
			cout<<"tree after addition is"<<endl;
			obj.show_asc();
			break;
		case 2:
			cout<<"Enter the keyword to be deleted"<<endl;
			getline(cin,a);
			obj.Del(a);
			obj.show_asc();
			break;
		case 3:
			cout<<"Enter the keyword whose meaning you want to update"<<endl;
			getline(cin, a);
			cout<<"Enter the updated meaning"<<endl;
			getline(cin, b);
			obj.update(a,b);
			obj.show_asc();
			break;
		case 4:
			var=obj;
			var.show_asc();
			break;
		case 5:
			obj.show_asc();
			break;
		case 6:
			obj.show_des();
			break;
		case 7:
			cout<<"Maximum comparisons: "<<obj.max_cnt()<<endl;
			break;
		case -1:
			break;
			break;
		default:
			cout<<"Wrong input"<<endl;
		}
	}while(choice!=-1);
	return 0;
}
void BST::create()
{
	int choice;
	string a, b;
	while(1)
	{
		cout<<"Enter -1 to exit..press any key to continue"<<endl;
		cin>>choice;
		cin.ignore(1);
		if(choice==-1)
				break;
		cout<<"Enter keyword"<<endl;
		getline(cin,a);
		cout<<"Enter meaning"<<endl;
		getline(cin, b);
		root=insert(root,a,b);
	}
}
Node* BST::insert(Node* t, string a, string b)
{

	if(t==NULL)
	{
		t=new Node(a,b);
		return t;
	}
	else
	{
		if(a<t->W.keyword)
		{
			t->left=insert(t->left, a, b);
			return t;
		}
		else if(a>t->W.keyword)
		{
			t->right=insert(t->right, a, b);
			return t;
		}
		else
			return t;
	}
}
void BST::show_asc()
{
	/*cout<<"Root of the tree is"<<endl;
	cout<<root->keyword<<endl;*/
	cout<<"keyword\tmeaning\n"<<endl;
	inorder(root);
}
void BST::inorder(Node* t)
{
	if(t!=NULL)
	{
		inorder(t->left);
		cout<<t->W.keyword<<"\t"<<t->W.meaning<<endl;
		inorder(t->right);
	}
}
void BST::add_new(string a, string b)
{
	root=insert(root, a, b);
}
void BST::Del(string a)
{
	root=Delete(root, a);
}
Node* BST::Delete(Node* t, string a)
{
	if(t==NULL)
			return NULL;
	else if(a<t->W.keyword)
	{
		t->left=Delete(t->left, a);
		return t;
	}
	else if(a>t->W.keyword)
	{
		t->right=Delete(t->right, a);
		return t;
	}
	// data is found here
	if(t->left==NULL && t->right==NULL)
	{
		delete t;
		return NULL;
	}
	else if(t->left==NULL) // here it implies that t->right!=NULL thus right child present
	{
		Node* p=t->right;
		delete t;
		return p;
	}
	else if(t->right==NULL)
	{
		Node* p=t->left;
		delete t;
		return p;
	}
	Node* p=t->right;
	while(p->left!=NULL)
	{
		p=p->left;
	}
	swap(t->W.keyword, p->W.keyword);
	swap(t->W.meaning, p->W.meaning);
	t->right=Delete(p, a);
	return t;
}
void BST::update(string a, string b)
{
	update1(root,a, b);
}
void BST::update1(Node* t,string a, string b)
{
	if(t==NULL)
	{
		cout<<"data not found..cannot update"<<endl;
		return;
	}
	else
	{
		if(a<t->W.keyword)
		{
			update1(t->left,a, b);
		}
		else if(a>t->W.keyword)
		{
			update1(t->right,a, b);
		}
		else
		{
			t->W.meaning=b;
			cout<<"successfully updated"<<endl;
			//return;
		}
	}
}
Node* BST::copy(Node* t)
{
	if(t==NULL)
			return NULL;
	else
	{
		t->left=copy(t->left);
		t->right=copy(t->right);
		return t;
	}
}
void BST::operator=(BST obj)
{
	root=copy(obj.root);
}
void BST::show_des()
{
	cout<<"Keyword\tMeaning\n"<<endl;
	des(root);
}
void BST::des(Node* t)
{
	if(t!=NULL)
	{
		des(t->right);
		cout<<t->W.keyword<<" "<<t->W.meaning<<endl;
		des(t->left);
	}
}
int BST::max_cnt()
{
	return max_comp(root);
}
int BST::max_comp(Node* t)
{
	int l,r;
	if(t==NULL)
			return 0;
	else
	{
		l=max_comp(t->left);
		r=max_comp(t->right);
		if(l>r)
				return 1+l;
		return 1+r;
	}
}
