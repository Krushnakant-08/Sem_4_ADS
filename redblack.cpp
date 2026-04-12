#include <iostream>
#include <string>
using namespace std;

enum Color { RED, BLACK };

struct Dir {
    string name;
    Color color;
    Dir* left;
    Dir* right;
    Dir* rbParent;
    Dir* parentDir;
    Dir* childrenRoot;
};

Dir* NIL;
Dir* rootDir;
Dir* currentDir;

Dir* newDirNode(const string& name, Dir* parentDir) {
    Dir* node = new Dir;
    node->name = name;
    node->color = RED;
    node->left = NIL;
    node->right = NIL;
    node->rbParent = NIL;
    node->parentDir = parentDir;
    node->childrenRoot = NIL;
    return node;
}

void leftRotate(Dir*& treeRoot, Dir* x) {
    Dir* y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->rbParent = x;

    y->rbParent = x->rbParent;
    if (x->rbParent == NIL) treeRoot = y;
    else if (x == x->rbParent->left) x->rbParent->left = y;
    else x->rbParent->right = y;

    y->left = x;
    x->rbParent = y;
}

void rightRotate(Dir*& treeRoot, Dir* x) {
    Dir* y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->rbParent = x;

    y->rbParent = x->rbParent;
    if (x->rbParent == NIL) treeRoot = y;
    else if (x == x->rbParent->right) x->rbParent->right = y;
    else x->rbParent->left = y;

    y->right = x;
    x->rbParent = y;
}

void fixInsert(Dir*& treeRoot, Dir* z) {
    while (z->rbParent->color == RED) {
        if (z->rbParent == z->rbParent->rbParent->left) {
            Dir* y = z->rbParent->rbParent->right;
            if (y->color == RED) {
                z->rbParent->color = BLACK;
                y->color = BLACK;
                z->rbParent->rbParent->color = RED;
                z = z->rbParent->rbParent;
            } else {
                if (z == z->rbParent->right) {
                    z = z->rbParent;
                    leftRotate(treeRoot, z);
                }
                z->rbParent->color = BLACK;
                z->rbParent->rbParent->color = RED;
                rightRotate(treeRoot, z->rbParent->rbParent);
            }
        } else {
            Dir* y = z->rbParent->rbParent->left;
            if (y->color == RED) {
                z->rbParent->color = BLACK;
                y->color = BLACK;
                z->rbParent->rbParent->color = RED;
                z = z->rbParent->rbParent;
            } else {
                if (z == z->rbParent->left) {
                    z = z->rbParent;
                    rightRotate(treeRoot, z);
                }
                z->rbParent->color = BLACK;
                z->rbParent->rbParent->color = RED;
                leftRotate(treeRoot, z->rbParent->rbParent);
            }
        }
    }
    treeRoot->color = BLACK;
}

Dir* searchDir(Dir* treeRoot, const string& name) {
    Dir* cur = treeRoot;
    while (cur != NIL) {
        if (name < cur->name) cur = cur->left;
        else if (name > cur->name) cur = cur->right;
        else return cur;
    }
    return NIL;
}

bool insertDir(Dir*& treeRoot, const string& name, Dir* parentDir) {
    Dir* z = newDirNode(name, parentDir);
    Dir* y = NIL;
    Dir* x = treeRoot;

    while (x != NIL) {
        y = x;
        if (z->name < x->name) x = x->left;
        else if (z->name > x->name) x = x->right;
        else {
            delete z;
            return false;
        }
    }

    z->rbParent = y;
    if (y == NIL) treeRoot = z;
    else if (z->name < y->name) y->left = z;
    else y->right = z;

    fixInsert(treeRoot, z);
    return true;
}

Dir* minimum(Dir* node) {
    while (node->left != NIL) node = node->left;
    return node;
}

void transplant(Dir*& treeRoot, Dir* u, Dir* v) {
    if (u->rbParent == NIL) treeRoot = v;
    else if (u == u->rbParent->left) u->rbParent->left = v;
    else u->rbParent->right = v;
    v->rbParent = u->rbParent;
}

void fixDelete(Dir*& treeRoot, Dir* x) {
    while (x != treeRoot && x->color == BLACK) {
        if (x == x->rbParent->left) {
            Dir* w = x->rbParent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->rbParent->color = RED;
                leftRotate(treeRoot, x->rbParent);
                w = x->rbParent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->rbParent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(treeRoot, w);
                    w = x->rbParent->right;
                }
                w->color = x->rbParent->color;
                x->rbParent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(treeRoot, x->rbParent);
                x = treeRoot;
            }
        } else {
            Dir* w = x->rbParent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->rbParent->color = RED;
                rightRotate(treeRoot, x->rbParent);
                w = x->rbParent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->rbParent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(treeRoot, w);
                    w = x->rbParent->left;
                }
                w->color = x->rbParent->color;
                x->rbParent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(treeRoot, x->rbParent);
                x = treeRoot;
            }
        }
    }
    x->color = BLACK;
}

