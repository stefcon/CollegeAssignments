#include "RB234Tree.h"

#include <iostream>

RB234Tree::~RB234Tree() {
	DeleteTree();
}

void RB234Tree::DeleteTree() {

	if (!root)
		return;
	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node* curr = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			if (curr->C[i]) {
				q.push(curr->C[i]);
			}
		}
		delete curr;
	}

	root = nullptr;
	height = -1;
}

bool RB234Tree::Insert(string action, int priority) {
	Node::Member* key = new Node::Member(action, priority);
	if (!root) {
		root = new Node(key);
		height++;
		
		return true;
	}

	Node* curr = root, * prev = nullptr;
	
	curr = searchNode(key, &prev);
		
	if (curr) return false;
	else curr = prev;
	
	if (!curr->isFull()) {// ukoliko list nije pun, samo ubacimo kljuc
		curr->addNonFullKey(key);
	}
	else { // u suprotnom, idemo do prvog pretka koji nije pun, a zatim splitujemo sve do lista
		Node* parent = curr->parent;
		while (parent && parent->isFull()) {
			parent = parent->parent;
		}
		if (parent == nullptr) { // stigli smo do korena, dize se visina celog stabla
			Node* n_root = new Node(nullptr);
			n_root->C[1] = root;
			n_root->splitChild(root);
			
			if (cmpMem(key, n_root->keys[1]) <= 0)
				n_root->C[1]->insertNonFull(key);
			else
				n_root->C[2]->insertNonFull(key);


			root = n_root;
			height++;
		}
		else {
			parent->insertNonFull(key);
		}

	}
	
	
	return true;
}

bool RB234Tree::inputAction(istream& is) {
	string line, action, num_str;
	int pos, priority;

	if (getline(is, line)) {
		pos = line.find_last_of(" ");
		if (pos != string::npos) {
			action = line.substr(0, pos);
			num_str = line.erase(0, pos + 1);
			priority = stoi(num_str);
		}
		else {
			return false;
		}
		if (action.length() > 256)
			return false;

		Insert(action, priority);

		return true;
	}
	else {
		return false;
	}
}

void RB234Tree::inputFromFile(istream& is) {
	while (inputAction(is));
}

bool RB234Tree::DeletePriority(int priority) {
	Node* prev;
	Node* target = searchPriorityNode(priority, &prev);
	if (!target) {
		return false;
	}
	else {
		int pos = target->getKeyPosforP(priority);
		DeleteKey(pos, target);
	}

	return true;
}

bool RB234Tree::DeleteMaxPriority() {
	if (!root) {
		return false;
	}

	Node* node = findMax();
	int pos = (node->keys[2]) ? 2 : 1;
	DeleteKey(pos, node);
	

	return true;
}

void RB234Tree::DeleteKey(int pos, Node* node) {
	bool flag = false;
	do {
		if (node->isLeaf() || flag) { // If target node is a leaf, we can delete the key

			if (node->isLeaf()) {
				delete node->keys[pos];
				node->keys[pos] = nullptr;
				--node->n;
			}

			flag = false;

			int keyCount = node->Count();
			if (keyCount) {
				if (node->keys[1] == nullptr) {
					if (node->keys[2]) {
						node->keys[1] = node->keys[2];
						node->keys[2] = nullptr;
					}
					else {
						node->keys[1] = node->keys[0];
						node->keys[0] = nullptr;
					}
				}
			}
			else { // Slucajevi raznog pozajmljivanja
				 // First, we check if we have a 'real bro', the one we would have in equivelent r-b tree

				Node* parent = node->parent;
				int target, sibling; // i = target, j = realBro(if he exists) :`(

				if (!parent) {
					continue;
				}

				for (target = 0; target < 4; target++)
					if (parent->C[target] == node) break;
				for (sibling = 0; sibling < 4; sibling++)
					if (parent->isRealBro(target, sibling))
						break;

				if (sibling < 4) {
					int pos = (target < sibling) ? target : sibling;
					if (parent->C[sibling]->Count() > 1) {
						parent->realBroBorrow(target, sibling, pos);
					}
					else if (pos != 1) {
						parent->realBroMerge(target, sibling, pos);
					}
					else { // Merging occurs, where it is propagated until our parent doesn't become
						// empty after the operation
						parent->Merge(target, sibling);
						node = parent;
						if (parent->parent != nullptr) {
							flag = true;
						}
					}
				}
				else {
					// Afterwards, we check if we can borrow from our 'cousin'
					int cousin = (target == 1) ? 2 : 1;

					if (parent->C[cousin]->Count() > 1)
						parent->cousinBorrow(target, cousin);
					else
						parent->cousinMerge(target, cousin);
				}
			}
		}
		else { // We first find the successor and then do the case for the leaf node
			int succ_pos;
			Node* prev;
			Node::Member* succ = node->getSucc(pos, succ_pos), * tmp = node->keys[pos];
			node->keys[pos] = new Node::Member(*succ);

			if (cmpMem(tmp, succ) > 0)
				node = node->C[pos]->searchNode(succ, &prev);
			else
				node = node->C[pos + 1]->searchNode(succ, &prev);
			
			pos = succ_pos;
			flag = true;
		}
	} while (flag);

	if (root->Count() == 0) {
		Node* old_root = root;
		root = root->C[1];
		delete old_root;
		if (root)
			root->parent = nullptr;
		height--;
	}

}


