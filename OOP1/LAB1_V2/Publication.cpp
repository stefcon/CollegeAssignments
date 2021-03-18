#include "Publication.h"

Publication::Publication(User* u, string txt) : Notice(u) {
	text = txt;
}

void Publication::write(ostream& os) const {
	Notice::write(os);
	os << text << endl;
}