bool deleteDir(Dir*& treeRoot, const string& name) {
    Dir* z = searchDir(treeRoot, name);
    if (z == NIL) return false;
    if (z->childrenRoot != NIL) return false;

    Dir* y = z;
    Dir* x = NIL;
    Color yOriginalColor = y->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(treeRoot, z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(treeRoot, z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->rbParent == z) {
            x->rbParent = y;
        } else {
            transplant(treeRoot, y, y->right);
            y->right = z->right;
            y->right->rbParent = y;
        }
        transplant(treeRoot, z, y);
        y->left = z->left;
        y->left->rbParent = y;
        y->color = z->color;
    }

    delete z;
    if (yOriginalColor == BLACK) fixDelete(treeRoot, x);
    return true;
}

void inorderList(Dir* treeRoot) {
    if (treeRoot == NIL) return;
    inorderList(treeRoot->left);
    cout << treeRoot->name << " ";
    inorderList(treeRoot->right);
}

void printIndent(int depth) {
    for (int i = 0; i < depth; i++) cout << "  ";
}

void showTree(Dir* treeRoot, int depth);

void showDirectory(Dir* dir, int depth) {
    printIndent(depth);
    cout << dir->name << endl;
    showTree(dir->childrenRoot, depth + 1);
}

void showTree(Dir* treeRoot, int depth) {
    if (treeRoot == NIL) return;
    showTree(treeRoot->left, depth);
    showDirectory(treeRoot, depth);
    showTree(treeRoot->right, depth);
}

bool mkdirCmd(const string& name) {
    if (name.empty()) return false;
    return insertDir(currentDir->childrenRoot, name, currentDir);
}

bool rmdirCmd(const string& name) {
    return deleteDir(currentDir->childrenRoot, name);
}

bool cdCmd(const string& name) {
    if (name == "/") {
        currentDir = rootDir;
        return true;
    }
    if (name == "..") {
        if (currentDir->parentDir != nullptr) currentDir = currentDir->parentDir;
        return true;
    }
    Dir* next = searchDir(currentDir->childrenRoot, name);
    if (next == NIL) return false;
    currentDir = next;
    return true;
}

void lsCmd() {
    if (currentDir->childrenRoot == NIL) {
        cout << "(empty)" << endl;
        return;
    }
    inorderList(currentDir->childrenRoot);
    cout << endl;
}

void pwdCmd() {
    string path = "";
    Dir* temp = currentDir;
    while (temp != nullptr) {
        path = "/" + temp->name + path;
        temp = temp->parentDir;
    }
    cout << path << endl;
}

void clearAll(Dir* treeRoot) {
    if (treeRoot == NIL) return;
    clearAll(treeRoot->left);
    clearAll(treeRoot->right);
    clearAll(treeRoot->childrenRoot);
    delete treeRoot;
}

int main() {
    NIL = new Dir;
    NIL->name = "";
    NIL->color = BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->rbParent = NIL;
    NIL->parentDir = nullptr;
    NIL->childrenRoot = NIL;

    rootDir = new Dir;
    rootDir->name = "root";
    rootDir->color = BLACK;
    rootDir->left = NIL;
    rootDir->right = NIL;
    rootDir->rbParent = NIL;
    rootDir->parentDir = nullptr;
    rootDir->childrenRoot = NIL;

    currentDir = rootDir;

    mkdirCmd("home");
    mkdirCmd("etc");
    mkdirCmd("var");

    cdCmd("home");
    mkdirCmd("user");
    mkdirCmd("guest");

    cdCmd("user");
    mkdirCmd("documents");
    mkdirCmd("pictures");
    mkdirCmd("music");

    cout << "Current Path: ";
    pwdCmd();
    cout << "Current Directory Listing: ";
    lsCmd();

    cdCmd("/");
    cout << endl << "Directory Tree:" << endl;
    showDirectory(rootDir, 0);

    cout << endl << "Delete empty directory /root/etc: ";
    cout << (rmdirCmd("etc") ? "success" : "failed") << endl;

    cout << "Delete non-empty directory /root/home: ";
    cout << (rmdirCmd("home") ? "success" : "failed") << endl;

    cout << endl << "Directory Tree:" << endl;
    showDirectory(rootDir, 0);

    clearAll(rootDir->childrenRoot);
    delete rootDir;
    delete NIL;
    return 0;
}