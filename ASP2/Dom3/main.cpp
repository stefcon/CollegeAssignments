#include <iostream>
#include <ctime>
using namespace std;


#include "TrieStablo.h"

int main() 
{
    TrieStablo* stablo = nullptr;

    int opcija;
    string broj_string;
    bool ima_samo_cifre;
    ifstream fajl;
    string naziv;
    int frekv;
    Rec* struktura;
    do {
        try {
            for (int i = 0; i < 70; ++i) cout << "*"; cout << endl;
            cout << "Unesite zeljenu opciju: " << endl;
            cout << "1. Stavaranje praznog recnika" << endl;
            cout << "2. Stvaranje recnika na osnovu zadate datoteke ili skupa datoteka" << endl;
            cout << "3. Pretrazivanje reci" << endl;
            cout << "4. Umetanje nove reci" << endl;
            cout << "5. Azuriranje frekvencija reci" << endl;
            cout << "6. Predvidjanje reci na osnovu zadatog stringa" << endl;
            cout << "7. Brisanje recnika" << endl;
            cout << "0. Izadji iz programa" << endl;
            for (int i = 0; i < 70; ++i) cout << "*"; cout << endl;
            cout << "Vas izbor? ";

            getline(cin, broj_string);
            ima_samo_cifre = (broj_string.find_first_not_of("0123456789") == string::npos);
            if (!ima_samo_cifre || broj_string == "") throw exception("Greska prilikom citanja opcija");
            opcija = stoi(broj_string);
        
            switch (opcija)
            {
            case 1:
                if (stablo)
                    delete stablo;
                stablo = new TrieStablo;
                cout << "Prazan recnik je kreiran." << endl;
                break;
            case 2:
                if (!stablo) throw exception("Greska: Recnik nije stvoren!");

                cout << endl << "Odaberite opcija za unos:" << endl;
                cout << "1. Iz jednog fajla" << endl;
                cout << "2. Iz direktorijuma" << endl;

                getline(cin, broj_string);
                if (!ima_samo_cifre && broj_string == "") throw exception("Greska prilikom citanja opcije");
                opcija = stoi(broj_string);
                
                if (opcija == 1) {
                    
                    cout << "Unesite putanju do fajla za citanje: ";
                    getline(cin, naziv);
                    fajl.open(naziv);
                    if (fajl.is_open()) {
                        stablo->procitajFajl(fajl);
                        cout << "Fajl je uspesno procitan." << endl;
                        stablo->ispisiStatistiku(cout);
                        fajl.close();
                    }
                    else {
                        cout << "Greska prilikom citanja fajla!" << endl;
                    }

                }
                else if (opcija == 2) {
                    cout << "Unesite putanju do direktorijuma: ";
                    getline(cin, naziv);
                    try {
                        stablo->procitajDirektorijum(naziv);
                        stablo->ispisiStatistiku(cout);
                    }
                    catch (exception e)
                    {
                        cout << e.what() << endl;
                    }
                }
                else {
                    cout << "Nepostojeca opcija." << endl;
                }
                break;
            case 3:
                if (!stablo) throw exception("Greska: Recnik nije stvoren!");

                cout << "Unesite rec za pretragu: ";
                getline(cin, naziv);
                struktura = stablo->pretragaRecnika(naziv.c_str());
                if (struktura) {
                    cout << "Rec " << naziv << " je pronadjena." << endl;
                    cout << "Frekvencija: " << struktura->frek << endl;
                }
                else {
                    cout << "Zadata rec ne postoji u recniku." << endl;
                }
                break;
            case 4:
                if (!stablo) throw exception("Greska: Recnik nije stvoren!");

                cout << "Unesite rec za umetanje u recnik: ";
                getline(cin, naziv);
                if (all_of(naziv.begin(), naziv.end(), [](char c) { return isalpha(c); }) == false)
                    throw exception("Rec se mora sastojati iskljucivo is malih i velikih");
                if (stablo->umetni(naziv.c_str(), naziv.c_str())) {
                    cout << "Rec je uspesno umetnuta." << endl;
                }
                else {
                    cout << "Frekvencija reci " << naziv << " je povecana za jedan." << endl;
                }
                break;
            case 5:
                if (!stablo) throw exception("Greska: Recnik nije stvoren!");

                cout << "Unesite rec za azuriranje: ";
                getline(cin, naziv);
                if (all_of(naziv.begin(), naziv.end(), [](char c) { return isalpha(c); }) == false)
                    throw exception("Rec se mora sastojati iskljucivo is malih i velikih");

                getline(cin, broj_string);
                if (!ima_samo_cifre || broj_string == "") throw exception("Greska prilikom citanja frekvencije");
                stablo->azurirajFrek(naziv.c_str(), stoi(broj_string));
                break;
            case 6:
                if (!stablo) throw exception("Greska: Recnik nije stvoren!");

                cout << "Unesite zeljenu rec: ";
                getline(cin, naziv);
                if (all_of(naziv.begin(), naziv.end(), [](char c) { return isalpha(c); }) == false)
                    throw exception("Rec se mora sastojati iskljucivo is malih i velikih");
                stablo->predvidjanjeReci(naziv);
                break;
            case 7:
                delete stablo;
                stablo = nullptr;
                cout << "Recnik je obrisan." << endl;
                break;
            case 0:
                cout << "Kraj programa" << endl;
                if (stablo)
                    delete stablo;
                continue;
                break;
            default:
                cout << "Nepostojeca opcija!" << endl;
                break;
            }
        }
        catch (exception e) {
            opcija = -1;
            cout << e.what() << endl;
        }
    } while (opcija != 0);
    
    return 0;
}