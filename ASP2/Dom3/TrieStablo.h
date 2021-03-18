#ifndef _triestablo_h_
#define _triestablo_h_


#include "Stablo.h"
#include <filesystem>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>

struct Rec {
    int frek;
    std::string rec;

    Rec(std::string r, int f = 1) : rec(r), frek(f) {}
};

class TrieStablo : public Stablo  
{
protected:

    class TrieCvor
    {

	    TrieCvor  * m_niz_pokazivaca[255];
        TrieCvor * m_roditelj;
	    Rec * m_info;
        int m_brojPodstabala;

        TrieCvor(const TrieCvor &) { }
        TrieCvor &operator=(const TrieCvor &) { }
        void iterativniDest();
    public:
	    TrieCvor(TrieCvor *roditelj);

	    virtual ~TrieCvor();

        TrieCvor *roditelj() {
                return m_roditelj;
        }

	    TrieCvor * pronadjiPodstablo(char deoKljuca);
	    void dodajPodstablo(char deoKljuca, TrieCvor *cvor);
        void ukloniPodstablo(char deoKljuca);

        int brojPodstabala() const { return m_brojPodstabala; }

        Rec * dohvatiInfo();
        void postaviInfo(const char *tekst);

        void poseti(ostream &it);
    };


    TrieCvor * m_koren;



    TrieStablo(const TrieStablo &) { }
    TrieStablo &operator=(const TrieStablo &) { }

    TrieCvor * pronadjiCvor(const char *kljuc);   // pronalazi cvor koji sadrzi dati kljuc

    void sugerisiReci(TrieCvor* koren, priority_queue<pair<int, string>>& preporuke);

    void kreirajPrefikse(unordered_set<string>& skup_prefiksa, string prefiks);

public:
	TrieStablo();
	virtual ~TrieStablo();

    static unordered_map<char, vector<char>> kreirajMapuSuseda();

    void predvidjanjeReci(string prefiks);

	virtual bool umetni(const char *kljuc, const char *podaci);
	virtual bool obrisi(const char *kljuc);

    virtual void obidji(ostream &it);

    virtual string * dohvatiInfo(const char *kljuc);

    bool azurirajFrek(const char* kljuc, int frekvencija);

    Rec* dohvatiStuct(const char* kljuc);

    void procitajFajl(ifstream& fajl);

    void procitajDirektorijum(string put);

    Rec* pretragaRecnika(const char* kljuc, bool azuriraj = false);
};

#endif
