#include "RB234Tree.h"

#include <fstream>

int cnt = 0;

int main() {
	RB234Tree tree;
	ifstream file;
	bool has_only_digits;
	string name, line, num_str;
	Node* prev, * found;
	int choice = -1, priority, new_p, pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	while (choice) {
		cout << "***************************************************************\n"
			"Unesite zeljeni broj opcije:\n"
			"1. Formiranje stabla na osnovu datoteke\n"
			"2. Umetanje nove akcije u stable\n"
			"3. Pretrazivanje stabla po prioritetu akcije\n"
			"4. Brisanje proizvoljne akcije po prioritetu\n"
			"5. Brisanje akcije najveceg prioritet\n"
			"6. Ispis stabla kao 2-3-4 stablo\n"
			"7. Ispis stabla kao RB - stablo\n"
			"8. Izmena prioriteta akcije\n"
			"9. Pronalazenje ukupnog broja akcija sa zadatim prioritetom\n"
			"10. Brisanje trenutno ucitanog stabla\n"
			"0. Izlaz iz programa\n"
			"***************************************************************\n"
			"Vas izbor?  ";

		getline(cin, num_str);
		has_only_digits = (num_str.find_first_not_of("0123456789") == std::string::npos);
		if (has_only_digits && num_str != "") {
			choice = stoi(num_str);
		}
		else {
			choice = -1;
		}
		switch (choice) {
		case 1:

			if (!tree.isEmpty()) {
				tree.DeleteTree();
			}

			cout << "Unesite naziv datoteke iz koje zelite da citate: ";
			getline(cin, name);

			
			file.open(name);
			if (!file.is_open()) {
				cout << "Greska pri citanju!" << endl;
				break;
			}
			tree.inputFromFile(file);
			cout << "Stablo je uspesno procitano." << endl;
			file.close();
			break;
		case 2:
			cout << "Unesite naziv i prioritet akcije koje zelite da unesete: ";
			
			if (tree.inputAction(cin)) {
				cout << "Nova akcija je ucitana." << endl;
			}
			else {
				cout << "Akcija vec postoji u stablu!" << endl;
			}
			break;
		case 3: 
			cout << "Unesite prioritet akcije za koji zelite da izvrsite pretragu: ";
			getline(cin, num_str);
			has_only_digits = (num_str.find_first_not_of("0123456789") == std::string::npos);
			if (has_only_digits && num_str != "") {
				priority = stoi(num_str);
			}
			else {
				cout << "Greska pri unosu!" << endl;
				break;
			}
			if (found = tree.searchPriorityNode(priority, &prev)) {
				cout << "Pronadjena akcija: ";
				found->getKey(found->getKeyPosforP(priority))->printMember(cout) << endl;
			}
			else {
				cout << "Ne postoji akcija sa zadatim prioritetom." << endl;
			}
			break;
		case 4:
			cout << "Unesite prioritet koji zelite da brisete: ";
			getline(cin, num_str);
			has_only_digits = (num_str.find_first_not_of("0123456789") == std::string::npos);
			if (has_only_digits && num_str != "") {
				priority = stoi(num_str);
			}
			else {
				cout << "Greska pri unosu!" << endl;
				break;
			}
			if (tree.DeletePriority(priority)) {
				cout << "Akcija je uspesno izbrisana." << endl;
			}
			else {
				cout << "Ne postoji akcija sa zadatime prioritetom." << endl;
			}
			break;
		case 5:
			if (tree.DeleteMaxPriority()) {
				cout << "Akcija je uspesno izbrisana." << endl;
			}
			else {
				cout << "Ne postoji akcija sa zadatime prioritetom." << endl;
			}
			break;
		case 6:
			cout << tree;
			break;
		case 7:
			tree.printRBTree(cout);
			break;
		case 8:
			cout << "Unesite prioritet i naziv akcije koju zelite da menjate: " << endl;

			getline(cin, line);
			pos = line.find_last_of(" ");
			if (pos != string::npos) {
				name = line.substr(0, pos);
				num_str = line.erase(0, pos + 1);
				has_only_digits = (num_str.find_first_not_of("0123456789") == std::string::npos);
				if (has_only_digits && num_str != "") {
					priority = stoi(num_str);
				}
				else {
					cout << "Greska pri unosu!" << endl;
					break;
				}
			}
			else {
				cout << "Greska pri unosu!" << endl;
				break;
			}
			if (name.length() > 256) {
				cout << "Greska pri unosu!" << endl;
				break;
			}

			cout << "Unesite novi prioritet: ";
			getline(cin, num_str);
			has_only_digits = (num_str.find_first_not_of("0123456789") == std::string::npos);
			if (has_only_digits && num_str != "") {
				new_p = stoi(num_str);
			}
			else {
				cout << "Greska pri unosu!" << endl;
				break;
			}
			if (tree.changePriority(name, priority, new_p)) {
				cout << "Prioritet je uspesno promenjen." << endl;
			}
			else {
				cout << "Akcija sa identicnim imenom i prioritetom vec postoji!" << endl;
			}
			break;
		case 9:
			cout << "Unesite vrednost prioriteta: ";
			getline(cin, num_str);
			has_only_digits = (num_str.find_first_not_of("0123456789") == std::string::npos);
			if (has_only_digits && num_str != "") {
				priority = stoi(num_str);
			}
			else {
				cout << "Greska pri unosu!" << endl;
				break;
			}
			cout << "Broj akcija sa prioritetom " << priority << " je " << tree.keysWithPriority(priority) << endl;
			break;
		case 10:
			tree.DeleteTree();
			cout << "Stablo je obrisano." << endl;
			break;
		case 0: break;
		default: cout << "Nepostojece opcija!" << endl;
		}
	}
	return 0;
}