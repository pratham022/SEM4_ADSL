#include <QCoreApplication>
#include "iostream"
using namespace std;


class Node{
    int data;
    Node* left, *right;
    friend class Tree;
public:
    Node()
    {
        data = -1;
        left = right = NULL;
    }
    Node(int x)
    {
        data = x;
        left = right = NULL;
    }
};

class Stack{
    Node* data[100];
    int top;
public:
    Stack()
    {
        top = -1;
    }
    bool full()
    {
        if(top == 99)
        {
            cout<<"Stack full"<<endl;
            return true;
        }
        return false;
    }
    bool empty()
    {
        if(top == -1)
        {
            cout<<"stack empty"<<endl;
            return true;
        }
        return false;
    }
    void push(Node* t)
    {
        if(!full())
        {
            top++;
            data[top] = t;
        }
    }
    Node* pop()
    {
        if(!empty())
        {
            Node* t = data[top];
            top--;
            return t;
        }
    }
};

class StackNode{
    Node* link;
    int flag;
    friend class Tree;
};

class StackTwo{
    StackNode data[100];
    int top;
public:
    StackTwo()
    {
        top = -1;
    }
    bool full()
    {
        if(top == 99)
        {
            cout<<"Stack full"<<endl;
            return true;
        }
        return false;
    }
    bool empty()
    {
        if(top == -1)
        {
            cout<<"Stack empty"<<endl;
            return true;
        }
        return false;
    }
    void push(StackNode t)
    {
        if(!full())
        {
            top++;
            data[top] = t;
        }
    }
    StackNode pop()
    {
        if(!empty())
        {
            StackNode t = data[top];
            top--;
            return t;
        }
    }
};

class Tree{
    Node* root;
    friend int main(int argc, char *argv[]);
public:
    Tree()
    {
        root = NULL;
    }

    void create()
    {
        root = createRec();
    }

    Node* createRec()
    {
        int x;
        cout<<"Enter data..enter -1 to stop"<<endl;
        cin>>x;
        if(x!=-1)
        {
             Node* p = new Node(x);
             cout<<"Enter data to the left of "<<x<<endl;
             p->left = createRec();
             cout<<"Enter data to the right of "<<x<<endl;
             p->right = createRec();
             return p;
        }
        else
        {
            return NULL;
        }
    }

    void callInorder()
    {
        cout<<"Inorder: "<<endl;
        inorder(root);
        cout<<endl;
    }
    void inorder(Node* p)
    {
        if(p!=NULL)
        {
            inorder(p->left);
            cout<<p->data<<" ";
            inorder(p->right);
        }
    }

    void callPreorder()
    {
        cout<<"Preorder: "<<endl;
        preorder(root);
        cout<<endl;
    }
    void preorder(Node* p)
    {
        if(p!=NULL)
        {
            cout<<p->data<<" ";
            preorder(p->left);
            preorder(p->right);
        }
    }

    void callPostorder()
    {
        cout<<"Postorder: "<<endl;
        postorder(root);
        cout<<endl;
    }
    void postorder(Node* p)
    {
        if(p!=NULL)
        {
            postorder(p->left);
            postorder(p->right);
            cout<<p->data<<" ";
        }
    }

    void preorderNonRec()
    {
        cout<<"Non recursive preorder"<<endl;
        Stack st;
        Node* p = root;
        while (p!=NULL)
        {
            cout<<p->data<<" ";
            st.push(p);
            p = p->left;
        }
        while (!st.empty())
        {
            p = st.pop();
            p = p->right;
            while(p!=NULL)
            {
                cout<<p->data<<" ";
                st.push(p);
                p = p->left;
            }
        }
    }

    void inorderNonRec()
    {
        cout<<"Non recursive inorder"<<endl;
        Node* p = root;
        Stack st;
        while(p!=NULL)
        {
            st.push(p);
            p = p->left;
        }
        while(!st.empty())
        {
            p = st.pop();
            cout<<p->data<<" ";
            p = p->right;
            while(p!=NULL)
            {
                st.push(p);
                p = p->left;
            }
        }
    }

