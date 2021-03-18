#include "Node.h"
#include "RB234Tree.h"


Node::Node(Member* valB, Node* mid1, Node* mid2, Member* valR1, Node* left, Member* valR2, Node* right, Node* par) {
	keys[1] = valB;
	keys[0] = valR1;
	keys[2] = valR2;
	C[0] = left;
	C[1] = mid1;
	C[2] = mid2;
	C[3] = right;
	n = 0;
	parent = par;

	if (mid1) mid1->parent = this;
	if (mid2) mid2->parent = this;
	if (left) left->parent = this;
	if (right) right->parent = this;

	if (valR1) n++;
	if (valB) n++;
	if (valR2) n++;
}

Node::~Node() {
	delete keys[0];
	delete keys[1];
	delete keys[2];
}

bool Node::hasKey(Member key) const {
	int r1_cmp, b_cmp, r2_cmp;
	r1_cmp = (!keys[0]) ? -1 : cmpMem(keys[0], &key);
	b_cmp = (!keys[1]) ? -1 : cmpMem(keys[1], &key);
	r2_cmp = (!keys[2]) ? -1 : cmpMem(keys[2], &key);
	if (!r1_cmp || !b_cmp || !r2_cmp)
		return true;
	else
		return false;
}

Node::Member* Node::getKey(int i) const {

	return keys[i];

}

bool Node::hasPriority(int p) {
	bool r1_cmp, b_cmp, r2_cmp;
	r1_cmp = (!keys[0]) ? 0 : keys[0]->priority == p;
	b_cmp = (!keys[1]) ? 0 : keys[1]->priority == p;
	r2_cmp = (!keys[2]) ? 0 : keys[2]->priority == p;
	if (r1_cmp || b_cmp || r2_cmp)
		return true;
	else
		return false;
}

Node::Member*& Node::fetchMem(Member key) {
	if (keys[0] && !cmpMem(keys[0], &key)) return keys[0];
	if (keys[1] && !cmpMem(keys[1], &key)) return keys[1];
	if (keys[2] && !cmpMem(keys[2], &key)) return keys[2];
}

int Node::getKeyPosforP(int p)
{
	// Changing order of ifs so it is also taking action into calculations
	if (keys[2] && keys[2]->priority == p) return 2;
	if (keys[1] && keys[1]->priority == p) return 1;
	if (keys[0] && keys[0]->priority == p) return 0;
}

Node* Node::fetchPointerPos(Member* key){
	int ind;
	if (keys[0]) {
		ind = cmpMem(keys[0], key);
		if (ind == 1 || ind == 0)
			return C[0];
	}
	if (keys[1]) {
		ind = cmpMem(keys[1], key);
		if (ind == 1 || ind == 0)
			return C[1];
	}
	if (keys[2]) {
		ind = cmpMem(keys[2], key);
		if (ind == 1 || ind == 0)
			return C[2];
		else
			return C[3];
	}

	return C[2];
}

Node* Node::fetchPointerForP(int p)
{
	int ind;
	if (keys[0] && keys[0]->priority > p) {
		return C[0];
	}
	if (keys[1] && keys[1]->priority > p) {
		return C[1];
	}
	if (keys[2] && keys[2]->priority > p) {
		return C[2];
	}
	else if (keys[2] && keys[2]->priority < p) {
		return C[3];
	}

	return C[2];
}

Node* Node::searchNode(Node::Member* key, Node** prev) {
	if (!this) {
		return nullptr;
	}

	Node* curr = this;
	while (true) {
		if (curr->hasKey(*key)) {
			break;
		}
		else if (!curr->isLeaf()) {
			*prev = curr;
			curr = curr->fetchPointerPos(key);
		}
		else {
			*prev = curr;
			curr = nullptr;
			break;
		}
	}
	return curr;
}

int Node::splitChild(Node* x) {
	// Pravimo dva nova cvora, gde su sredisnji kljucevi crveni iz cvora koga splitujemo
	Node* z = new Node(x->keys[2], x->C[2], x->C[3]), * y = new Node(x->keys[0], x->C[0], x->C[1]);
	
	// Update parent pointers for the new children
	if (x->C[2]) x->C[2]->parent = z;
	if (x->C[3]) x->C[3]->parent = z;
	if (x->C[0]) x->C[0]->parent = y;
	if (x->C[1]) x->C[1]->parent = y;

	int pos = addNonFullKey(x->keys[1]); // ubacujemo sredisnji kljuc u this i vracamo poziciju umetanja
	C[pos] = y;
	C[pos + 1] = z;
	z->parent = y->parent = this; // azuriramo parent pokazivace

	for (Member*& k : x->keys)
		k = nullptr;
	delete x;
	return pos;
}

