#ifndef _USER_H_
#define _USER_H_

#include <iostream>
#include <string>

using namespace std;

class User {
public:
	User(string n);

	User(const User&) = delete;

	User& operator=(const User&) = delete;

	string getName() const { return username; }

	friend ostream& operator<<(ostream& os, const User& u);

	void sendNotice(User& recipient, string txt = "");

protected:
	string username;
};
#endif // !_USER_H_

