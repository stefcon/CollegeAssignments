#include "type.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <algorithm>
#include <random>
#include <queue>


using namespace std;


Matrix::Matrix(const Matrix& matrix)
{
	m = matrix.m, n = matrix.n, dim = matrix.dim;
	mat = new int*[dim];
	cnt = 0;
	for (int i = 0; i < dim; i++) {
		mat[i] = new int[dim];
		if (i < m) {
			for (int j = 0; j < n; j++) {
				mat[i][j] = matrix.mat[i][j];
			}
		}
	}
}

Matrix::Matrix(Matrix&& matrix)
{
	m = matrix.m;
	n = matrix.n;
	dim = matrix.dim;
	cnt = 0;
	mat = matrix.mat;

	matrix.mat = nullptr;

}

Matrix::~Matrix()
{
	del_mat();
}

void Matrix::input()
{
	cout << "Unesite dimenzije matrice: ";
	cin >> m >> n;
	if (mat) del_mat();
	dim = (m > n) ? m : n;
	cout << "Unesite vrednosti matrice:" << endl;
	mat = new int* [dim];
	for (int i = 0; i < dim; i++) {
		mat[i] = new int[dim];
		if (i < m) {
			for (int j = 0; j < n; j++) {
				cin >> mat[i][j];
			}
		}
	}
}

void Matrix::transpose()
{
	int tmp;
	for (int i = 1; i < dim; i++) {
		for (int j = 0; j < i; j++) {
			tmp = mat[i][j], mat[i][j] = mat[j][i], mat[j][i] = tmp;
		}
	}
	tmp = m, m = n, n = tmp;
}

void Matrix::sort_rows()
{
	for (int k = 0; k < m; k++) {
		sort(mat[k], mat[k] + n);
	}
}

void Matrix::del_mat()
{
	for (int i = 0; i < dim; i++)
		delete[] mat[i];
	delete[] mat;
	mat = nullptr;
}

void Matrix::sort_mat()
{
	sort_rows();
	transpose();
	sort_rows();
	transpose();
}


bool Matrix::search(int key)
{
	int i = 0, j = n - 1;
	while (i < m && j >= 0) {
		cnt += 3;
		int curr = mat[i][j];
		if (curr == key) {
			return true;
		}
		else if (curr > key) {
			j--;
		}
		else {
			i++;
		}
		cnt++;
	}
	return false;
}

void Matrix::generate(int rows, int cols, int low, int high)
{	
	if (low > high) {
		int tmp;
		tmp = low, low = high, high = tmp;
	}
	srand((unsigned)time(NULL));
	if (mat) del_mat();
	m = rows;
	n = cols;
	dim = (m > n) ? m : n;
	mat = new int* [dim];
	for (int i = 0; i < dim; i++) {
		mat[i] = new int[dim];
		if (i < m) {
			for (int j = 0; j < n; j++) {
				mat[i][j] = rand() / (RAND_MAX + 1.) * (high - low) + low;
			}
		}
	}
}

double Matrix::benchmark(vector<int> keys)
{
	cnt = 0;
	for (int key : keys) {
		search(key);
	}

	return (double) cnt / keys.size() ;
}

TNode* AVL::clone_node(TNode* node)
{
	TNode* clone = new TNode;
	clone->key = node->key;
	clone->cnt = node->cnt;
	clone->balance = node->balance;
	clone->left = node->left;
	clone->right = node->right;

	return clone;
}

TNode* AVL::copy_tree(TNode* old_root)
{
	if (old_root == nullptr) {
		return nullptr;
	}
	stack<TNode*> s;
	TNode* tmp, * cpy = clone_node(old_root);
	s.push(cpy);
	while (!s.empty()) {
		tmp = s.top();
		s.pop();

		if (tmp->left != nullptr) {
			tmp->left = clone_node(tmp->left);
			s.push(tmp->left);
		}
		if (tmp->right != nullptr) {
			tmp->right = clone_node(tmp->right);
			s.push(tmp->right);
		}
	}

	return cpy;
}

void AVL::delete_tree()
{
	TNode* next = root;
	stack<TNode*> s;
	if (next) {
		do {
			while (next) {
				if (next->right != nullptr)
					s.push(next->right);
				s.push(next);
				next = next->left;
			}
			next = s.top();
			s.pop();

			if (next->right) {
				if (!s.empty()) {
					if (next->right == s.top()) {
						s.pop();
						s.push(next);
						next = next->right;
					}
					else {
						delete next;
						next = nullptr;
					}
				}
			}
			else {
				delete next;
				next = nullptr;
			}
		} while (!s.empty());
	}
	root = nullptr;
}

