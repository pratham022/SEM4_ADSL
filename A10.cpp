#include <bits/stdc++.h>
#include<fstream>
using namespace std;
class Department{
	int roll;
	string name,div,add;
public:
	Department()
{
		roll=0;
		name=div=add="\0";
}
	void read();
	void display();
	bool check(int r);
};
void Department::read()
{
	cout<<"Enter roll:";
	cin>>roll;
	cout<<"Enter name:";
	cin>>name;
	cout<<"Enter division:";
	cin>>div;
	cout<<"Enter address:";
	cin>>add;
}
void Department::display()
{
	cout<<"Roll:"<<roll<<endl;
	cout<<"Name:"<<name<<endl;
	cout<<"Division:"<<div<<endl;
	cout<<"Address:"<<add<<endl;
}
bool Department::check(int r)
{
	if(roll==r)
		return true;
	return false;
}
int main() {
	int n=0,i=0,j=0,k=0;
	int choice,roll;
	char old[]="record.txt";
	char newname[]= "new.txt";
	Department a[10],b[10],c[10],d[10];
	fstream f;
	//ifstream f1;
	f.open("record.txt",ios::out|ios::trunc);
	f.close();
	do{
		cout<<"Menu\n1.Add student\n2.Read from file\n3.Find a record\n4.Delete a record\n";
		cin>>choice;
		switch(choice){
		case 1:
			//ofstream f;
			cout<<"Enter number of students:";
			cin>>n;
			f.open(old,ios::out|ios::app|ios::binary);
			for(i=0;i<n;i++)
			{
				a[i].read();
				f.write((char *)& a[i], sizeof(a[i]));

			}
			f.close();
			break;
		case 2:
			//ifstream f1;
			i=0;
			f.open(old,ios::in);
			if(!f)
			{
				cout<<"File didn't open successfully\n";
			}
			while(f.eof()==0&&i<n)
			{
				f.read((char*)& b[i],sizeof(b[i]));
				b[i].display();
				cout<<endl;
				i++;
			}
			f.close();
			//delete b;
			for(i=0;i<n;i++)
			{
				b[i];
			}
			break;
		case 3:
			i=0;
			cout<<"Enter roll to find:";
			cin>>roll;
			f.open(old,ios::in);
			if(!f)
			{
				cout<<"File didn't open successfully\n";
			}
			while(f.eof()==0&&i<n)
			{
				f.read((char*)& d[i],sizeof(d[i]));
				if(d[i].check(roll))
				{
					cout<<"Found\n";
					break;
				}
				i++;
			}
			if(i==n)
			{
				cout<<"Not Found\n";
			}
			f.close();
			break;
		case 4:
			i=0;
			//f.open("record.txt",ios::in|ios::binary);
			fstream f1;
			f1.open(newname,ios::out);
			cout<<"Enter roll to delete:";
			cin>>roll;
			for(int i=0;i<n;i++)
			{
				if(!b[i].check(roll))
				{
					f1.write((char*)& b[i],sizeof(b[i]));
				}
				else
				{
					n--;
				}
			}
			cout<<remove(old);
			f1.close();
			cout<<rename(newname,old);
			break;
		
		}
	}while(choice!=0);
	return 0;
}