Node* RB234Tree::searchNode(Node::Member* key, Node** prev) {
	return root->searchNode(key, prev);
}

Node* RB234Tree::searchPriorityNode(int p, Node** prev) {
	if (!root) {
		return nullptr;
	}

	Node* curr = root;
	while (true) {
		if (curr->hasPriority(p)) {
			break;
		}
		else if (!curr->isLeaf()) {
			*prev = curr;
			curr = curr->fetchPointerForP(p);
		}
		else {
			*prev = curr;
			curr = nullptr;
			break;
		}
	}
	return curr;
}

Node::Member* RB234Tree::searchPriorityKey(int p) {
	Node* prev;
	if (Node* res = searchPriorityNode(p, &prev))
		return res->keys[res->getKeyPosforP(p)];
	else
		return nullptr;
}

bool RB234Tree::searchKey(Node::Member* key) {
	Node* prev;
	if (searchNode(key, &prev))
		return true;
	else
		return false;
}

int RB234Tree::keysWithPriority(int p) {
	if (!root) {
		return 0;
	}

	queue<Node*> q;
	q.push(root);
	int counter = 0;
	while (!q.empty()) {
		Node* next = q.front();
		q.pop();

		if (next->keys[0] && next->keys[0]->priority == p) counter++;
		if (next->keys[1] && next->keys[1]->priority == p) counter++;
		if (next->keys[2] && next->keys[2]->priority == p) counter++;

		for (Node* c : next->C) {
			if (c)
				q.push(c);
		}
	}

	return counter;
}

bool RB234Tree::changePriority(string a, int p, int newP) {
	if (!root) {
		return false;
	}
	Node* prev;
	Node::Member oldKey(a, p), newKey(a, newP), *succ, * pred;
	Node* node = root->searchNode(&oldKey, &prev);
	if (!node) {
		return false;
	}
	int pos = node->getKeyPosforP(p), succ_pos, pred_pos;

	succ = node->getSucc(pos, succ_pos);
	pred = node->getPred(pos, pred_pos);

	if (succ && pred) {
		if (cmpMem(&newKey, succ) < 0 && cmpMem(&newKey, pred) > 0) {
			node->keys[pos]->priority = newP;
			return true;
		}
	}
	else if (succ) {
		if (cmpMem(&newKey, succ) < 0) {
			node->keys[pos]->priority = newP;
			return true;
		}
	}
	else if (pred) {
		if (cmpMem(&newKey, pred) > 0) {
			node->keys[pos]->priority = newP;
			return true;
		}
	}
	else if (!succ && !pred) {
		node->keys[pos]->priority = newP;
		return true;
	}

	DeleteKey(pos, node);
	Insert(a, newP);
	return true;
}

void RB234Tree::printMTree(ostream& os) const {
	if (!root) {
		os << "Prazno stablo!" << endl;
		return;
	}
	HANDLE consoleHandle;
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	queue<Node*> q;

	os << "Izgled 2-3-4 stabla: " << endl << endl;
	int W = 16;
	int lineLength = pow(4, height) * W + (pow(4, height) - 1);
	
	int rowIndent = (lineLength - W) / 2, nodeSpacing = lineLength;

	q.push(root);

	for (int i = 0; i <= height; i++) {
		int maxNode = 1 << (2 * i);
		if (i != 0) {
			rowIndent = (rowIndent + W / 2) / 4 - W / 2;
			nodeSpacing = (nodeSpacing - 4 * W) / 4;
			if (rowIndent < 0) rowIndent = 0;
			if (nodeSpacing < 0) nodeSpacing = 1;
		}
		for (int k = 0; k < rowIndent; k++) os << " ";
		for (int j = 0; j < maxNode; j++) {
			Node* next = q.front();
			q.pop();
			if (next) {
				next->printNode(consoleHandle, os);
				for (Node* c : next->C)
					q.push(c);
			}
			else {
				for (int i = 0; i < W; i++) os << " ";
				for (int k = 0; k < 4; k++)
					q.push(nullptr);
			}
			for (int k = 0; k < nodeSpacing; k++) os << " ";
		}
		os << endl << endl;

	}
	q.empty();
}

