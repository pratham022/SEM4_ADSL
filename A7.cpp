#include <QCoreApplication>
#include "iostream"
using namespace std;

class Node
{
    string identifier, value, scope, data_type;
    int flag, chain;
public:
    Node() {
        identifier = value = scope = data_type = "NIL";
        flag = 0;
        chain = -1;
    }
    friend class HashTable;
};

class HashTable{
    Node data[26];
public:
    void show()
    {
        cout<<"index\tidentifier\tvalue\tscope\tdata_type\tchain"<<endl;
        for(int i=0;i<26;i++)
        {
            cout<<i<<"\t"<<data[i].identifier<<"\t\t"<<data[i].value<<"\t"<<data[i].scope<<"\t"<<data[i].data_type<<"\t\t"<<data[i].chain<<endl;
        }
    }

    int getIndex(string a)
    {
        int ind = a[0];
        ind -= 97;
        ind = ind%26;
        return ind;
    }

    int linearProbe(int index, string a, string b, string c, string d, int chain)
    {
        int i;
        i = index+1;
        do{

            if(data[i].flag == 0)   // empty location found
            {
                data[i].identifier = a;
                data[i].value = b;
                data[i].scope = c;
                data[i].data_type = d;
                data[i].flag = 1;
                data[i].chain = chain;
                break;
            }
            i = (i+1)%26;
        }while(i!=index);

        return i;
    }

    void doChaining(int addind, int index, string a)
    {
        int i, j;
        i = addind+1;              // we start searching from added index +1..we are finding here if any element same as that of the incoming element family is already present or not
        bool flag = false;
        do{

            if(data[i].identifier[0] == a[0])
            {
                j = i;
                flag = true;
                while(data[j].chain != -1)
                {
                    j = data[j].chain;
                }
                break;
            }
            i = (i+1)%26;
        }while(i!=addind);

        if(flag)
        {
            data[j].chain = addind;
        }
        data[addind].chain = -1;
    }

    void insertWithoutReplacement()
    {
        string a, b, c, d;
        int i, j, addind;
        cout<<"Enter identifier:"<<endl;
        getline(cin, a);
        int index = getIndex(a);
        cout<<"Element should be inserted at index: "<<index<<endl;
        cout<<"Enter value"<<endl;
        getline(cin, b);
        cout<<"Enter scope"<<endl;
        getline(cin, c);
        cout<<"Enter data_type"<<endl;
        getline(cin, d);

        if(data[index].flag == 0)       // index unoccupied..place it onto that index
        {
            data[index].identifier = a;
            data[index].value = b;
            data[index].scope = c;
            data[index].data_type = d;
            data[index].flag = 1;
            addind = index;
        }                               // here there is a possiblility that a valid entry may be present at
                                        // an index afterwards...so we have to linear probe through the entire table to execute chaining
                                        // eg. add a, b, bb then delete b after that add ba

        else                            // index is already occupied...search for next empty location
        {
            addind = linearProbe(index, a, b, c, d, -1); // addind is used to tell to which index the incoming element is added
        }
        // now we will do chaining
        doChaining(addind, index, a);
    }

    int deleteTheEntry(int index, string a)
    {
        int i, j;
        i = index;
        do{

            if(data[i].identifier[0] == a[0])
            {
                j = i;
                while(data[j].identifier != a && j!=-1)
                {
                    i = j;
                    j = data[j].chain;
                }
                if(j == -1)
                {
                    cout<<"Entry not found!"<<endl;
                    break;
                }
                cout<<i<<" "<<index<<endl;
                    data[i].chain = data[j].chain;

                data[j].identifier = "NIL";
                data[j].value = "NIL";
                data[j].scope = "NIL";
                data[j].data_type = "NIL";
                data[j].flag = 0;
                break;
            }
            i = (i+1)%26;
        }while(i!=index);

        for(int t=0;t<26;t++)
        {
            cout<<"for loop executing"<<endl;
            cout<<"value of j: "<<j<<endl;
            if(data[t].chain == j)
            {
                data[t].chain = data[j].chain;
                break;
            }
        }
        data[j].chain = -1;
        return j;
    }

