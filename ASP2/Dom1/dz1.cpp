#include "type.h"
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <cstdlib>


using namespace std;


int main() {
	bool end_prog = false;
	Matrix matrix;
	AVL tree, tree_org;
	
	while (!end_prog) {

		cout << "********************************************************************" << endl;
		cout << "Unesite broj zeljene opcije: " << endl;
		cout << "1. Unos matrice kljuceva" << endl;
		cout << "2. Pretraga na zadati kljuc" << endl;
		cout << "3. Generisanje matrice sa neopadajucim vrstama i kolonama" << endl;
		cout << "4. Ispis matrice" << endl;
		cout << "5. Evaluacija perfomansi u matrici kljuceva" << endl;
		cout << "6. Formiranje AVL stabla na osnovu matrice kljuceva" << endl;
		cout << "7. Pretraga stabla na zadatu vrednost kljuca" << endl;
		cout << "8. Umetanje novog kljuca u stablo" << endl;
		cout << "9. Formatiran ispis stabla" << endl;
		cout << "10. Poredjenje performansi prilikom pretrage matrice i odgovarajuceg AVL stabla" << endl;
		cout << "0. Izadji iz programa (ili prazna linija)" << endl;
		cout << "********************************************************************" << endl;
		int choice = -1, key, size;
		cout << "Vas izbor? "; cin >> choice;
		vector<int> keys;
		switch (choice)
		{
		case 1:
			matrix.input();
			break;
		case 2:
			if (matrix.isEmpty() == false) {
				cout << "Unesite kljuc za pretragu: ";
				cin >> key;
				if (matrix.search(key)) {
					cout << "Kljuc je pronadjen";
				}
				else {
					cout << "Kljuc nije pronadjen";
				}
				cout << endl;
			}
			else {
				cout << "Matrica nije uneta!" << endl;
			}
			break;
		case 3:
			int m, n, low, high;
			cout << "Unesite dimenzije matrice: "; cin >> m >> n;
			cout << "Unesite zeljeni opseg vrednosti: "; cin >> low >> high;
			matrix.generate(m, n, low, high);
			matrix.sort_mat();
			matrix.print();
			break;
		case 4:
			if (matrix.isEmpty() == false) {
				cout << "Matrica kljuceva: " << endl;
				matrix.print();
			}
			else {
				cout << "Matrica nije uneta!" << endl;
			}
			break;
		case 5:
			if (matrix.isEmpty() == false) {
				keys.empty();
				srand((unsigned)time(NULL));
				cout << "Unesite broj kljuceva i zeljeni opseg za koji zelite da testirate performanse: ";
				cin >> size >> low >> high;
				if (low > high) {
					int tmp;
					tmp = low, low = high, high = tmp;
				}

				cout << "Test uzorak: ";
				for (int i = 0; i < size; i++) {
					int num = rand() / (RAND_MAX + 1.) * (high - low) + low;
					keys.push_back(num);
					cout << num << " ";
				}
				cout << endl << "Prosecan broj provera za dat uzorak kljuceva: " << matrix.benchmark(keys) << endl;
			}
			else {
				cout << "Matrica nije uneta!" << endl;
			}
			break;
		case 6: 
			if (matrix.isEmpty() == false) {
				if (tree.isEmpty() == false) {
					tree.delete_tree();
					tree_org.delete_tree();
				}
				tree.create_tree(matrix);
				tree_org.create_tree(matrix);
				cout << "Stablo je kreirano" << endl;
			}
			else {
				cout << "Matrica nije uneta!" << endl;
			}
			break;
		case 7:
			if (tree.isEmpty() == false) {
				cout << "Unesite kljuc za pretragu: ";
				cin >> key;
				if (tree.interact(key, "search")) {
					cout << "Kljuc je pronadjen";
				}
				else {
					cout << "Kljuc nije pronadjen";
				}
				cout << endl;
			}
			else {
				cout << "AVL stablo nije napravljeno" << endl;
			}
			break;
		case 8:
			cout << "Unesite kljuc koji zelite da umetnete u stablo: ";
			cin >> key; tree.interact(key, "insert");
			cout << "Novo stablo: " << endl;
			tree.print();
			break;
		case 9:
			if (tree.isEmpty() == false) {
				cout << endl;
				tree.print();
				cout << endl;
			}
			else {
				cout << "AVL stablo nije napravljeno!" << endl;
			}
			break;
		case 10:
			if (matrix.isEmpty() || tree_org.isEmpty()) {
				cout << "Niste inicijalizovali matricu ili AVL stablo" << endl;
				break;
			}
			keys.empty();
			int sub_option;
			cout << "Unesite broj opcije za nacine unosa kljuceva:\n"
				"1. Standardni ulaz\n"
				"2. Datoteka\n";
			cin >> sub_option;
			if (sub_option == 1) {
				cout << "Unesite broj kljuceva koji zelite da unesete: ";
				cin >> size;
				cout << "Unesite vrednost kljuceva: ";
				for (int i = 0, num; i < size; i++) {
					cin >> num;
					keys.push_back(num);
				}
				cout << "\nProsecan broj provera potreban za dati uzorak pri pretrzi u matrici: " << matrix.benchmark(keys);
				cout << "\nProsecan broj provera potreban za dati uzorak pri pretrazi u AVL stablu: " << tree_org.benchmark(keys);
				cout << endl;
			}
			else if (sub_option == 2) {
				ifstream input;
				string name;
				cout << "Unesite naziv fajla: ";
				cin >> name;
				input.open(name);
				if (!input.good()) {
					cout << "Greska prilikom otvaranja fajla" << endl;
				}
				for (int num; input >> num; ) {
					keys.push_back(num);
				}
				input.close();
				cout << "Test kljucevi: ";
				for (auto n : keys) cout << n << " ";
				cout << endl;
				cout << "\nProsecan broj provera potreban za dati uzorak pri pretrzi u matrici: " << matrix.benchmark(keys);
				cout << "\nProsecan broj provera potreban za dati uzorak pri pretrazi u AVL stablu: " << tree_org.benchmark(keys);
				cout << endl;
			}
			else {
				cout << "Nepostojeca opcija!" << endl;
			}
			break;
		case 0:
			end_prog = true;
			break;
		default:
			cout << "Nepostojeca opcija!" << endl;
			break;
		}
	}
	

	return 0;
}