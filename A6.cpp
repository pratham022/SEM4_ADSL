//Implement all the functions of a dictionary (ADT) using hashing. Data: Set of
//(key, value) pairs, Keys are mapped to values, Keys must be comparable, Keys
//must be unique Standard Operations: Insert(key, value), Find(key), Delete(key)
//(Use linear probing with and without replacement. Calculate the average search
//cost for both.)

#include<iostream>
#include<string>
using namespace std;
string to_upper(string s)
{
	for(int i=0;i<s.length();i++)
	{
		if(s[i]>=97 && s[i]<=122)
		{
			s[i]=s[i]-32;
		}
	}
	return s;
}
class Word{
public:
	string data, value;
	int flag;
};
class HashTable{
public:
	Word dictionary[26];
public:
	HashTable()
	{
		for(int i=0;i<26;i++)
		{
			dictionary[i].flag=0;
		}
	}
	void insertWithoutReplace()
	{
//		cin.ignore(1);
		string a, b;
		int index, i;
		cout<<"Enter name"<<endl;
		getline(cin, a);
		cout<<"Enter meaning"<<endl;
		getline(cin, b);
		a=to_upper(a);
		b=to_upper(b);
		cout<<a<<"\t"<<b<<endl;

		index=a[0];
		index -= 65;
		index = index%26;
		cout<<"Element should be inserted at index "<<index<<endl;
		if(dictionary[index].flag==0)
		{
			// put into the slot
			dictionary[index].data=a;
			dictionary[index].value=b;
			dictionary[index].flag=1;
			cout<<"Element inserted at index "<<index<<endl;
		}
		else
		{
			i=index;
			do{
				if(dictionary[i].flag==0)
				{
					// put in slot
					dictionary[i].data=a;
					dictionary[i].value=b;
					dictionary[i].flag=1;
					cout<<"Element inserted at index "<<i<<endl;
					break;
				}
				i=(i+1)%26;

			}while(i!=index);
		}
	}
	void insertWithReplace()
	{
//		cin.ignore(1);
		string a, b;
		Word temp;
		int index, i;
		cout<<"Enter name"<<endl;
		getline(cin, a);
		cout<<"Enter meaning"<<endl;
		getline(cin, b);
		a=to_upper(a);
		b=to_upper(b);
		cout<<a<<"\t"<<b<<endl;

		index=a[0];
		index -= 65;
		index = index%26;
		cout<<"Element should be inserted at index "<<index<<endl;
		if(dictionary[index].flag==0)
		{
			//index not occupied
			// put into the slot
			dictionary[index].data=a;
			dictionary[index].value=b;
			dictionary[index].flag=1;
			cout<<"Element inserted at index "<<index<<endl;
			return;
		}
		else	// slot already occupied
		{
			int c=dictionary[index].data[0];
			c-=65;
			cout<<"value of c is "<<c<<endl;

			// case 1 element that has already occupied is InVALID
			if(c!=index)
			{
				temp=dictionary[index];
				dictionary[index].data=a;
				dictionary[index].value=b;
				dictionary[index].flag=1;
				cout<<"new element added at index "<<index<<endl;
				//check if old element can be precisely placed or not
				if(dictionary[c].flag==0)
				{
					// place old element to its correct index...
					// if that index is unoccupied
					dictionary[c]=temp;
					dictionary[c].flag=1;
					cout<<"new element added at index "<<c<<endl;
					return;
				}
				else
				{
					// start linear probing from the occupied index
					i=index;
					do{
						if(dictionary[i].flag==0)
						{
							// put in slot
							dictionary[i]=temp;
							cout<<"Old Element inserted at index "<<i<<endl;
							return;
						}
						i=(i+1)%26;

					}while(i!=index);
				}//				already occupied element is VALID element
			}

			else//				already occupied element is VALID element
			{
				i=index;
				do{
					if(dictionary[i].flag==0)
					{
						// put in slot
						dictionary[i].data=a;
						dictionary[i].value=b;
						dictionary[i].flag=1;
						cout<<"Element inserted at index "<<i<<endl;
						break;
					}
					i=(i+1)%26;

				}while(i!=index);
			}
		}

	}
	int call_find()
	{
		string s;
		cout<<"Enter word"<<endl;
		getline(cin, s);
		s=to_upper(s);
		return find(s);
	}
	int find(string s)
	{
//		cin.ignore(1);
		int index=s[0];
//		cout<<"value of c is "<<c<<endl;
		index -= 65;
		index = index%26;
		// we have the required index now
		if(dictionary[index].data == s)
		{
			// word found at the 1st chance
			cout<<"word found at index "<<index<<endl;
			return index;
		}
		else
		{
			// start linear probe
			int i=index+1;
			while(i!=index)
			{
				if(dictionary[i].data == s)
				{
					cout<<"Word found at index "<<i<<endl;
					return i;
				}
				i=(i+1)%26;
			}
			cout<<"word not found"<<endl;
			return -1;
		}
	}
	void delete_()
	{
//		cin.ignore(1);
		string s;
		Word tem;
		cout<<"Enter the word to be deleted "<<endl;
		getline(cin, s);
		s=to_upper(s);
		int index=find(s);
		cout<<"find() returns "<<index<<" value in delete()"<<endl;
		if(index!=-1)
		{
			// word found here
			dictionary[index].data="";
			dictionary[index].value="";
			dictionary[index].flag=0;
			// resetting done
			cout<<"resetting done"<<endl;
			cout<<"checking for replacement!"<<endl;
			int i=(index+1)%26;
			while(i!=index)
			{
				if(dictionary[i].flag == 1)
				{
					string temp=dictionary[i].data;
					int c= temp[0];
					c -= 65;
					c= c%26;
					if(c==index)
					{
						cout<<"scope of replacement"<<endl;
						tem=dictionary[i];
						dictionary[i].data="";
						dictionary[i].value="";
						dictionary[i].flag=0;
						dictionary[index]=tem;
						cout<<"replacement done!"<<endl;
						break;
					}
				}
				i=(i+1)%26;
			}
		}

	}
	void show()
	{
		for(int i=0;i<26;i++)
		{
			cout<<dictionary[i].data<<"\t"<<dictionary[i].value<<"\t"<<dictionary[i].flag<<endl;
		}
	}
};
int main()
{
	HashTable obj;
	int choice;
	while(1)
	{
		cout<<"Enter 1- insert elements with replacement"<<endl;
		cout<<"		 2- insert elements without replacement"<<endl;
		cout<<"		 3- find a particular key"<<endl;
		cout<<"		 4-delete a particular key"<<endl;
		cout<<"		 5- show table"<<endl;
		cout<<" 	 	-1 to exit"<<endl;
		cin>>choice;
		cin.ignore(1);
		switch(choice)
		{
			case 1:
					obj.insertWithReplace();
					break;
			case 2:
					obj.insertWithoutReplace();
					break;
			case 3:
					obj.call_find();
					break;
			case 4:
					obj.delete_();
					break;
			case 5:
					obj.show();
					break;
			case -1:
					break;
					break;
			default:
				cout<<"wrong input"<<endl;
				break;

		}
	}
//	obj.insertWithReplace();
//	obj.insertWithReplace();
//	obj.insertWithReplace();
//	obj.insertWithReplace();
//	obj.show();
//	obj.call_find();
//	obj.delete_();
//	cout<<"now showing the table"<<endl;
//	obj.show();
	return 0;
}
