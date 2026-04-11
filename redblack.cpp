// Implement the scenario of a file system which maintains directory structure using the Red-Black Tree. 
// Each node in the tree represents a directory, and the tree is balanced to ensure efficient insertion, deletion, and display operations when navigating through the file system.
#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    string name;
    Color color;
    Node *left, *right, *parent;

    Node(string name){
        this->name = name;
        this->color = RED;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }
};

class RedBlackTree {
private:
    Node *root;

    void rotateLeft(Node *&pt) {
        Node *pt_y = pt->right;
        pt->right = pt_y->left;
        if (pt->right != nullptr)
            pt->right->parent = pt;

        pt_y->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_y;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_y;
        else
            pt->parent->right = pt_y;

        pt_y->left = pt;
        pt->parent = pt_y;
    }

    void rotateRight(Node *&pt) {
        Node *pt_y = pt->left;
        pt->left = pt_y->right;
        if (pt->left != nullptr)
            pt->left->parent = pt;

        pt_y->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_y;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_y;
        else
            pt->parent->right = pt_y;

        pt_y->right = pt;
        pt->parent = pt_y;
    }

    void fixViolation(Node *&pt) {
        Node *parent_pt = nullptr;
        Node *grandparent_pt = nullptr;

        while ((pt != root) && (pt->color == RED) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grandparent_pt = parent_pt->parent;

            // Case A: Parent of PT is left child of grandparent_pt
            if (parent_pt == grandparent_pt->left) {
                Node *uncle_pt = grandparent_pt->right;

                // Case 1: The uncle of PT is also red, only recoloring is required
                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grandparent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grandparent_pt;
                } else { // Case 2 and Case 3: Uncle is black
                    if (pt == parent_pt->right) {
                        rotateLeft(parent_pt);
                        swap(pt, parent_pt);
                    }
                    rotateRight(grandparent_pt);
                    swap(parent_pt->color, grandparent_pt->color);
                    pt = parent_pt;
                }
            } else { // Case B: Parent of PT is right child of grandparent_pt
                Node *uncle_pt = grandparent_pt->left;

                // Case 1: The uncle of PT is also red, only recoloring is required
                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                    grandparent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grandparent_pt;
                } else { // Case 2 and Case 3: Uncle is black
                    if (pt == parent_pt->left) {
                        rotateRight(parent_pt);
                        swap(pt, parent_pt);
                    }
                    rotateLeft(grandparent_pt);
                    swap(parent_pt->color, grandparent_pt->color);
                    pt = parent_pt;
                }
            }
        }
        root->color = BLACK;
    }

public:
    RedBlackTree() { root = nullptr; }

    void insert(const string &name) {
        Node *pt = new Node(name);
        root = BSTInsert(root, pt);
        fixViolation(pt);
    }

    Node* BSTInsert(Node* &root, Node* &pt) {
        if (root == nullptr)
            return pt;

        if (pt->name < root->name) {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        } else if (pt->name > root->name) {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }

        return root;
    }

    void inorder(Node *root) {
        if (root == nullptr)
            return;

        inorder(root->left);
        cout << root->name << " ";
        inorder(root->right);
    }

    void preorder(Node *root) {
        if (root == nullptr)
            return;

        cout << root->name << " ";
        preorder(root->left);
        preorder(root->right);
    }

    void postorder(Node *root) {
        if (root == nullptr)
            return;

        postorder(root->left);
        postorder(root->right);
        cout << root->name << " ";
    }

    void display() {
        cout << "Directory Structure (Inorder Traversal): ";
        inorder(root);
        cout << endl;

        cout << "Directory Structure (Preorder Traversal): ";
        preorder(root);
        cout << endl;

        cout << "Directory Structure (Postorder Traversal): ";
        postorder(root);
        cout << endl;
    }
};

int main() {
    RedBlackTree rbt;
    rbt.insert("root");
    rbt.insert("home");
    rbt.insert("user");
    rbt.insert("documents");
    rbt.insert("pictures");
    rbt.insert("music");

    rbt.display();

    return 0;
}