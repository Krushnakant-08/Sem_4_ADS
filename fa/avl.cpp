#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

// A single train record
struct TrainRecord {
    int trainID;
    string destination;
    string arrivalTime;
};

// Linked list node to store multiple trains per station
struct TrainList {
    TrainRecord data;
    TrainList* next;

    TrainList(TrainRecord rec) {
        data = rec;
        next = nullptr;
    }
};

// AVL Tree node — keyed by SOURCE station name
// Each node holds ALL trains departing from that station
struct Node {
    string source;       // Key: starting station
    TrainList* trains;   // Linked list of train records from this station
    Node* left;
    Node* right;
    int height;

    Node(string src) {
        source = src;
        trains = nullptr;
        left = right = nullptr;
        height = 1;
    }
};

// ── Utility ─────────────────────────────────────────────────────────────────

int height(Node* n) {
    return n ? n->height : 0;
}

int balanceFactor(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

void updateHeight(Node* n) {
    if (n)
        n->height = 1 + max(height(n->left), height(n->right));
}

// Add a train record to the front of a node's linked list
void addTrain(Node* node, TrainRecord rec) {
    TrainList* entry = new TrainList(rec);
    entry->next = node->trains;
    node->trains = entry;
}

// ── AVL Rotations ────────────────────────────────────────────────────────────

Node* rotateRight(Node* y) {
    Node* x  = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left  = T2;

    updateHeight(y);
    updateHeight(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y  = x->right;
    Node* T2 = y->left;

    y->left  = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

Node* balance(Node* node) {
    updateHeight(node);
    int bf = balanceFactor(node);

    // Left Heavy
    if (bf > 1) {
        if (balanceFactor(node->left) < 0)          // Left-Right
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Heavy
    if (bf < -1) {
        if (balanceFactor(node->right) > 0)         // Right-Left
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// ── Insert ───────────────────────────────────────────────────────────────────

Node* insert(Node* root, string src, int id, string dest, string time) {
    if (!root) {
        Node* newNode = new Node(src);
        addTrain(newNode, {id, dest, time});
        return newNode;
    }

    if (src < root->source)
        root->left  = insert(root->left,  src, id, dest, time);
    else if (src > root->source)
        root->right = insert(root->right, src, id, dest, time);
    else {
        // Same source station — just add train to existing node's list
        addTrain(root, {id, dest, time});
        return root;  // No structural change needed
    }

    return balance(root);
}

// ── Search ───────────────────────────────────────────────────────────────────

// Returns the node for the given source station, or nullptr if not found
Node* search(Node* root, string src) {
    if (!root) return nullptr;
    if (src == root->source) return root;
    if (src  < root->source) return search(root->left,  src);
    return search(root->right, src);
}

// ── Display ──────────────────────────────────────────────────────────────────

void printTrains(Node* node) {
    cout << "\n  Trains departing from [ " << node->source << " ]:" << endl;
    cout << "  " << string(50, '-') << endl;
    cout << "  TrainID\tTo\t\tArrival Time" << endl;
    cout << "  " << string(50, '-') << endl;

    TrainList* cur = node->trains;
    while (cur) {
        cout << "  " << cur->data.trainID
             << "\t\t" << cur->data.destination
             << "\t\t" << cur->data.arrivalTime << endl;
        cur = cur->next;
    }
    cout << "  " << string(50, '-') << endl;
}

// Inorder traversal — prints all stations in alphabetical order
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printTrains(root);
    inorder(root->right);
}

// Display AVL tree structure
void displayTree(Node* node, int level = 0, string prefix = "Root: ") {
    if (!node) return;
    cout << string(level * 4, ' ') << prefix
         << "[" << node->source << "] (h=" << node->height << ")" << endl;
    if (node->left  || node->right) {
        if (node->left)  displayTree(node->left,  level + 1, "L--- ");
        if (node->right) displayTree(node->right, level + 1, "R--- ");
    }
}

// ── Main ─────────────────────────────────────────────────────────────────────

int main() {
    Node* root = nullptr;

    // Insert trains — same data as tree.cpp, keyed by SOURCE station
    root = insert(root, "CSMT",     30, "Dadar",    "5.00 PM");
    root = insert(root, "CSMT",     40, "Karjat",   "10.30 PM");
    root = insert(root, "CSMT",     90, "Kalyan",   "1.15 PM");
    root = insert(root, "Dadar",    50, "Lonavala", "9.00 AM");
    root = insert(root, "Dadar",    70, "Nashik",   "8.00 PM");
    root = insert(root, "Kalyan",   45, "Daund",    "10.00 AM");
    root = insert(root, "Kalyan",   65, "Sinnar",   "12.30 PM");
    root = insert(root, "Lonavala", 85, "Dadar",    "7.45 AM");

    // ── Show AVL Tree Structure ──────────────────────────────────────────────
    cout << "=== AVL Tree Structure (keyed by Source Station) ===" << endl;
    displayTree(root);

    // ── Show All Trains (Inorder = Alphabetical by Source) ──────────────────
    cout << "\n=== All Trains (Alphabetical by Source Station) ===" << endl;
    inorder(root);

    // ── Search by Source Station ─────────────────────────────────────────────
    cout << "\n=== Search by Source Station ===" << endl;

    string queries[] = {"CSMT", "Kalyan", "Nashik"};
    for (string& q : queries) {
        cout << "\nSearching for trains from: " << q << endl;
        Node* result = search(root, q);
        if (result)
            printTrains(result);
        else
            cout << "  No trains found departing from " << q << endl;
    }

    return 0;
}
