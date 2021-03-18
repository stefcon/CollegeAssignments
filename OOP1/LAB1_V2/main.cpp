#include "Notice_list.h"

using namespace std;

int main() {
	User u1("stefcon"), u2("cobran");
	Notice_list list;

	Notice* not1 = new Notice(&u1);
	Publication* pub1 = new Publication(&u2, "Zdravo Cobrane!");

	list += *not1;
	list += *pub1;

	cout << list;
	cout << +list << endl;
	cout << *list[1] << endl;
	!list;
	cout << +list << endl;

	
	return 0;
}