#pragma once

enum Color {
	RED,
	BLACK
};

template <typename T>
struct Node {
	T value;
	Color color;
	Node *left, *right, *parent;

	Node(const T& v) : value(v), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class RedBlackTree {
	private:
		Node<T>* root = nullptr;

		Node<T>* get_minimum(Node<T>* node) {
			while (node && node->left) {
				node = node->left;
			}
			return node;
		}

		void left_rotate(Node<T>* x) {
			Node<T>* y = x->right;
			Node<T>* t2 = y->left;

			y->left = x;
			x->right = t2;
			if (t2)
				t2->parent = x;
			y->parent = x->parent;
			x->parent = y;
			if (y->parent == nullptr)
				root = y;
			else if (y->parent->left == x)
				y->parent->left = y;
			else
				y->parent->right = y;
		}

		void right_rotate(Node<T>* y) {
			Node<T>* x = y->left;
			Node<T>* t2 = x->right;

			x->right = y;
			y->left = t2;
			if (t2) t2->parent = y;
			x->parent = y->parent;
			y->parent = x;
			if (x->parent == nullptr)
				root = x;
			else if (x->parent->left == y)
				x->parent->left = x;
			else
				x->parent->right = x;
		}

		void fix_insert(Node<T>* node) {
			while (node != root && node->parent->color == RED) {
				Node<T>* p = node->parent;
				Node<T>* g = p ? p->parent : nullptr;
				if (!g)
					break;
				Node<T>* u = (p == g->left) ? g->right : g->left;
				if (u && u->color == RED) {
						p->color = BLACK;
						u->color = BLACK;
						g->color = RED;
						node = g;
				} else {
					if (g->left == p) {
						if (node == p->right) {
							node = p;
							left_rotate(node);
							p = node->parent;
						}
						right_rotate(g);
						p->color = BLACK;
						g->color = RED;
					} else {
						if (node == p->left) {
							node = p;
							right_rotate(node);
							p = node->parent;
						}
						left_rotate(g);
						g->color = RED;
						p->color = BLACK;
					}
				}
			}
			root->color = BLACK;
		}

		void remove_fix(Node<T>* child, Node<T>* parent) {
			while (child != root && (child == NULL || child->color == BLACK)) {
				Node<T>* sibling;
				if (child == parent->left)
					sibling = parent->right;
				else
					sibling = parent->left;
				if (sibling && sibling->color == RED) {
					sibling->color = BLACK;
					parent->color = RED;
					if (child == parent->left)
						left_rotate(parent);
					else
						right_rotate(parent);
					if (child == parent->left)
						sibling = parent->right;
					else
						sibling = parent->left;
				}
				bool leftBlack  = !sibling || !sibling->left || sibling->left->color == BLACK;
				bool rightBlack = !sibling || !sibling->right || sibling->right->color == BLACK;
				if (leftBlack && rightBlack) {
					if (sibling)
						sibling->color = RED;
					child = parent;
					parent = parent->parent;
					continue;
				}
				if (child == parent->left) {
					if (sibling->left && sibling->left->color == RED &&
						(!sibling->right || sibling->right->color == BLACK)) {
						sibling->color = RED;
						sibling->left->color = BLACK;
						right_rotate(sibling);
						sibling = parent->right;
					}
					sibling->color = parent->color;
					parent->color = BLACK;
					if (sibling->right)
						sibling->right->color = BLACK;

					left_rotate(parent);
				}
				else {
					if (sibling->right && sibling->right->color == RED &&
						(!sibling->left || sibling->left->color == BLACK)) {

						sibling->color = RED;
						sibling->right->color = BLACK;
						left_rotate(sibling);

						sibling = parent->left;
					}
					sibling->color = parent->color;
					parent->color = BLACK;
					if (sibling->left)
						sibling->left->color = BLACK;
					right_rotate(parent);
				}
				child = root;
			}
			if (child)
				child->color = BLACK;
		}

	public:
		void insert(const T& value) {
			Node<T>* new_node = new Node<T>(value);
			if (!root) {
				root = new_node;
				return;
			}
			Node<T>* curr = root;
			Node<T>* parent = nullptr;
			while (curr) {
				parent = curr;
				if (value < curr->value)
					curr = curr->left;
				else if (value > curr->value)
					curr = curr->right;
				else {
					delete new_node;
					return ;
				}
			}
			new_node->parent = parent;
			if (value < parent->value)
				parent->left = new_node;
			else
				parent->right = new_node;
			fix_insert(new_node);
		}

		Node<T>* search(const T& value) {
			Node<T>* curr = root;
			while (curr) {
				if (value < curr->value)
					curr = curr->left;
				else if (value > curr->value)
					curr = curr->right;
				else
					return curr;
			}
			return nullptr;
		}

		void remove(const T& value) {
			Node<T>* node = search(value);
			if (!node)
				return ;
			Node<T>* parent = node->parent;
			if (node->left && node->right) {
				Node<T>* successor = get_minimum(node->right);
				node->value = successor->value;
				parent = successor->parent;
				node = successor;
			}
			Color original_color = node->color;
			Node<T>* child = node->left ? node->left : node->right;
			if (child)
				child->parent = parent;
			if (!parent)
				root = child;
			else if (parent->left == node)
				parent->left = child;
			else
				parent->right = child;
			delete node;
			if (original_color == BLACK)
				remove_fix(child, parent);
		}

		const Node<T>* get_root() const {
			return root;
		}
};
