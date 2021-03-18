#ifndef _NODE_H_
#define _NODE_H_

#include <string>
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

extern int cnt;

// cvor 2-3-4 stabla
class Node {
private:
	friend class RB234Tree;
	struct Member {
		string action;
		int priority;
		int count;

		Member(string a, int p) : action(a), priority(p), count(cnt++) {}
		Member(const Member& m) {
			action = m.action;
			priority = m.priority;
			count = m.count;
		}
		ostream& printMember(ostream& os) const {
			return os << action << " " << priority;
		}
	};

	enum Color { BLACK = 8, RED = 12, WHITE = 15 };

	int n;
	Member* keys[3];
	Node* parent;
	Node* C[4];// Have to add it for convenience, it was a mistake to start without it in the first place...
public:

	Node(Member* valB, Node* mid1 = nullptr, Node* mid2 = nullptr, Member* valR1 = nullptr,
		Node * left = nullptr, Member* valR2 = nullptr, Node* right = nullptr, Node* parent = nullptr);

	~Node();

	bool isFull() const { 
		if (keys[0] && keys[1] && keys[2])
			return true;
		else
			return false;
	}

	bool isLeaf() const { return !C[0] && !C[1] && !C[2] && !C[3]; }

	int Count() const { 
		int count = 0;
		for (Member* k : keys)
			if (k) count++;

		return count;
	}

	bool hasKey(Member key) const;

	Member* getKey(int i) const;

	bool hasPriority(int p);

	Member*& fetchMem(Member key);

	int getKeyPosforP(int p);

	Node* fetchPointerPos(Member * key);

	Node* fetchPointerForP(int p);

	Node* searchNode(Node::Member* key, Node** prev);

	int splitChild(Node* x);

	void Merge(int target, int sibling);

	bool isRealBro(int i, int j);

	void realBroBorrow(int target, int bro, int pos); // TODO: menjaj oca

	void realBroMerge(int target, int bro, int pos);

	void cousinBorrow(int t, int c);

	void cousinMerge(int t, int c);

	Member* getSucc(int ind, int& pos);

	Member* getPred(int ind, int& pos);

	void insertNonFull(Member* key);

	int addNonFullKey(Member* key);

	void printNode(HANDLE hConsole, ostream& os);

	friend int cmpMem(Node::Member* mem1, Node::Member* mem2);
};
#endif //!_NODE_H_