#include <iostream>
using namespace std;

struct node
{
    public:
    node* left;
    node* right;
    char data;
    
    node(char v)
    {
        left=NULL; right=NULL; data=v;
    }
};

bool insert(node* root, char v)
{
    int ch;
    
    if(root==NULL)
    {
        return false;
    }
    else
    {
        cout << "Current node is: " << root->data << endl;
        cout << "Do you want to insert node to left or right of " << root->data << ":" << endl;
        cout << "1.Left    2.Right" << endl;
        cin >> ch;

        switch(ch)
        {
            case 1:
                if(root->left == NULL)
                {
                    root->left = new node(v);
                    cout << "Node inserted at left successfully" << endl;
                    return true;
                }
                else 
                {
                    return insert(root->left, v);
                }
                break;

            case 2:
                if (root->right == NULL)
                {
                    root->right = new node(v);
                    cout << "Node inserted right successfully" << endl;
                    return true;
                }
                else 
                {
                    return insert(root->right, v);
                }
                break;
        }
    }
    return true;
}



void inorder(node* r)
{
    if(r==NULL)
        return;
    inorder(r->left);
    cout << r->data << " ";
    inorder(r->right);
}

void preorder(node* r)
{
    if(r==NULL)
        return;
    cout << r->data << " ";
    preorder(r->left);
    preorder(r->right);
}

int main()
{
    node* root = new node('1');
    char val;
    int c;

    do {
        cout << "enter the node you want to insert" << " ";    
        cin >> val;
        insert(root, val);
        
        cout << "Do you want to continue press: 1.Yes 2.No" << endl;
        cin >> c;
    } while(c == 1);
    
    cout << "Inorder display:-";
    inorder(root);
    cout << endl;
    cout << "Preorder display:-";
    preorder(root);
    
    return 0;
}