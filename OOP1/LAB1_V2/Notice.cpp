#include "Notice.h"

int Notice::id_cnt = 1;

Notice::Notice(User* u) {
	user = u;
	read = false;
	id = id_cnt++;

	time_t t; 
	time(&t);
	ct = localtime(&t);
}

void Notice::write(ostream& os) const {
	os << id << '|' << user->getName() << '-' << ct->tm_hour << ':' << ct->tm_min << ':' << ct->tm_sec << endl;
}

ostream& operator<<(ostream& os, const Notice& n) {
	n.write(os);
	return os;
}
