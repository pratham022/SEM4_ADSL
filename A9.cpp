#include "iostream"
using namespace std;

class Node{
    int data;
    Node* next;
    friend class Set;
public:
    Node(int x)
    {
        data = x;
        next = NULL;
    }
};

class Set{
    Node* head;
public:
    Set()
    {
        head = NULL;
    }
    void add()
    {
        int x;
        cout<<"Enter element to be added"<<endl;
        cin>>x;

        if(contains(x))
        {
            cout<<"Element already present"<<endl;
            return;
        }
        addAtEnd(x);
    }

    void addAtEnd(int x)
    {
        if(head == NULL)
            head = new Node(x);
        else
        {
            Node* p = head;
            while(p->next!=NULL)
            {
                p = p->next;
            }
            p->next = new Node(x);
        }
    }
    void show()
    {
        Node* p = head;
        while(p!=NULL)
        {
            cout<<p->data<<" ";
            p = p->next;
        }
    }
    void remove()
    {
        int x;
        cout<<"Enter the value to be removed"<<endl;
        cin>>x;
        Node* p, *q;
        if(head->data == x)
        {
            p = head;
            head = head->next;
            delete p;
        }
        else
        {
            p = head;
            while(p!=NULL)
            {
                if(p->data == x)
                {
                    q->next = p->next;
                    delete p;
                }
                q=p;
                p = p->next;
            }
        }
    }
    bool contains(int x)
    {
        Node* p = head;
        while(p!=NULL)
        {
            if(p->data == x)
                return true;
            p = p->next;
        }
        return false;
    }
    int size()
    {
        Node* p = head;
        int c = 0;
        while(p!=NULL)
        {
            c++;
            p = p->next;
        }
        return c;
    }

    Set intersection(Set obj2)
    {
        Node* p, *q;
        p = head;
        Set obj3;
        while(p!=NULL)
        {
            q = obj2.head;
            while(q!=NULL)
            {
                if(p->data == q->data)
                {
                    obj3.addAtEnd(p->data);
                }
                q = q->next;
            }
            p = p->next;
        }
    return obj3;
    }

    Set findUnion (Set obj2)
    {
        Node* p, *q;
        Set obj3;
        p = head;
        while(p!=NULL)
        {
            obj3.addAtEnd(p->data);
            p = p->next;
        }
        q = obj2.head;
        while(q!=NULL)
        {
        if(obj3.contains(q->data))
        {
        //cout<<"data already present"<<endl;
        }
            else
            {
                obj3.addAtEnd(q->data);
            }
            q = q->next;
        }
        return obj3;
    }

    Set findDifference(Set obj2)
    {
        Set obj3;
        Node* p;
        p = head;
        while(p!=NULL)
        {
            if(obj2.contains(p->data))
            {
                // don't put this data into resultant set
            }
            else
            {
                obj3.addAtEnd(p->data);
            }
            p = p->next;
        }
        return obj3;
    }

    bool subset(Set obj2)
    {
        Node* p = obj2.head;
        while(p!=NULL)
        {
            if(!contains(p->data))
            {
                return false;
            }
            p = p->next;
        }
        return true;
    }
};
int main(int argc, char *argv[])
{

    Set obj, obj2, obj3;
    int choice, ip=1;
    int x, n, y;

    // first we create both the sets
    cout<<"Enter number of elements in set 1"<<endl;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter element"<<endl;
        cin>>x;
        obj.addAtEnd(x);
    }
    cout<<"Enter number of elements in set 2"<<endl;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter element"<<endl;
        cin>>x;
        obj2.addAtEnd(x);
    }

    do{
        cout<<"1)Add (newElement)"<<endl;
        cout<<"2)Remove (element)"<<endl;
        cout<<"3)Check if the element is present or not"<<endl;
        cout<<"4)Size of the set"<<endl;
        cout<<"5)Intersection of 2 sets"<<endl;
        cout<<"6)Union of 2 sets"<<endl;
        cout<<"7)Difference of 2 sets"<<endl;
        cout<<"8)Check if given set is a subset or not"<<endl;
        cout<<"9)Display both the sets"<<endl;
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Press 1 to add into set 1 and 2 to add into set 2"<<endl;
            cin>>y;
            if(y==1)
                obj.add();
            else if(y==2)
                obj2.add();
            else
                cout<<"Invalid"<<endl;
            break;
        case 2:
            cout<<"Press 1 to remove from set 1 and 2 to remove from set 2"<<endl;
            cin>>y;
            if(y==1)
                obj.remove();
            else if(y==1)
                obj2.remove();
            else
                cout<<"invalid"<<endl;
            break;
        case 3:
            cout<<"Enter 1 to find in set 1 and 2 to find in set 2"<<endl;
            cin>>y;
            if(y==1)
            {
                cout<<"Enter element you want to find"<<endl;
                cin>>x;
                if(obj.contains(x))
                    cout<<"Element present"<<endl;
                else
                    cout<<"Element not present"<<endl;
            }
            else if(y==2)
            {
                cout<<"Enter element you want to find"<<endl;
                cin>>x;
                if(obj2.contains(x))
                    cout<<"Element present"<<endl;
                else
                    cout<<"Element not present"<<endl;
            }
            else
                cout<<"invalid"<<endl;
            break;
        case 4:
            cout<<"Enter 1 to find size of set 1 and 2 to find size of set 2"<<endl;
            cin>>y;
            if(y==1)
                cout<<"Size of the set is: "<<obj.size()<<endl;
            else if(y==2)
                cout<<"size of the set 2: "<<obj2.size()<<endl;
            break;
        case 5:
            obj3 = obj.intersection(obj2);
            cout<<"Intersection of 2 sets"<<endl;
            obj3.show();
            break;
        case 6:
            obj3 = obj.findUnion(obj2);
            cout<<"Union of 2 sets: "<<endl;
            obj3.show();
            break;
        case 7:
            obj3 = obj.findDifference(obj2);
            cout<<"Difference: "<<endl;
            obj3.show();
            break;
        case 8:
            if(obj.subset(obj2))
            {
                cout<<"Subset"<<endl;
            }
            else
                cout<<"Not a subset"<<endl;
            break;
        case 9:
            cout<<"Set 1: ";
            obj.show();
            cout<<endl;
            cout<<"Set 2: ";
            obj2.show();
            cout<<endl;
            break;
        default:
            cout<<"Invalid operation"<<endl;
            break;
        }
        cout<<"Press 1 to continue"<<endl;
        cin>>ip;
    }while(ip==1);

    return 0;
}

