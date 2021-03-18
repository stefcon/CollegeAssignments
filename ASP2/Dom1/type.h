#ifndef _type_h_ // begin type.h
#define _type_h_

#include <limits>
#include <vector>
#include <iostream>
#include <string>


using namespace std;

struct TNode {
	int key, balance, cnt;
	TNode* left, * right;
};

class Matrix {
	int m, n, dim;
	int cnt;
	int** mat;
	void sort_rows();
	void del_mat();
public:
	Matrix() : m(0), n(0), dim(0), cnt(0), mat(nullptr) {};
	Matrix(const Matrix& matrix);
	Matrix(Matrix&& matrix);
	~Matrix();
	void input();
	void transpose();
	void sort_mat();
	bool search(int key);
	void generate(int rows, int cols, int low, int high);
	double benchmark(vector<int> keys);
	
	bool isEmpty() {
		if (mat == nullptr)
			return true;
		else
			return false;
	}
	void print() const {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout << mat[i][j];
				if (j == n - 1) cout << endl;
				else cout << " ";
			}
		}
	}

	int el(int i, int j) const { return mat[i][j]; }
	int row_n() const { return m; }
	int col_n() const { return n; }
};


class AVL {
	TNode* root;
	int num;
	TNode* clone_node(TNode* node);
	TNode* copy_tree(TNode* old_root);
	void insert_node(int key, TNode* father_x, TNode* father_s, TNode* x);
	void right_rotation(TNode* crit);
	void left_rotation(TNode* crit);
public:
	AVL() : root(nullptr), num(0) {}
	AVL(const AVL& tree);
	AVL(AVL&& tree);
	~AVL();
	bool isEmpty() {
		if (root == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	void delete_tree();
	bool interact(int key, string option);
	void create_tree(Matrix matrix);
	double benchmark(vector<int> keys);
	int height();
	void print();
};

#endif // !_type_h_