    void deleteWithoutReplacement()
    {
        string a;
        int i, j;
        cout<<"Enter the identifier you want to delete"<<endl;
        getline(cin, a);
        int index = getIndex(a);
        int delind = deleteTheEntry(index, a);
    }

    void insertWithReplacement()
    {
        string a, b, c, d;
        int i, j, addind;
        cout<<"Enter identifier:"<<endl;
        getline(cin, a);
        int index = getIndex(a);
        cout<<"Element should be inserted at index: "<<index<<endl;
        cout<<"Enter value"<<endl;
        getline(cin, b);
        cout<<"Enter scope"<<endl;
        getline(cin, c);
        cout<<"Enter data_type"<<endl;
        getline(cin, d);

        if(data[index].flag == 0)               // index unoccupied
        {
                data[index].identifier = a;
                data[index].value = b;
                data[index].scope = c;
                data[index].data_type = d;
                data[index].flag = 1;
                addind = index;

                doChaining(addind, index, a);
        }
        else                                    // index already occupied
        {
            if(data[index].identifier[0] == a[0])   // deserving element already present
            {
                addind = linearProbe(index, a, b, c, d, -1);
                doChaining(addind, index, a);
            }
            else
            {
                int index2, addind2;
                index2 = getIndex(data[index].identifier);
                if(data[index2].flag == 0)      // that index is unoccupied
                {
                    data[index2].identifier = data[index].identifier;
                    data[index2].value = data[index].value;
                    data[index2].scope = data[index].scope;
                    data[index2].data_type = data[index].data_type;
                    data[index2].flag = 1;
                    addind2 = index2;
                    data[index].identifier = data[index].value = data[index].scope = data[index].data_type = "NIL";
                    data[index].flag = 0;
                    data[index].chain = -1;
                    doChaining(addind2, index2, data[addind2].identifier);


                }
                else                            // index already occupied
                {
                    addind2 = linearProbe(index2, data[index].identifier, data[index].value, data[index].scope, data[index].data_type, data[index].chain);
                    data[index].identifier = data[index].value = data[index].scope = data[index].data_type = "NIL";
                    data[index].flag = 0;
                    data[index].chain = -1;
                    if(data[index2].identifier[0] == data[addind2].identifier[0])
                    {
                        data[index2].chain = addind2;
                    }
                }
                data[index].identifier = a;
                data[index].value = b;
                data[index].scope = c;
                data[index].data_type = d;
                data[index].flag = 1;
                addind = index;
                doChaining(addind, index, a);
            }
        }
    }

    void deleteWithReplacement()
    {
        string a;
        int i, j, temp;
        cout<<"Enter the identifier you want to delete"<<endl;
        getline(cin, a);
        int index = getIndex(a);
        int delind = deleteTheEntry(index, a);

        i = delind+1;
        do{

            temp = data[i].identifier[0];
            temp -= 97;
            temp = temp%26;
            if(temp == delind)
            {
                //this element must be placed at the deleted index
                data[delind].identifier = data[i].identifier;
                data[delind].value = data[i].value;
                data[delind].scope = data[i].scope;
                data[delind].data_type = data[i].data_type;
                data[delind].flag = 1;
                data[delind].chain = data[i].chain;

                data[i].identifier = data[i].value = data[i].scope = data[i].data_type = "NIL";
                data[i].flag = 0;
                data[i].chain = -1;
                break;
            }
            i = (i+1)%26;
        }while(i!=delind);

        if(i!=delind)
        {
            for(int t=0;t<26;t++)
            {
                if(data[t].chain == i)
                {
                    data[t].chain = delind;
                }
            }
        }
    }