void AVL::insert_node(int key, TNode* father_x, TNode* father_s, TNode* x)
{
	TNode* curr, * y;
	TNode* q = new TNode;
	int imbalance;
	q->left = q->right = nullptr;
	q->balance = 0;
	q->key = key;
	q->cnt = 1;
	if (root == nullptr) {
		root = q;
		return;
	}

	if (key < father_s->key)
		father_s->left = q;
	else
		father_s->right = q;

	if (key < x->key) {
		curr = x->left;
		imbalance = 1;
	}
	else {
		curr = x->right;
		imbalance = -1;
	}
	y = curr;

	while (curr != q) {
		if (key < curr->key) {
			curr->balance = 1;
			curr = curr->left;
		}
		else {
			curr->balance = -1;
			curr = curr->right;
		}	
	}

	if (x->balance == 0) {
		x->balance = imbalance;
		return;
	}

	if (x->balance != imbalance) {
		x->balance = 0;
		return;
	}

	if (y->balance == imbalance) {
		curr = y;
		if (imbalance == 1)
			right_rotation(x);
		else
			left_rotation(x);
		x->balance = y->balance = 0;
	}
	else {
		if (imbalance == 1) {
			curr = y->right;
			left_rotation(y);
			x->left = curr;
			right_rotation(x);
		}
		else {
			curr = y->left;
			x->right = curr;
			right_rotation(y);
			left_rotation(x);
		}

		if (curr->balance == 0) {
			x->balance = y->balance = 0;
		}
		else {
			if (curr->balance == imbalance) {
				x->balance = -imbalance;
				y->balance = 0;
			}
			else {
				x->balance = 0;
				y->balance = imbalance;
			}
			curr->balance = 0;
		}	
	}

	if (father_x == nullptr) {
		root = curr;
	}
	else if (x == father_x->right) {
		father_x->right = curr;
	}
	else {
		father_x->left = curr;
	}

}

void AVL::right_rotation(TNode* crit)
{
	TNode* crit_son = crit->left;
	TNode* tmp = crit_son->right;
	crit_son->right = crit;
	crit->left = tmp;
}

void AVL::left_rotation(TNode* crit)
{
	TNode* crit_son = crit->right;
	TNode* tmp = crit_son->left;
	crit_son->left = crit;
	crit->right = tmp;
}

AVL::AVL(const AVL& tree)
{
	root = copy_tree(tree.root);
	num = tree.num;
}

AVL::AVL(AVL&& tree)
{
	root = tree.root;
	num = tree.num;
	tree.root = nullptr;
}

AVL::~AVL()
{
	delete_tree();
}

bool AVL::interact(int key, string option)
{
	TNode* father_x ,* father_s, * q, * x, * curr;
	father_x = father_s = q = nullptr;
	curr = root;
	x = curr;
	while (curr) {
		if (curr->key == key) {
			if (option == "insert") {
				curr->cnt++;
				return true;
			}
			else if (option == "search") {
				return true;
			}

		}

		if (key < curr->key)
			q = curr->left;
		else
			q = curr->right;

		if (q != nullptr) {
			if (q->balance != 0) {
				father_x = curr;
				x = q;
			}
		}

		father_s = curr;
		curr = q;

	}
	if (option == "search") {
		return false;
	}
	else if (option == "insert") {
		insert_node(key, father_x, father_s, x);
		num++;
		return true;
	}
	return false;
}

void AVL::create_tree(Matrix matrix)
{
	int m = matrix.row_n(), n = matrix.col_n();

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) {
			interact(matrix.el(i, j), "insert");
		}
}

double AVL::benchmark(vector<int> keys)
{
	double cnt = 0;
	for (int key : keys) {
		TNode* curr = root;
		while (curr) {
			cnt += 2;
			if (curr->key == key) {
				break;
			}
			if (key < curr->key)
				curr = curr->left;
			else
				curr = curr->right;
			cnt++;
		}
	}

	return (double)cnt / keys.size();
}

int AVL::height()
{
	if (root == nullptr)
		return 0;
	queue<TNode*> q;
	q.push(root);
	int current_cnt = 1, height = 0;
	while (!q.empty()) {
		int next_cnt = 0;
		while (current_cnt) {
			current_cnt--;
			TNode* next = q.front();
			q.pop();
			if (next->left) {
				q.push(next->left);
				next_cnt++;
			}
			if (next->right) {
				q.push(next->right);
				next_cnt++;
			}
		}
		current_cnt = next_cnt;
		if (current_cnt) height++;
	}

	return height;
}

void AVL::print()
{
	if (root == nullptr)
		return;
	queue<TNode*> q; 
	/*int estimate = height();*/ // Ukoliko bih imao neogranicen ekran, mogao bih da koristim ovakvu formulu
	int line_length = 207, current_cnt = 1;
	/*for (int i = estimate; i > 0; i--) line_length = line_length * 2 + 7;*/
	int row_indent = line_length, node_spacing, height = 0;
	q.push(root);

	while (current_cnt) {
		int max_node_num = 1 << height, next_cnt = 0;
		node_spacing = row_indent;
		row_indent = (row_indent - 7)/ 2;
		for (int i = 0; i < row_indent; i++) cout << " ";
		for (int i = 0; i < max_node_num; i++) {
			TNode* next = q.front();
			q.pop();
			if (next) {
				if (next->left) { 
					cout << "-";
					next_cnt++;
				}
				else {
					cout << " ";
				}
				cout << "(" << next->key << "," << next->cnt << ")";
				current_cnt--;
				if (next->right) { 
					cout << "-";
					next_cnt++; 				
				}
				else {
					cout << " ";
				}
				q.push(next->left);
				q.push(next->right);
				
			}
			else {
				q.push(nullptr);
				q.push(nullptr);
				cout << "       ";
			}
			for (int i = 0; i < node_spacing; i++) cout << " ";

		}
		current_cnt = next_cnt;
		if (current_cnt) height++;
		cout << endl << endl;
	}
	q.empty();

}