#include <iostream>
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
    cout<<nodes<<' '<<leaf;
}