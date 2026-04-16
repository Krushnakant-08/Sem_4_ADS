#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

const int MAX_KEYS = 3; // Order 4 B+ Tree (max 3 keys, 4 children)

struct Record {
    int trainID;
    string source;        // Starting station
    string destination;   // Ending station
    string arrivalTime;
};

struct Node {
    int keys[MAX_KEYS + 1];      
    Node* children[MAX_KEYS + 2];
    Record* records[MAX_KEYS + 1];
    Node* next;
    int numKeys;
    bool isLeaf;

    Node(bool leaf) {
        isLeaf = leaf;
        numKeys = 0;
        next = nullptr;
        for (int i = 0; i < MAX_KEYS + 2; i++)
            children[i] = nullptr;
        for (int i = 0; i < MAX_KEYS + 1; i++)
            records[i] = nullptr;
    }
};

// Search for a key in the B+ Tree
Record* search(Node* root, int key) {
    if (!root) return nullptr;

    Node* cur = root;

    // Traverse internal nodes
    while (!cur->isLeaf) {
        int i = 0;
        while (i < cur->numKeys && key >= cur->keys[i])
            i++;
        cur = cur->children[i];
    }

    // Search in the leaf node
    for (int i = 0; i < cur->numKeys; i++) {
        if (cur->keys[i] == key)
            return cur->records[i];
    }
    return nullptr;
}

// Insert a key into a leaf node (may overflow)
void insertInLeaf(Node* leaf, int key, Record* rec) {
    int i = leaf->numKeys - 1;

    // Shift keys and records to make room
    while (i >= 0 && leaf->keys[i] > key) {
        leaf->keys[i + 1] = leaf->keys[i];
        leaf->records[i + 1] = leaf->records[i];
        i--;
    }
    leaf->keys[i + 1] = key;
    leaf->records[i + 1] = rec;
    leaf->numKeys++;
}

// Insert a key into an internal node (may overflow)
void insertInInternal(Node* node, int key, Node* rightChild) {
    int i = node->numKeys - 1;

    // Shift keys and children to make room
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i + 1] = node->keys[i];
        node->children[i + 2] = node->children[i + 1];
        i--;
    }
    node->keys[i + 1] = key;
    node->children[i + 2] = rightChild;
    node->numKeys++;
}

// Split a leaf node and return the new right node and the key to push up
Node* splitLeaf(Node* leaf, int &pushUpKey) {
    Node* newLeaf = new Node(true);

    int totalKeys = leaf->numKeys; // This is MAX_KEYS + 1 after overflow insert
    int splitIndex = totalKeys / 2;

    // Move second half to the new leaf
    int j = 0;
    for (int i = splitIndex; i < totalKeys; i++) {
        newLeaf->keys[j] = leaf->keys[i];
        newLeaf->records[j] = leaf->records[i];
        leaf->keys[i] = 0;
        leaf->records[i] = nullptr;
        j++;
    }
    newLeaf->numKeys = totalKeys - splitIndex;
    leaf->numKeys = splitIndex;

    // Maintain linked list
    newLeaf->next = leaf->next;
    leaf->next = newLeaf;

    // Key to push up is the first key of the new leaf
    pushUpKey = newLeaf->keys[0];

    return newLeaf;
}

// Split an internal node and return the new right node and the key to push up
Node* splitInternal(Node* node, int &pushUpKey) {
    Node* newNode = new Node(false);

    int totalKeys = node->numKeys; // MAX_KEYS + 1 after overflow insert
    int midIndex = totalKeys / 2;

    // The middle key is pushed up, not kept in either node
    pushUpKey = node->keys[midIndex];

    // Move keys and children after the middle to the new node
    int j = 0;
    for (int i = midIndex + 1; i < totalKeys; i++) {
        newNode->keys[j] = node->keys[i];
        node->keys[i] = 0;
        j++;
    }
    newNode->numKeys = totalKeys - midIndex - 1;

    // Move children
    j = 0;
    for (int i = midIndex + 1; i <= totalKeys; i++) {
        newNode->children[j] = node->children[i];
        node->children[i] = nullptr;
        j++;
    }

    node->keys[midIndex] = 0;
    node->numKeys = midIndex;

    return newNode;
}

