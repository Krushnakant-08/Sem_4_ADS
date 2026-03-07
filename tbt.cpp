#include <iostream>
using namespace std;
struct Node
{
    Node *left;
    Node *right;
    int data;
    int lth;
    int rth;
    Node()
    {
        data = 0;
        left = NULL;
        right = NULL;
        lth = 0;
        rth = 0;
    }
    Node(int d)
    {
        data = d;
        left = NULL;
        right = NULL;
        lth = 0;
        rth = 0;
    }
};

Node* insert(Node *root, int key)
{
    Node *temp = new Node(key);
    Node *parent = NULL;

    if (root == NULL)
    {
        root = temp;
    }
    else
    {
        Node *curr = root;

        while (curr != NULL)
        {
            if (key == curr->data)
            {
                cout << "Duplicate key not allowed\n";
                return root;
            }

            parent = curr;

            if (key < curr->data)
            {
                if (curr->lth == 1)
                    curr = curr->left;
                else
                    break;
            }
            else
            {
                if (curr->rth == 1)
                    curr = curr->right;
                else
                    break;
            }
        }
             cout<<"parent="<<parent->data<<endl;
             cout<<"curr="<<curr->data<<endl;
       
        if (key < parent->data)
        {
            temp->left = parent->left;
            temp->right = parent;
            parent->lth = 1;
            parent->left = temp;
        }
        else
        {
            temp->left = parent;
            temp->right = parent->right;
            parent->rth = 1;
            parent->right = temp;   
        }
    }
    return root;
}
bool search(Node *root, int key)
{
    while (root != NULL)
    {
        if (root->data == key)
        {
            cout << "Entered node" << " " << key << " " << "is present in tree" << endl;
            return true;
        }

        else if (root->data > key)
        {
            if(root->lth == 0) return false;
            root = root->left;
        }
        else
        {
            if(root->rth == 0) return false;
            root = root->right;
        }
    }

}

// Inorder Successor
Node *inorderSuccessor(Node *curr)
{
    if (curr->rth == 0)
        return curr->right;

    curr = curr->right;
    while (curr->lth == 1)
        curr = curr->left;

    return curr;
}

bool inorder(Node *root)
{
    if (root == NULL)
    {
        cout << "Tree empty\n";
        return true;
    }

    Node *curr = root;

    // Move to leftmost node
    while (curr->lth == 1)
    {
        curr = curr->left;
    }

    while (curr != NULL)
    {
        cout << curr->data << " ";
        curr = inorderSuccessor(curr);
    }
    return true;
}

int main()
{
    Node *root = NULL;
    int v, c;
    do
    {
        cin >> v;
        root = insert(root, v); // insert
        cout << "Do you want to add more, 0. Yes   2. No\n";
        cin >> c;
    } while (c == 0);
    cout << endl;
    inorder(root); // display
                   /*   int key;
                      cout<<"Enter node to be searched:"<<endl;
                      cin>>key;
                      search(root,key); //search
                      */
    return 1;
}