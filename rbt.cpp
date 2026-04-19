#include <iostream>

using namespace std;

class RedBlackTree {
private:
	enum class Color { Red, Black };

	struct Node {
		int key;
		Color color;
		Node* left;
		Node* right;
		Node* parent;

		Node(int k, Color c, Node* l, Node* r, Node* p)
			: key(k), color(c), left(l), right(r), parent(p) {}
	};

	Node* root_;
	Node* nil_;

	void clear(Node* node) {
		if (node == nil_) {
			return;
		}
		clear(node->left);
		clear(node->right);
		delete node;
	}

	Node* findNode(int key) const {
		Node* current = root_;
		while (current != nil_) {
			if (key < current->key) {
				current = current->left;
			} else if (key > current->key) {
				current = current->right;
			} else {
				return current;
			}
		}
		return nil_;
	}

	void inorder(Node* node) const {
		if (node == nil_) {
			return;
		}
		inorder(node->left);
		cout << node->key << ' ';
		inorder(node->right);
	}

	void leftRotate(Node* x) {
		Node* y = x->right;
		x->right = y->left;
		if (y->left != nil_) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nil_) {
			root_ = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(Node* y) {
		Node* x = y->left;
		y->left = x->right;
		if (x->right != nil_) {
			x->right->parent = y;
		}
		x->parent = y->parent;
		if (y->parent == nil_) {
			root_ = x;
		} else if (y == y->parent->right) {
			y->parent->right = x;
		} else {
			y->parent->left = x;
		}
		x->right = y;
		y->parent = x;
	}

	void insertFix(Node* z) {
		while (z->parent->color == Color::Red) {
			if (z->parent == z->parent->parent->left) {
				Node* y = z->parent->parent->right;
				if (y->color == Color::Red) {
					z->parent->color = Color::Black;
					y->color = Color::Black;
					z->parent->parent->color = Color::Red;
					z = z->parent->parent;
				} else {
					if (z == z->parent->right) {
						z = z->parent;
						leftRotate(z);
					}
					z->parent->color = Color::Black;
					z->parent->parent->color = Color::Red;
					rightRotate(z->parent->parent);
				}
			} else {
				Node* y = z->parent->parent->left;
				if (y->color == Color::Red) {
					z->parent->color = Color::Black;
					y->color = Color::Black;
					z->parent->parent->color = Color::Red;
					z = z->parent->parent;
				} else {
					if (z == z->parent->left) {
						z = z->parent;
						rightRotate(z);
					}
					z->parent->color = Color::Black;
					z->parent->parent->color = Color::Red;
					leftRotate(z->parent->parent);
				}
			}
		}
		root_->color = Color::Black;
		root_->parent = nil_;
	}

	void transplant(Node* u, Node* v) {
		if (u->parent == nil_) {
			root_ = v;
		} else if (u == u->parent->left) {
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	Node* minimum(Node* node) const {
		while (node->left != nil_) {
			node = node->left;
		}
		return node;
	}

	void deleteFix(Node* x) {
		while (x != root_ && x->color == Color::Black) {
			if (x == x->parent->left) {
				Node* w = x->parent->right;
				if (w->color == Color::Red) {
					w->color = Color::Black;
					x->parent->color = Color::Red;
					leftRotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == Color::Black && w->right->color == Color::Black) {
					w->color = Color::Red;
					x = x->parent;
				} else {
					if (w->right->color == Color::Black) {
						w->left->color = Color::Black;
						w->color = Color::Red;
						rightRotate(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = Color::Black;
					w->right->color = Color::Black;
					leftRotate(x->parent);
					x = root_;
				}
			} else {
				Node* w = x->parent->left;
				if (w->color == Color::Red) {
					w->color = Color::Black;
					x->parent->color = Color::Red;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == Color::Black && w->left->color == Color::Black) {
					w->color = Color::Red;
					x = x->parent;
				} else {
					if (w->left->color == Color::Black) {
						w->right->color = Color::Black;
						w->color = Color::Red;
						leftRotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = Color::Black;
					w->left->color = Color::Black;
					rightRotate(x->parent);
					x = root_;
				}
			}
		}
		x->color = Color::Black;
	}

public:
	RedBlackTree() {
		nil_ = new Node(0, Color::Black, nullptr, nullptr, nullptr);
		root_ = nil_;
	}


	void insert(int key) {
		Node* z = new Node(key, Color::Red, nil_, nil_, nil_);
		Node* y = nullptr;
		Node* x = root_;

		while (x != nil_) {
			y = x;
			if (z->key < x->key) {
				x = x->left;
			} else if (z->key > x->key) {
				x = x->right;
			} else {
				delete z;
				return;
			}
		}

		z->parent = (y == nullptr) ? nil_ : y;
		if (y == nullptr || y == nil_) {
			root_ = z;
		} else if (z->key < y->key) {
			y->left = z;
		} else {
			y->right = z;
		}

		insertFix(z);
	}

	void erase(int key) {
		Node* z = findNode(key);
		if (z == nil_) {
			return;
		}

		Node* y = z;
		Node* x = nullptr;
		Color yOriginalColor = y->color;

		if (z->left == nil_) {
			x = z->right;
			transplant(z, z->right);
		} else if (z->right == nil_) {
			x = z->left;
			transplant(z, z->left);
		} else {
			y = minimum(z->right);
			yOriginalColor = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			} else {
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}

		delete z;
		if (yOriginalColor == Color::Black) {
			deleteFix(x);
		}
	}

	void inorderPrint() const {
		inorder(root_);
		cout << "\n";
	}
};

int main() {
	RedBlackTree tree;
	tree.insert(10);
	tree.insert(20);
	tree.insert(30);
	tree.insert(15);
	tree.insert(25);
	tree.erase(20);
	tree.inorderPrint();
	return 0;
}
