/*
 * a.cpp
 *
 *  Created on: Jan 6, 2020
 *      Author: se
 */
//Create inorder threaded binary tree and perform inorder, preorder traversal.
#include<iostream>
using namespace std;
class Node{
public:
	int data;
	int lbit, rbit, child;
	Node* left, *right;
	Node(int x)
	{
		data=x;
		left=right=NULL;
		lbit=rbit=1;
	}
};
class TBT{
	Node* root;
public:
	TBT()
	{
		root=new Node(-1);
		root->left= root->right=root;
	}
	void create();
	void create_rec(Node* t, int child);
	void preorder();
	Node* pre_succ(Node* t);
	void inorder();
	Node* in_succ(Node* t);
	void postorder();
	Node* post_succ(Node* t);
};
int main()
{
	TBT T;
	T.create();
	cout<<"Preorder: ";
	T.preorder();
	cout<<"\n";
	cout<<"Inorder: ";
	T.inorder();
	cout<<"\n";
	cout<<"Postorder: ";
	T.postorder();
	return 0;
}
void TBT::create()
{
	create_rec(root, 0);
}
void TBT::create_rec(Node* father, int child)
{
	int x;
	cout<<"Enter data..enter -1 to stop"<<endl;
	cin>>x;
	if(x==-1)
			return;

	Node* t=new Node(x);
	if(child==0)	// 0 stand for left child and 1 for right
	{
		t->child=child;
		t->right=father;
		t->left=father->left;
		father->left=t;
		father->lbit=0;
	}
	else if(child==1)
	{
		t->child=child;
		t->left=father;
		t->right=father->right;
		father->right=t;
		father->rbit=0;
	}
	cout<<"Enter data to left of "<<t->data<<endl;
	create_rec(t, 0);
	cout<<"Enter data to the right of "<<t->data<<endl;
	create_rec(t, 1);
}
/*void TBT::preorder()
{
	Node* t=root;
	while(t->lbit==0)
	{
		t=t->left;
		cout<<t->data<<" ";
	}
	while(t!=root)
	{
		t=t->right;	//
		if(t->child==1)
				cout<<t->data<<" ";
		if(t->rbit==0)
		{
			t=t->right;
			cout<<t->data<<" ";
			while(t->lbit==0)
			{
				t=t->left;
				cout<<t->data<<" ";
			}
		}
	}
}*/
void TBT::preorder()
{
	Node* t=root->left;
	while(t!=root)
	{
		cout<<t->data<<" ";
		t=pre_succ(t);
	}
}
Node* TBT::pre_succ(Node* t)
{
	if(t->lbit==0)
			return t->left;
	while(t->rbit==1 && t!=root)
		t=t->right;
	return t->right;
}
void TBT::inorder()
{
	Node* t=root->left;
	while(t->lbit==0)
			t=t->left;
	while(t!=root)
	{
		cout<<t->data<<" ";
		t=in_succ(t);
	}
}
Node* TBT::in_succ(Node* t)
{
	if(t->rbit==1)
		return t->right;
	t=t->right;
	while(t->lbit==0)
			t=t->left;
	return t;
}
void TBT::postorder()
{
	Node* t=root->left;
	while(t->lbit==0 || t->rbit==0)
	{
		if(t->lbit==0)
			t=t->left;
		else
			t=t->right;
	}
	while(t!=root)
	{
		cout<<t->data<<" ";
		t=post_succ(t);
	}
}
Node* TBT::post_succ(Node* t)
{
	if(t->child == 1)	// right child
	{
		while(t->lbit==0)
			t=t->left;
		return t->left;
	}
	else
	{
		while(t->rbit == 0)
			t=t->right;
		t=t->right;

		if(t->rbit==1)
			return t;
		t=t->right;
		while(t->lbit==0 || t->rbit==0)
		{
			if(t->lbit==0)
				t=t->left;
			else
				t=t->right;
		}
		return t;
	}
}
/*	if(t->child==1)	//right child
	{
		while(t->lbit==0)
			t=t->left;
		return t->left;
	}
	//else if(t->child==0)//left child
	else
	{
		// first reach its parent
		while(t->lbit==0)
			t=t->right;
		t=t->right;	//parent reached
		if(t->rbit==0)
		{
			t=t->right;
			while(t->lbit==0 ||t->rbit==0)
			{
				if(t->lbit==0)
					t=t->left;
				else
					t=t->right;
			}
			return t;
		}
		else
			return t;
 *
 */
