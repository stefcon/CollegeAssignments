#include "User.h"

User::User(string n) {
	username = n;
}

//void User::sendNotice(User& recipient, string txt) {
//	Notice* notice;
//	if (txt == "") {
//		notice = new Notice(this);
//	}
//	else {
//		notice = new Publication(this, txt);
//	}
//
//	recipient.list += *notice;
//}

ostream& operator<<(ostream& os, const User& u) {
	return os << u.username;
}
