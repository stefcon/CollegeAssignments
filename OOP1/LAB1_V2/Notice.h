#ifndef _NOTICE_H_
#define _NOTICE_H_

#include <iostream>
#include <ctime>
#include "User.h"
//class User;

using namespace std;

class Notice {
public:
	Notice(User* u);

	int getId() const { return id; }

	User* getUser() const { return user; }

	bool isRead() const { return read; }

	void Read() { read = true; }

	friend ostream& operator<<(ostream& os, const Notice & n);

protected:
	int id;
	struct tm* ct;
	bool read;
	User* user;

	static int id_cnt;

	virtual void write(ostream& os) const;
};


#endif // !_NOTICE_H_


