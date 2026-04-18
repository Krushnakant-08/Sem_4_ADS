#include <iostream>

using namespace std;

class Node {
public:
	int data;
	Node* left;
	Node* right;
	int lth;
	int rth;

	Node(int value) : data(value), left(nullptr), right(nullptr), lth(1), rth(1) {}
};

class TBT {
public:
	Node* insert(Node* root, int key) {
		Node* temp = new Node(key);
		Node* parent = nullptr;

		if (root == nullptr) {
			root = temp;
		} else {
			Node* curr = root;

			while (curr != nullptr) {
				if (key == curr->data) {
					cout << "Duplicate key not allowed" << endl;
					delete temp;
					return root;
				}

				parent = curr;

				if (key < curr->data) {
					if (curr->lth == 0) {
						curr = curr->left;
					} else {
						break;
					}
				} else {
					if (curr->rth == 0) {
						curr = curr->right;
					} else {
						break;
					}
				}
			}

			if (key < parent->data) {
				temp->left = parent->left;
				temp->right = parent;

				parent->lth = 0;
				parent->left = temp;
			} else {
				temp->left = parent;
				temp->right = parent->right;

				parent->rth = 0;
				parent->right = temp;
			}
		}

		return root;
	}

	Node* leftMost(Node* root) {
		while (root->lth == 0) {
			root = root->left;
		}
		return root;
	}

	void inorder(Node* root) {
		if (root == nullptr) {
			cout << "Tree is empty" << endl;
			return;
		}

		Node* curr = leftMost(root);

		while (curr != nullptr) {
			cout << curr->data << " ";

			if (curr->rth == 1) {
				curr = curr->right;
			} else {
				curr = leftMost(curr->right);
			}
		}
		cout << endl;
	}
};

int main() {
	TBT tbt;
	Node* root = nullptr;

	int choice = 0;
	int value = 0;

	do {
		cout << "\n1. Insert" << endl;
		cout << "2. Inorder Traversal" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {
			case 1:
				cout << "Enter value: ";
				cin >> value;
				root = tbt.insert(root, value);
				break;
			case 2:
				cout << "Inorder: ";
				tbt.inorder(root);
				break;
			case 3:
				cout << "Exiting..." << endl;
				break;
			default:
				cout << "Invalid choice" << endl;
				break;
		}
	} while (choice != 3);

	return 0;
}