void Node::Merge(int target, int sibling) {

	Node* bro = C[sibling];
	Member* tmp = bro->keys[1];
	
	bro->keys[1] = keys[1];
	keys[1] = nullptr;

	if (cmpMem(bro->keys[1], tmp) > 0) {
		bro->keys[0] = tmp;

		if (!bro->isLeaf()) {
			bro->C[0] = bro->C[1];
			bro->C[1] = bro->C[2];
			bro->C[2] = C[target]->C[1];
			bro->C[2]->parent = bro;
		}
	}
	else {
		bro->keys[2] = tmp;

		if (!bro->isLeaf()) {
			bro->C[3] = bro->C[2];
			bro->C[2] = bro->C[1];
			bro->C[1] = C[target]->C[1];
			bro->C[1]->parent = bro;
		}
	}

	//We delete the target node
	delete C[target];
	C[target] = nullptr;

	//We will make it so that an 'empty node' has its only son in pos = 1
	C[sibling] = nullptr;
	C[1] = bro;

	n--;
}

bool Node::isRealBro(int i, int j)
{
	if (i == j || C[i] == nullptr || C[j] == nullptr || j > 3 || j < 0) return false;
	if ((i == 2 && j == 1 || i == 1 && j == 2) && Count() != 1 || abs(i - j) > 1) 
		return false;
	else
		return true;
}

void Node::realBroBorrow(int target, int bro, int pos) {
	C[target]->keys[1] = keys[pos];
	if (C[bro]->Count() == 2) {
		if (target > bro && C[bro]->keys[2]) {
			keys[pos] = C[bro]->keys[2];
			C[bro]->keys[2] = nullptr;
			// 1.2.1)
			if (!C[target]->isLeaf()) {
				C[target]->C[2] = C[target]->C[1]; //Prebacujem u slucaju merge - a

				C[target]->C[1] = C[bro]->C[3]; // Prebacujem sina iz brata, i null - ujemo ga
				C[bro]->C[3]->parent = C[target];
				C[bro]->C[3] = nullptr;
			}
		}
		else if (target < bro && C[bro]->keys[0]) {
			keys[pos] = C[bro]->keys[0];
			C[bro]->keys[0] = nullptr;

			// 1.1.1)
			if (!C[target]->isLeaf()) {
				C[target]->C[2] = C[bro]->C[0];
				C[bro]->C[0]->parent = C[target];
				C[bro]->C[0] = nullptr;
			}
		}
		else { // Slucaj kada brat nema crven cvor blizi target - u
			keys[pos] = C[bro]->keys[1];
			if (C[bro]->keys[2]) { // 1.1.2) slucaj
				C[bro]->keys[1] = C[bro]->keys[2];
				C[bro]->keys[2] = nullptr;
				
				if (!C[target]->isLeaf()) {
					C[target]->C[2] = C[bro]->C[1];
					C[bro]->C[1]->parent = C[target];
					C[bro]->C[1] = C[bro]->C[2];
					C[bro]->C[2] = C[bro]->C[3];
					C[bro]->C[3] = nullptr;
				}

			}
			else { // 1.2.2) slucaj
				C[bro]->keys[1] = C[bro]->keys[0];
				C[bro]->keys[0] = nullptr;

				if (!C[target]->isLeaf()) {
					C[target]->C[2] = C[target]->C[1];

					C[target]->C[1] = C[bro]->C[2];
					C[bro]->C[2]->parent = C[target];
					C[bro]->C[2] = C[bro]->C[1];
					C[bro]->C[1] = C[bro]->C[0];
					C[bro]->C[0] = nullptr;
				}
			}
		}
	}
	else {
		keys[pos] = C[bro]->keys[1];
		if (target > bro) {
			C[target]->keys[0] = C[bro]->keys[2];
			C[bro]->keys[2] = nullptr;
			C[bro]->keys[1] = C[bro]->keys[0];
			C[bro]->keys[0] = nullptr;

			// 2.2)
			if (!C[target]->isLeaf()) {
				C[target]->C[2] = C[target]->C[1];

				C[target]->C[1] = C[bro]->C[3];
				C[bro]->C[3]->parent = C[target];
				C[target]->C[0] = C[bro]->C[2];
				C[bro]->C[2]->parent = C[target];
				C[bro]->C[3] = nullptr;
				C[bro]->C[2] = C[bro]->C[1];
				C[bro]->C[1] = C[bro]->C[0];
				C[bro]->C[0] = nullptr;
			}
		}
		else {
			C[target]->keys[2] = C[bro]->keys[0];
			C[bro]->keys[0] = nullptr;
			C[bro]->keys[1] = C[bro]->keys[2];
			C[bro]->keys[2] = nullptr;

			// 2.1)
			if (!C[target]->isLeaf()) {
				C[target]->C[2] = C[bro]->C[0];
				C[bro]->C[0]->parent = C[target];
				C[target]->C[3] = C[bro]->C[1];
				C[bro]->C[1]->parent = C[target];
				C[bro]->C[0] = nullptr;
				C[bro]->C[1] = C[bro]->C[2];
				C[bro]->C[2] = C[bro]->C[3];
				C[bro]->C[3] = nullptr;
			}

		}
	}

	--C[bro]->n;
}

