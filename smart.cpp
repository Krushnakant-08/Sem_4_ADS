// Smart traffic system using AVL tree for junctions.
#include <algorithm>
#include <iostream>
#include <limits>
#include <stack>
#include <vector>

using namespace std;

struct Junction {
	int id;
	int traffic;
	Junction* left;
	Junction* right;
	bool lThread;
	bool rThread;
	int height;

	Junction(int idVal, int trafficVal)
		: id(idVal),
		  traffic(trafficVal),
		  left(nullptr),
		  right(nullptr),
		  lThread(false),
		  rThread(false),
		  height(1) {}
};

class TrafficSystem {
  public:
	Junction* root = nullptr;

	int height(Junction* n) {
		return (n == nullptr) ? 0 : n->height;
	}

	int getBalance(Junction* n) {
		return (n == nullptr) ? 0 : height(n->left) - height(n->right);
	}

	Junction* rightRotate(Junction* y) {
		Junction* x = y->left;
		Junction* T2 = x->right;

		x->right = y;
		y->left = T2;

		y->height = max(height(y->left), height(y->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;

		return x;
	}

	Junction* leftRotate(Junction* x) {
		Junction* y = x->right;
		Junction* T2 = y->left;

		y->left = x;
		x->right = T2;

		x->height = max(height(x->left), height(x->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;

		return y;
	}

	Junction* insert(Junction* node, int id, int traffic) {
		if (node == nullptr) {
			return new Junction(id, traffic);
		}

		if (id < node->id) {
			node->left = insert(node->left, id, traffic);
		} else if (id > node->id) {
			node->right = insert(node->right, id, traffic);
		} else {
			return node;
		}

		node->height = 1 + max(height(node->left), height(node->right));

		int balance = getBalance(node);

		if (balance > 1 && id < node->left->id) {
			return rightRotate(node);
		}

		if (balance < -1 && id > node->right->id) {
			return leftRotate(node);
		}

		if (balance > 1 && id > node->left->id) {
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		if (balance < -1 && id < node->right->id) {
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		return node;
	}

	Junction* search(Junction* node, int id) {
		if (node == nullptr || node->id == id) {
			return node;
		}

		if (id < node->id) {
			return search(node->left, id);
		}

		return search(node->right, id);
	}

	void updateTraffic(int id, int newTraffic) {
		Junction* node = search(root, id);
		if (node != nullptr) {
			node->traffic = newTraffic;
		} else {
			cout << "Junction not found" << endl;
		}
	}

	void inorderTraversal(Junction* node) {
		if (node == nullptr) {
			return;
		}

		stack<Junction*> stack;
		Junction* curr = node;

		while (curr != nullptr || !stack.empty()) {
			while (curr != nullptr) {
				stack.push(curr);
				curr = curr->left;
			}

			curr = stack.top();
			stack.pop();
			cout << "Junction: " << curr->id << " Traffic: " << curr->traffic << endl;

			curr = curr->right;
		}
	}

	void findLeastTrafficPath() {
		vector<Junction*> list;
		storeInorder(root, list);

		sort(list.begin(), list.end(),
				  [](const Junction* a, const Junction* b) { return a->traffic < b->traffic; });

		cout << "Best junctions (least traffic):" << endl;
		for (size_t i = 0; i < min<size_t>(3, list.size()); ++i) {
			cout << "Junction " << list[i]->id << " Traffic: " << list[i]->traffic << endl;
		}
	}

  private:
	void storeInorder(Junction* node, vector<Junction*>& list) {
		if (node == nullptr) {
			return;
		}
		storeInorder(node->left, list);
		list.push_back(node);
		storeInorder(node->right, list);
	}
};

int main() {
	TrafficSystem system;
	int choice = 0;

	do {
		cout << "1. Insert Junction" << endl;
		cout << "2. Search Junction" << endl;
		cout << "3. Update Traffic" << endl;
		cout << "4. Display All Junctions" << endl;
		cout << "5. Suggest Best Path" << endl;
		cout << "6. Exit" << endl;
		cout << "Enter your choice: ";

		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again." << endl;
			continue;
		}

		switch (choice) {
			case 1: {
				int id = 0;
				int traffic = 0;
				cout << "Enter Junction ID: ";
				cin >> id;
				cout << "Enter Traffic Density: ";
				cin >> traffic;
				system.root = system.insert(system.root, id, traffic);
				cout << "Junction inserted successfully." << endl;
				break;
			}
			case 2: {
				int searchId = 0;
				cout << "Enter Junction ID to search: ";
				cin >> searchId;
				Junction* result = system.search(system.root, searchId);
				if (result != nullptr) {
					cout << "Found -> ID: " << result->id << " Traffic: " << result->traffic
						  << endl;
				} else {
					cout << "Junction not found." << endl;
				}
				break;
			}
			case 3: {
				int updateId = 0;
				int newTraffic = 0;
				cout << "Enter Junction ID: ";
				cin >> updateId;
				cout << "Enter New Traffic: ";
				cin >> newTraffic;
				system.updateTraffic(updateId, newTraffic);
				break;
			}
			case 4:
				cout << "All Junctions (Inorder Traversal):" << endl;
				system.inorderTraversal(system.root);
				break;
			case 5:
				system.findLeastTrafficPath();
				break;
			case 6:
				cout << "Exiting system..." << endl;
				break;
			default:
				cout << "Invalid choice. Try again." << endl;
		}

	} while (choice != 6);

	return 0;
}