int RB234Tree::getRBHeight() {
	if (!root) {
		return 0;
	}
	queue<RB*> q;
	RB* next = new RB(root, 1);
	int rb_height = -2;
	q.push(next);
	q.push(nullptr);
	while (q.front() != nullptr) {
		next = q.front();
		q.pop();

		//Print here;
		if (next->node) {
			if (next->pos == 1) {

				if (next->node->keys[0]) {
					q.push(new RB(next->node, 0));
				}
				else {
					q.push(new RB(next->node->C[1], 1));
				}

				if (next->node->keys[2]) {
					q.push(new RB(next->node, 2));
				}
				else {
					q.push(new RB(next->node->C[2], 1));
				}

			}
			else {
				if (next->pos == 0) {
					q.push(new RB(next->node->C[0], 1));
					q.push(new RB(next->node->C[1], 1));
				}
				else {
					q.push(new RB(next->node->C[2], 1));
					q.push(new RB(next->node->C[3], 1));
				}
			}
		}
		delete next;
		if (q.front() == nullptr) {
			q.pop();
			q.push(nullptr);
			rb_height++;
		}
	}


	return rb_height;
}


void RB234Tree::printRBTree(ostream& os) {
	if (!root) {
		os << "Prazno stablo!" << endl;
		return;
	}

	HANDLE consoleHandle;
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	os << "Binarno RB stablo: " << endl << endl;

	queue<RB*> q;
	RB* next = new RB(root, 1);
	int rb_height = getRBHeight();
	int W = 5;
	int lineLength = pow(2, rb_height) * W + (pow(2, rb_height) - 1);
	int rowIndent = floor((lineLength - W) / 2.), nodeSpacing = lineLength;
	bool newLine = true;
	int cnt = -1;
	q.push(next);
	q.push(nullptr);
	while (cnt != rb_height) {
		next = q.front();
		q.pop();

		if (newLine) {
			for (int i = 0; i < rowIndent; i++) os << " ";
			newLine = false;
		}
		
		if (next->node == nullptr) {
			os << "     ";
		}
		else {
			os << "[";
			if (next->pos == 1) {
				SetConsoleTextAttribute(consoleHandle, 8);
				ios init(NULL);
				init.copyfmt(os);
				os << setw(3) << next->node->keys[next->pos]->priority;
				os.copyfmt(init);
			}
			else {
				SetConsoleTextAttribute(consoleHandle, 12);
				ios init(NULL);
				init.copyfmt(os);
				os << setw(3) << next->node->keys[next->pos]->priority;
				os.copyfmt(init);
			}
			SetConsoleTextAttribute(consoleHandle, 15);
			os << "]";
		}
		for (int i = 0; i < nodeSpacing; i++) os << " ";

		if (next->node == nullptr) {

			for (int i = 0; i < 2; i++) 
				q.push(new RB(nullptr, -1));

		} else if (next->pos == 1) {
			if (next->node->keys[0]) {
				q.push(new RB(next->node, 0));
			}
			else {
				q.push(new RB(next->node->C[1], 1));
			}

			if (next->node->keys[2]) {
				q.push(new RB(next->node, 2));
			}
			else {
				q.push(new RB(next->node->C[2], 1));
			}

		}
		else {
			if (next->pos == 0) {
				q.push(new RB(next->node->C[0], 1));
				q.push(new RB(next->node->C[1], 1));
			}
			else {
				q.push(new RB(next->node->C[2], 1));
				q.push(new RB(next->node->C[3], 1));
			}
		}
		
		delete next;
		if (q.front() == nullptr) {
			q.push(nullptr);
			q.pop();
			os << endl << endl;
			newLine = true;
			nodeSpacing = rowIndent;
			rowIndent = (rowIndent - W) / 2;
			rowIndent = (rowIndent <= 0) ? 0 : rowIndent;
			cnt++;
		}
	}
	os << endl;
	q.empty();
}

ostream& operator<<(ostream& os, const RB234Tree& t) {
	t.printMTree(os);
	return os;
}

Node* RB234Tree::findMax() {
	Node* prev = nullptr, * curr = root;
	while (curr) {
		prev = curr;
		curr = (curr->C[3])? curr->C[3] : curr->C[2];
	}

	return prev;
}