#include <iostream>  
#include <queue>  
using namespace std;  
class Node {  
public:  
    string key;       // word  
    string value;     // meaning  
    Node* left;  
    Node* right;  
  
    Node(string k, string v) {  
        key = k;  
        value = v;  
        left = right = NULL;  
    }  
};  
  
class Dictionary {  
    Node* root;  
    Node* insert(Node* root, string key, string value) {  
        if (root == NULL)  
            return new Node(key, value);  
  
        if (key < root->key)  
            root->left = insert(root->left, key, value);  
        else if (key > root->key)  
            root->right = insert(root->right, key, value);  
        else {  
            cout << "Duplicate key found. Updating meaning.\n";  
            root->value = value;   // Handle duplicate by updating value  
        }  
        return root;  
    }  
  
    Node* findMin(Node* root) {  
        while (root->left != NULL)  
            root = root->left;  
        return root;  
    }  
  
    Node* deleteNode(Node* root, string key) {  
        if (root == NULL) return root;  
  
        if (key < root->key)  
            root->left = deleteNode(root->left, key);  
        else if (key > root->key)  
            root->right = deleteNode(root->right, key);  
        else {  
            // Node with one child or no child  
            if (root->left == NULL) {  
                Node* temp = root->right;  
                delete root;  
                return temp;  
            }  
            else if (root->right == NULL) {  
                Node* temp = root->left;  
                delete root;  
                return temp;  
            }  
  
            // Node with two children  
            Node* temp = findMin(root->right);  
            root->key = temp->key;  
            root->value = temp->value;  
            root->right = deleteNode(root->right, temp->key);  
        }  
        return root;  
    }  
  
    Node* search(Node* root, string key) {  
        if (root == NULL || root->key == key)  
            return root;  
  
        if (key < root->key)  
            return search(root->left, key);  
  
        return search(root->right, key);  
    }  
  
    void inorder(Node* root) {  
        if (root != NULL) {  
            inorder(root->left);  
            cout << root->key << " : " << root->value << endl;  
            inorder(root->right);  
        }  
    }  
  
    void mirror(Node* root) {  
        if (root == NULL) return;  
  
        mirror(root->left);  
        mirror(root->right);  
  
        Node* temp = root->left;  
        root->left = root->right;  
        root->right = temp;  
    }  
  
    Node* copyTree(Node* root) {  
        if (root == NULL) return NULL;  
  
        Node* newNode = new Node(root->key, root->value);  
        newNode->left = copyTree(root->left);  
        newNode->right = copyTree(root->right);  
  
        return newNode;  
    }  
  
public:  
    Dictionary() {  
        root = NULL;  
    }  
  
    void insertWord(string key, string value) {  
        root = insert(root, key, value);  
    }  
  
    void deleteWord(string key) {  
        root = deleteNode(root, key);  
    }  
  
    void searchWord(string key) {  
        Node* result = search(root, key);  
        if (result)  
            cout << "Word Found: " << result->key << " = " << result->value << endl;  
        else  
            cout << "Word not found.\n";  
    }  
  
    void display() {  
        if (root == NULL)  
            cout << "Dictionary is empty.\n";  
        else  
            inorder(root);  
    }  
  
    void mirrorDictionary() {  
        mirror(root);  
        cout << "Mirror image created.\n";  
    }  
  
    Dictionary createCopy() {  
        Dictionary newDict;  
        newDict.root = copyTree(this->root);  
        return newDict;  
    }  
  
    void displayLevelWise() {  
        if (root == NULL) {  
            cout << "Dictionary is empty.\n";  
            return;  
        }  
  
        queue<Node*> q;  
        q.push(root);  
  
        while (!q.empty()) {  
            Node* temp = q.front();  
            q.pop();  
  
            cout << temp->key << " : " << temp->value << "  ";  
  
            if (temp->left)  
                q.push(temp->left);  
            if (temp->right)  
                q.push(temp->right);  
        }  
        cout << endl;  
    }  
};  
  
int main() {  
    Dictionary dict;  
    int choice;  
    string word, meaning;  
  
    do {  
        cout << "\n---- Dictionary Menu ----\n";  
        cout << "1. Insert Word\n";  
        cout << "2. Delete Word\n";  
        cout << "3. Search Word\n";  
        cout << "4. Display Dictionary (Inorder)\n";  
        cout << "5. Mirror Dictionary\n";  
        cout << "6. Create Copy of Dictionary\n";  
        cout << "7. Display Level Wise\n";  
        cout << "0. Exit\n";  
        cout << "Enter choice: ";  
        cin >> choice;  
  
        switch (choice) {  
        case 1:  
            cout << "Enter word: ";  
            cin >> word;  
            cout << "Enter meaning: ";  
            cin >> meaning;  
            dict.insertWord(word, meaning);  
            break;  
  
        case 2:  
            cout << "Enter word to delete: ";  
            cin >> word;  
            dict.deleteWord(word);  
            break;  
  
        case 3:  
            cout << "Enter word to search: ";  
            cin >> word;  
            dict.searchWord(word);  
            break;  
  
        case 4:  
            dict.display();  
            break;  
  
        case 5:  
            dict.mirrorDictionary();  
            break;  
  
        case 6: {  
            Dictionary copyDict = dict.createCopy();  
            cout << "Copied Dictionary (Inorder):\n";  
            copyDict.display();  
            break;  
        }  
  
        case 7:  
            dict.displayLevelWise();  
            break;  
}  
} while (choice != 0);  
return 0;  
}