void Node::realBroMerge(int target, int bro, int pos) {
	/*delete C[target];
	C[target] = nullptr;*/
	Node* brother = C[bro];
	Node* t = C[target];
	int insert, del;
	if (pos == 0) {
		insert = max(target, bro);
		del = min(target, bro);
		if (target > bro) { // 1.1)
			//Node::Node(Member* valB, Node* mid1, Node* mid2, Member* valR1, Node* left, Member* valR2, Node* right, Node* parent)
			C[insert] = new Node(keys[pos], C[bro]->C[2], C[target]->C[1], C[bro]->keys[1], C[bro]->C[1], nullptr, nullptr, this);
		}
		else { // 1.2)
			C[insert] = new Node(keys[pos], C[target]->C[1], C[bro]->C[1], nullptr, nullptr, C[bro]->keys[1], C[bro]->C[2], this);
		}
		C[del] = nullptr;
	}
	else {
		insert = min(target, bro);
		del = max(target, bro);
		if (target > bro) { // 2.1)
			C[insert] = new Node(keys[pos], C[bro]->C[2], C[target]->C[1], C[bro]->keys[1], C[bro]->C[1], nullptr, nullptr, this);
		}
		else { // 2.2)
			C[insert] = new Node(keys[pos], C[target]->C[1], C[bro]->C[1], nullptr, nullptr, C[bro]->keys[1], C[bro]->C[2], this);
		}
		C[del] = nullptr;
	}
	if (brother) brother->keys[1] = nullptr;
	delete brother;
	delete t;
	n--;
	keys[pos] = nullptr;
}

