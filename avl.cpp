#include <iostream>
using namespace std;

struct Node {
    int playerID;
    Node* left;
    Node* right;
    int height;
    int key;
    int value;

    Node(int id, int k, int v) {
        playerID = id;
        key = k;
        value = v;
        left = nullptr;
        right = nullptr;
        height = 1; 
    }
};

class AVL{

    public:
    Node *root;
    AVL() { root = nullptr; };
    
    int height(Node* node) {
        if (node == nullptr) return -1;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

    int getBalance(Node* node) {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    Node* insert(Node* root, int id, int value, int key) {
        if (root == nullptr) {
            return new Node(id, key, value);
        }

        if (id < root->playerID) {
            root->left = insert(root->left, id, value, key);
        } else if (id > root->playerID) {
            root->right = insert(root->right, id, value, key);
        } else {
            return root;
        }

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

        if (balance > 1 && id < root->left->playerID) {
            return rightRotate(root);
        }

        if (balance < -1 && id > root->right->playerID) {
            return leftRotate(root);
        }

        if (balance > 1 && id > root->left->playerID) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && id < root->right->playerID) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current != nullptr && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* root, int id) {
        if (root == nullptr) {
            return root;
        }

        if (id < root->playerID) {
            root->left = deleteNode(root->left, id);
        } else if (id > root->playerID) {
            root->right = deleteNode(root->right, id);
        } else {
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = (root->left != nullptr) ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->playerID = temp->playerID;
                root->key = temp->key;
                root->value = temp->value;
                root->right = deleteNode(root->right, temp->playerID);
            }
        }

        if (root == nullptr) {
            return root;
        }

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0) {
            return rightRotate(root);
        }

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0) {
            return leftRotate(root);
        }

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    Node* rightRotate(Node* y){
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));
        return x;
    }

    Node* leftRotate(Node* x){
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));
        return y;
    }

    void preOrder(Node* root){
        if(root != nullptr){
            cout << root->playerID << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }
};


int main() {
    AVL tree;
    
    while(true) {
        int choice, id, key, value;
        cout << "\n1. Insert player\n2. Preorder traversal\n3. Delete player\n4. Exit\nEnter your choice: ";
        cin >> choice;
       switch (choice)
       {
        case 1:
            cout << "Enter player ID, key and value: ";
            cin >> id >> key >> value;
            tree.root = tree.insert(tree.root, id, value, key);
            break;
        case 2:
            cout << "Preorder traversal: ";
            tree.preOrder(tree.root);
            cout << endl;
            break;
        case 3:
            cout << "Enter player ID to delete: ";
            cin >> id;
            tree.root = tree.deleteNode(tree.root, id);
            break;
        case 4:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;

       }


    }

    return 0;
}