    void postNonRec()
    {
        cout<<"Non recursive postorder"<<endl;
        StackTwo st;
        Node* p = root;
        StackNode temp;
        while(p!=NULL)
        {
            temp.link = p;
            temp.flag = 0;
            st.push(temp);
            p = p->left;
        }
        while(!st.empty())
        {
            temp = st.pop();
            temp.flag++;
            if(temp.flag == 1)      // element is popped for the 1st time (Left completed)
            {
                p = temp.link;
                st.push(temp);
                p = p->right;
                while(p!=NULL)
                {
                    temp.link = p;
                    temp.flag = 0;
                    st.push(temp);
                    p = p->left;
                }
            }
            else if(temp.flag == 2)
            {
                p = temp.link;
                cout<<p->data<<" ";
            }
        }
    }

    void callprintLeafInternal()
    {
        int leaf[100];
        int inter[100];
        int rootval;
        int i=0, j=0;
        printLeafInternal(root);
    }
    void printLeafInternal(Node* p)
    {
        if(p!=NULL)
        {
            if(p==root)
            {
                cout<<"Root: "<<p->data<<endl;
            }
            else if(p->left == NULL && p->right == NULL && p!=root)
            {
                cout<<"Leaf: "<<p->data<<endl;
            }
            else
            {
                cout<<"Internal: "<<p->data<<endl;
            }

            printLeafInternal(p->left);
            printLeafInternal(p->right);
        }
    }

    void callCheck(Tree obj2)
    {
        if(check(root, obj2.root))
        {
            cout<<"Both the trees are equal"<<endl;
        }
        else
        {
            cout<<"Unequal trees"<<endl;
        }
    }
    bool check(Node* t1, Node* t2)
    {
        if(t1==NULL && t2!=NULL)
        {
            return false;
        }
        else if(t2==NULL && t1!=NULL)
        {
            return false;
        }
        else if(t1!=NULL && t2!=NULL)
        {
            if(t1->data != t2->data)
            {
                return false;
            }
            return (check(t1->left, t2->left) && check(t1->right, t2->right));
        }
        else
        {
            return true;
        }
    }
    Node* callMirror()
    {
        Node* root2;
        root2 = mirror(root);
        return root2;
    }
    Node* mirror(Node* t)
    {
        if(t!=NULL)
        {
            Node* p = new Node(t->data);
            p->left = mirror(t->right);
            p->right = mirror(t->left);
            return p;
        }
        else
            return NULL;
    }

    void callErase()
    {
        root = erase(root);
    }
    Node* erase(Node* t)
    {
        if(t!=NULL)
        {
            t->left = erase(t->left);
            t->right = erase(t->right);
            delete t;
            return NULL;
        }
    }

    void operator =(Tree obj1)
    {
        cout<<"function called!"<<endl;
        root = assignRec(obj1.root);
    }

    Node* assignRec(Node* t)
    {
        if(t!=NULL)
        {
            Node* p = new Node(t->data);
            t->left = assignRec(t->left);
            t->right = assignRec(t->right);
            return t;
        }
        else
            return NULL;
    }
};
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Tree obj, obj2;
    int choice, ip=1;
    obj.create();
    do{
        cout<<"1) Assign this tree to another [operator=]"<<endl;
        cout<<"2) Erase all nodes in a binary tree"<<endl;
        cout<<"3) Create a mirror image of the tree"<<endl;
        cout<<"4) Check two binary trees are equal or not"<<endl;
        cout<<"5) Inorder, Preorder, Postorder traversal of tree(recursive and non-recursive)"<<endl;
        cout<<"6) Print internal and leaf nodes"<<endl;
        cin>>choice;

        switch (choice) {
        case 1:
            obj2 = obj;
            cout<<"Tree 1 assigned to Tree 2"<<endl;
            obj2.callPreorder();
            obj2.callInorder();
            obj2.callPostorder();
            break;
        case 2:
            obj.callErase();
            obj.callPreorder();
            obj.callInorder();
            obj.callPostorder();
            break;
        case 3:
            obj2.root = obj.callMirror();
            obj2.callPreorder();
            obj2.callInorder();
            obj2.callPostorder();
            break;
        case 4:
            obj.callCheck(obj2);
            break;
        case 5:
            obj.callPreorder();
            obj.callInorder();
            obj.callPostorder();
            obj.preorderNonRec();
            obj.inorderNonRec();
            obj.postNonRec();
            break;
        case 6:
            obj.callprintLeafInternal();
            break;
        default:
            cout<<"Wrong input"<<endl;
            break;
        }

        cout<<"Press 1 to continue"<<endl;
        cin>>ip;
    }while(ip==1);
    return a.exec();
}