    void findEntry()
    {
        string a;
        cout<<"Enter identifier to find"<<endl;
        getline(cin, a);
        int ind = find(a);
        if(ind == -1)
        {
            cout<<"Entry Not found "<<endl;
        }
        else
        {
            cout<<"Entry found at index "<<ind<<endl;
        }
    }

    void retrieve()
    {
        string a;
        cout<<"Enter identifier to retrieve"<<endl;
        getline(cin, a);
        int ind = find(a);
        if(ind == -1)
        {
            cout<<"Entry Not found "<<endl;
        }
        else
        {
            cout<<"Identifier: "<<data[ind].identifier<<endl;
            cout<<"Value: "<<data[ind].value<<endl;
            cout<<"Scope: "<<data[ind].scope<<endl;
            cout<<"Data Type: "<<data[ind].data_type<<endl;
        }
    }

    void modify()
    {
        string a, b, c, d;
        cout<<"Enter identifier to modify its attributes"<<endl;
        getline(cin, a);
        int ind = find(a);
        if(ind == -1)
        {
            cout<<"Entry Not found "<<endl;
        }
        else
        {
            cout<<"Enter value"<<endl;
            getline(cin, b);
            cout<<"Enter scope"<<endl;
            getline(cin, c);
            cout<<"Enter data type"<<endl;
            getline(cin, d);

            data[ind].value = b;
            data[ind].scope = c;
            data[ind].data_type = d;
        }
    }
    int find(string a)
    {
        int ind = a[0];
        ind -= 97;
        ind = ind%26;
        int i, j=-1;
        i = ind;
        do{
            if(data[i].identifier[0] == a[0])
            {
                j = i;
                while(data[j].identifier != a && j!= -1)
                {
                    j = data[j].chain;
                }
                if(j == -1)
                {
                    return -1;
                }
                break;
            }
            i = (i+1)%26;
        }while(i!=ind);
        return j;
    }

};
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    HashTable obj;
    int choice, ip;
//    obj.show();
//    //obj.deleteWithReplacement();
//    //obj.deleteWithReplacement();
//    //obj.show();
//    obj.insertWithReplacement();
//    obj.show();
//    obj.insertWithReplacement();
//    obj.show();
//    obj.insertWithReplacement();
//    obj.show();
//    obj.insertWithReplacement();
//    obj.show();
//    obj.deleteWithoutReplacement();
//    obj.show();
//    obj.insertWithReplacement();
//    obj.show();
//     obj.findEntry();
//     obj.modify();
//     obj.retrieve();
    do{
        cout<<"1-Insert with replacement\n2-Insert without replacement\n3-Delete with replacement"<<endl;
        cout<<"4-Delete without replacement\n5-Determine if present or not\n6-Modify the attributes of identifier"<<endl;
        cout<<"7-Retrieve the attributes of an identifier\n8-Display the symbol table"<<endl;
        cin>>choice;
        cin.ignore(1);
        switch (choice) {
        case 1:
            obj.insertWithReplacement();
            break;
        case 2:
            obj.insertWithoutReplacement();
            break;
        case 3:
            obj.deleteWithReplacement();
            break;
        case 4:
            obj.deleteWithoutReplacement();
            break;
        case 5:
            obj.findEntry();
            break;
        case 6:
            obj.modify();
            break;
        case 7:
            obj.retrieve();
            break;
        case 8:
            obj.show();
            break;
        default:
            cout<<"Wrong input"<<endl;
            break;
        }

        cout<<"Press 1 to continue"<<endl;
        cin>>ip;
    }while(ip == 1);
    return a.exec();
}

// important test case!
//data[0].identifier = "bab";
//data[0].chain = 4;
//data[1].identifier = "b";
//data[1].chain = 0;
//data[4].identifier = "ba";
//data[4].chain = 5;
//data[5].identifier = "bc";
//data[5].chain = -1;
//data[0].flag= data[1].flag = data[4].flag = data[5].flag = 1;