void Node::cousinBorrow(int t, int c) {
	Node* target = C[t], * cousin = C[c];


	target->keys[1] = keys[1];

	if (t > c) {
		keys[1] = keys[0];
		keys[0] = nullptr;
	}
	else {
		keys[1] = keys[2];
		keys[2] = nullptr;
	}

	if (cousin->Count() == 2) {
		if (t > c && cousin->keys[2]) {
			keys[2] = C[c]->keys[2];
			cousin->keys[2] = nullptr;

			if (!C[t]->isLeaf()) {
				C[t]->C[2] = C[t]->C[1]; //Prebacujem u slucaju merge - a

				C[t]->C[1] = C[c]->C[3]; // Prebacujem sina iz brata, i null - ujemo ga
				C[c]->C[3]->parent = C[t];
				C[c]->C[3] = nullptr;
			}

		}
		else if (t < c && cousin->keys[0]) {
			keys[0] = C[c]->keys[0];
			C[c]->keys[0] = nullptr;

			if (!C[t]->isLeaf()) {
				C[t]->C[2] = C[c]->C[0];
				C[c]->C[0]->parent = C[t];
				C[c]->C[0] = nullptr;
			}
		}
		else {
			if (cousin->keys[2]) { // && t < c
				keys[0] = C[c]->keys[1];
				C[c]->keys[1] = C[c]->keys[2];
				C[c]->keys[2] = nullptr;

				if (!C[t]->isLeaf()) {
					C[t]->C[2] = C[c]->C[1];
					C[c]->C[1]->parent = C[t];
					C[c]->C[1] = C[c]->C[2];
					C[c]->C[2] = C[c]->C[3];
					C[c]->C[3] = nullptr;
				}
			}
			else { // t > c && cousin->keys[0]
				keys[2] = C[c]->keys[1];
				C[c]->keys[1] = C[c]->keys[0];
				C[c]->keys[0] = nullptr;

				if (!C[t]->isLeaf()) {
					C[t]->C[2] = C[t]->C[1];

					C[t]->C[1] = C[c]->C[2];
					C[c]->C[2]->parent = C[t];
					C[c]->C[2] = C[c]->C[1];
					C[c]->C[1] = C[c]->C[0];
					C[c]->C[0] = nullptr;
				}
			}
		}
	}

	if (cousin->Count() == 3) {
		if (t > c) {
			keys[2] = C[c]->keys[1];
			C[c]->keys[1] = C[c]->keys[0];
			C[c]->keys[0] = nullptr;
			C[t]->keys[0] = C[c]->keys[2];
			C[c]->keys[2] = nullptr;

			if (!C[t]->isLeaf()) {
				C[t]->C[2] = C[t]->C[1];

				C[t]->C[1] = C[c]->C[3];
				C[c]->C[3]->parent = C[t];
				C[t]->C[0] = C[c]->C[2];
				C[c]->C[2]->parent = C[t];
				C[c]->C[3] = nullptr;
				C[c]->C[2] = C[c]->C[1];
				C[c]->C[1] = C[c]->C[0];
				C[c]->C[0] = nullptr;
			}
		}
		else {
			keys[0] = C[c]->keys[1];
			C[c]->keys[1] = C[c]->keys[2];
			C[c]->keys[2] = nullptr;
			C[t]->keys[2] = C[c]->keys[0];
			C[c]->keys[0] = nullptr;

			if (!C[t]->isLeaf()) {
				C[t]->C[2] = C[c]->C[0];
				C[c]->C[0]->parent = C[t];
				C[t]->C[3] = C[c]->C[1];
				C[c]->C[1]->parent = C[t];
				C[c]->C[0] = nullptr;
				C[c]->C[1] = C[c]->C[2];
				C[c]->C[2] = C[c]->C[3];
				C[c]->C[3] = nullptr;
			}
		}

		--cousin->n;
		++target->n;
	}
	
	if (t > c) {
		for (int i = 3; i >= 1; i--) C[i] = C[i - 1];
		C[0] = nullptr;
	}
	else {
		for (int i = 0; i <= 2; i++) C[i] = C[i + 1];
		C[3] = nullptr;
	}

	--cousin->n;
	++target->n;
}

void Node::cousinMerge(int t, int c) {
	Node* target = C[t], * cousin = C[c];

	if (t > c) {
		cousin->keys[0] = cousin->keys[1];
		cousin->keys[1] = keys[1];
		keys[1] = keys[0];
		keys[0] = nullptr;
		
		cousin->C[0] = cousin->C[1];
		cousin->C[1] = cousin->C[2];
		cousin->C[2] = target->C[1];
		if (!cousin->isLeaf())
			cousin->C[2]->parent = cousin;
		
		delete C[2];
		C[2] = C[1];
		C[1] = C[0];
		C[0] = nullptr;
	}
	else {
		cousin->keys[2] = cousin->keys[1];
		cousin->keys[1] = keys[1];
		keys[1] = keys[2];
		keys[2] = nullptr;

		cousin->C[3] = cousin->C[2];
		cousin->C[2] = cousin->C[1];
		cousin->C[1] = target->C[1];
		if (!cousin->isLeaf())
			cousin->C[1]->parent = cousin;

		delete C[1];
		C[1] = C[2];
		C[2] = C[3];
		C[3] = nullptr;
	}
}

Node::Member* Node::getSucc(int ind, int& pos) {
	if (!this->isLeaf()) {
		Node* curr = C[ind + 1];
		while (!curr->isLeaf()) {
			if (curr->keys[0])
				curr = curr->C[0];
			else
				curr = curr->C[1];
		}

		pos = (curr->keys[0]) ? 0 : 1;
		return (curr->keys[0]) ? curr->keys[0] : curr->keys[1];
	}
	else {
		if (ind + 1 < 3 && this->keys[ind + 1]) {
			pos = ind + 1;
			return keys[ind + 1];
		}
		else {
			Node* parent = this->parent;
			Node* curr = this;
			while (parent) {
				int i = 0;
				while (i <= 3 && parent->C[i] != curr)
					i++;
				if (i < 3 && parent->keys[i]) {
					pos = i;
					return parent->keys[i];
				}
				curr = parent;
				parent = curr->parent;
			}
		}
	}
	pos = -1;
	return nullptr;
}

