#ifndef _NOTICE_LIST_H_
#define _NOTICE_LIST_H_

#include "Publication.h"
#include "Notice.h"


using namespace std;

class Notice_list {
	struct ListNode {
		Notice* notice;
		ListNode* next;

		ListNode(Notice* n = nullptr, ListNode* nxt = nullptr) : notice(n), next(nxt) {}

		~ListNode() { delete notice; }
	};

	ListNode* head;
	int num;
public:
	Notice_list();

	~Notice_list();

	Notice_list(const Notice_list&) = delete;

	Notice_list& operator=(const Notice_list&) = delete;

	Notice_list& operator+=(Notice& n);

	void operator()();

	int operator+();

	void operator!();

	Notice* operator[](int id);

	friend ostream& operator<<(ostream& os, const Notice_list& n_l);

};
#endif // !_NOTICE_LIST_H_

