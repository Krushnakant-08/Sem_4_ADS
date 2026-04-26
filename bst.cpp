#include <iostream>
#include <stack>
using namespace std;

class Node {
    public:
    int data;
    Node* left;
    Node* right;

    Node(int data){
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};

Node* insert(Node* root, int data){
    if(!root) return new Node(data);

    if(root->data < data) root->right = insert(root->right, data);
    else if(root->data > data) root->left = insert(root->left, data);
    else return root;
}

void totalNodes(Node* root, int& a){
    if(!root) return;

    a++;
    totalNodes(root->left, a);
    totalNodes(root->right, a);
}

void leafNodes(Node* root, int& a){
    if(!root) return;

    if(!root->left && !root->right) a++;
    leafNodes(root->left, a);
    leafNodes(root->right, a);
}

void inOrderIterative(Node* root){
    if(!root) return;

    stack<Node*> s;
    Node* curr = root;
    while(curr || !s.empty()){
        while(curr){
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();
        cout<<curr->data<<' ';
        curr = curr->right;
    }
}

void preOrderIterative(Node* root){
    if(!root) return;

    stack<Node*> s;
    s.push(root);
    while(!s.empty()){
        Node* curr = s.top();
        s.pop();
        cout<<curr->data<<' ';

        if(curr->right) s.push(curr->right);
        if(curr->left) s.push(curr->left);
    }
}

void postOrderIterative(Node* root){
    if(!root) return;

    stack<Node*> s1, s2;
    s1.push(root);
    while(!s1.empty()){
        Node* curr = s1.top();
        s1.pop();
        s2.push(curr);

        if(curr->left) s1.push(curr->left);
        if(curr->right) s1.push(curr->right);
    }

    while(!s2.empty()){
        cout<<s2.top()->data<<' ';
        s2.pop();
    }
}

int main(){
    Node * root = nullptr;

    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 40);
    insert(root, 60);
    int nodes = 0;
    int leaf = 0;

    totalNodes(root, nodes);
    leafNodes(root, leaf);
    cout<<nodes<<' '<<leaf<<endl;
    cout<<"In-order (Iterative): ";
    inOrderIterative(root);
    cout<<endl;
    cout<<"Pre-order (Iterative): ";
    preOrderIterative(root);
    cout<<endl;
    cout<<"Post-order (Iterative): ";
    postOrderIterative(root);
    cout<<endl;
}