// Recursive insert helper — returns a new child and pushUpKey if a split occurred
Node* insertHelper(Node* node, int key, Record* rec, int &pushUpKey, bool &didSplit) {
    if (node->isLeaf) {
        // Insert into leaf
        insertInLeaf(node, key, rec);

        // Check overflow
        if (node->numKeys > MAX_KEYS) {
            didSplit = true;
            return splitLeaf(node, pushUpKey);
        }
        didSplit = false;
        return nullptr;
    }

    // Find appropriate child
    int i = 0;
    while (i < node->numKeys && key >= node->keys[i])
        i++;

    int childPushUpKey;
    bool childSplit;
    Node* newChild = insertHelper(node->children[i], key, rec, childPushUpKey, childSplit);

    if (childSplit) {
        // Insert the pushed-up key and new child into this node
        insertInInternal(node, childPushUpKey, newChild);

        // Check overflow
        if (node->numKeys > MAX_KEYS) {
            didSplit = true;
            return splitInternal(node, pushUpKey);
        }
    }

    didSplit = false;
    return nullptr;
}

// Main insert function
Node* insert(Node* root, int id, string src, string dest, string time) {
    Record* rec = new Record{id, src, dest, time};

    // If tree is empty, create first leaf
    if (!root) {
        root = new Node(true);
        root->keys[0] = id;
        root->records[0] = rec;
        root->numKeys = 1;
        return root;
    }

    int pushUpKey;
    bool didSplit;
    Node* newChild = insertHelper(root, id, rec, pushUpKey, didSplit);

    if (didSplit) {
        // Root was split — create a new root
        Node* newRoot = new Node(false);
        newRoot->keys[0] = pushUpKey;
        newRoot->children[0] = root;
        newRoot->children[1] = newChild;
        newRoot->numKeys = 1;
        return newRoot;
    }

    return root;
}

// Display all records by traversing leaf linked list (sorted order)
void displayAll(Node* root) {
    if (!root) return;

    // Go to the leftmost leaf
    Node* cur = root;
    while (!cur->isLeaf)
        cur = cur->children[0];

    // Traverse linked list of leaves
    cout << "------------------------------------------------------------" << endl;
    cout << "TrainID\tFrom\t\tTo\t\tArrival Time" << endl;
    cout << "------------------------------------------------------------" << endl;
    while (cur) {
        for (int i = 0; i < cur->numKeys; i++) {
            cout << cur->records[i]->trainID << "\t"
                 << cur->records[i]->source << "\t\t"
                 << cur->records[i]->destination << "\t\t"
                 << cur->records[i]->arrivalTime << endl;
        }
        cur = cur->next;
    }
    cout << "------------------------------------------------------------" << endl;
}

// Display tree structure (level-wise)
void displayTree(Node* node, int level) {
    if (!node) return;

    cout << "Level " << level << " [";
    for (int i = 0; i < node->numKeys; i++) {
        if (i > 0) cout << " | ";
        cout << node->keys[i];
    }
    cout << "]";
    if (node->isLeaf) cout << " (leaf)";
    cout << endl;

    if (!node->isLeaf) {
        for (int i = 0; i <= node->numKeys; i++) {
            displayTree(node->children[i], level + 1);
        }
    }
}

int main() {
    Node* root = nullptr;

    root = insert(root, 30, "CSMT",     "Dadar",    "5.00 PM");
    root = insert(root, 40, "CSMT",     "Karjat",   "10.30 PM");
    root = insert(root, 50, "Dadar",    "Lonavala", "9.00 AM");
    root = insert(root, 45, "Kalyan",   "Daund",    "10.00 AM");
    root = insert(root, 85, "Lonavala", "Dadar",    "7.45 AM");
    root = insert(root, 90, "CSMT",     "Kalyan",   "1.15 PM");
    root = insert(root, 70, "Dadar",    "Nashik",   "8.00 PM");
    root = insert(root, 65, "Kalyan",   "Sinnar",   "12.30 PM");

    cout << "\n=== B+ Tree Structure ===" << endl;
    displayTree(root, 0);

    cout << "\n=== All Train Records (Sorted by TrainID) ===" << endl;
    displayAll(root);

    // Search for a train
    cout << "\n=== Search Results ===" << endl;
    int searchKeys[] = {45, 85, 99};
    for (int key : searchKeys) {
        Record* r = search(root, key);
        if (r)
            cout << "Train " << key << " found: "
                 << r->source << " -> " << r->destination
                 << " at " << r->arrivalTime << endl;
        else
            cout << "Train " << key << " not found." << endl;
    }

    return 0;
}