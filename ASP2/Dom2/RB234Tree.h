#ifndef _RB234TREE_H_
#define _RB234TREE_H_

#include "Node.h"
#include <math.h>
#include <stack>
#include <queue>	

using namespace std;

class RB234Tree {

	Node* root;
	int height;

	struct RB {
		Node* node;
		int pos;

		RB(Node* node, int p) : node(node), pos(p) {}

	};

	void DeleteKey(int pos, Node* node);

public:
	
	RB234Tree() : root(nullptr), height(-1) {}

	~RB234Tree();

	bool isEmpty() const { return !root; }

	void DeleteTree();

	Node* findMax();

	Node* searchNode(Node::Member* key, Node** prev);

	Node* searchPriorityNode(int p, Node** prev);

	Node::Member* searchPriorityKey(int p);

	bool searchKey(Node::Member* key);

	bool Insert(string action, int priority);

	bool inputAction(istream& is);

	void inputFromFile(istream& is);

	bool DeletePriority(int priority);

	bool DeleteMaxPriority();

	int keysWithPriority(int p);

	bool changePriority(string a, int p, int newP);

	void printMTree(ostream& os) const;

	int getRBHeight();

	void printRBTree(ostream& os);

	friend ostream& operator<<(ostream& os, const RB234Tree& t);

	friend int cmpMem(Node::Member* mem1, Node::Member* mem2);
};
#endif // !_RB234TREE_H_