Node::Member* Node::getPred(int ind, int& pos) {
	if (!this->isLeaf()) {
		Node* curr = C[ind];
		while (!curr->isLeaf()) {
			if (curr->keys[2])
				curr = curr->C[3];
			else
				curr = curr->C[2];
		}

		pos = (curr->keys[2]) ? 2 : 1;
		return (curr->keys[2]) ? curr->keys[2] : curr->keys[1];
	}
	else {
		if (ind - 1 >= 0 && this->keys[ind - 1]) {
			pos = ind - 1;
			return keys[ind - 1];
		}
		else {
			Node* parent = this->parent;
			Node* curr = this;
			while (parent) {
				int i = 0;
				while (i <= 3 && parent->C[i] != curr)
					i++;
				if (i > 0 && parent->keys[i - 1]) {
					pos = i - 1;
					return parent->keys[i - 1];
				}
				curr = parent;
				parent = curr->parent;
			}
		}
	}

	pos = -1;
	return nullptr;
}

void Node::insertNonFull(Member* key) {
	if (this->isLeaf()) {
		addNonFullKey(key);
	}
	else { // nije list
		int i ,j;
		if (Count() == 1) {
			i = j = 1;
		}
		else if (keys[0]) {
			i = 1;
			j = 0;
		}
		else {
			i = 2;
			j = 1;
		}
		while (i >= j && cmpMem(keys[i], key) > 0)
			i--;
		

		if ((C[i + 1])->isFull()) { // Ukoliko je sledeci cvor pun, splitujemo
			 i = splitChild(C[i + 1]);
			 if (cmpMem(keys[i], key) < 0)
				 i++;
		}

		C[i]->insertNonFull(key); // Nastavljamo dalje do lista;
	}
}

int Node::addNonFullKey(Member* key)
{
	int pos = {-1};
	if (!keys[1]) { // Specijalan slucaj kada lomimo koren
		keys[1] = key;
		pos = 1;
	} else if (cmpMem(keys[1], key) >= 0) {
		if (keys[0] == nullptr) {
			keys[0] = key;
			pos = 0;
		}
		else {
			keys[2] = keys[1];
			C[3] = C[2];
			C[2] = C[1];
			if (cmpMem(keys[0], key) == -1) {
				keys[1] = key;
				pos = 1;
			}
			else {
				keys[1] = keys[0];
				C[1] = C[0];
				keys[0] = key;
				pos = 0;
			}
		}
	}
	else if (cmpMem(keys[1], key) == -1) {
		if (keys[2] == nullptr) {
			keys[2] = key;
			pos = 2;
		}
		else {
			keys[0] = keys[1];
			C[0] = C[1];
			C[1] = C[2];
			if (cmpMem(keys[2], key) >= 0) {
				keys[1] = key;
				pos = 1;
			}
			else {
				keys[1] = keys[2];
				C[2] = C[3];
				keys[2] = key;
				pos = 2;
			}
		}
	}

	n++; // inkrementiramo keys[1]roj kjluceva u cvoru
	return pos;
}

void Node::printNode(HANDLE hConsole, ostream& os) {
	Color col[] = { RED, BLACK, RED };
	os << "[";
	for (int i = 0; i < 3; i++) {
		if (keys[i]) {
			SetConsoleTextAttribute(hConsole, col[i]);
			ios init(NULL);
			init.copyfmt(os);
			os << setw(1) << keys[i]->action[0] << setw(3) << keys[i]->priority;
			os.copyfmt(init);
		}
		else {
			os << "    ";
		}
		SetConsoleTextAttribute(hConsole, WHITE);
		if (i != 2) {
			os << "|";
		}
		else {
			os << "]";
		}
	}

}



int cmpMem(Node::Member* mem1, Node::Member* mem2)
{
	if (!mem1 || !mem2) return 0;
	if (mem1->priority < mem2->priority ||
		mem1->priority == mem2->priority && mem1->action < mem2->action) {
		return -1;
	}
	if (mem1->priority > mem2->priority ||
		mem1->priority == mem2->priority && mem1->action > mem2->action) {
		return 1;
	}

	return 0;
}
