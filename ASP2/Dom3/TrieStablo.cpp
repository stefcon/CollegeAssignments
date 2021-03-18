#include "TrieStablo.h"

TrieStablo::TrieCvor::TrieCvor(TrieStablo::TrieCvor* roditelj) : m_roditelj(roditelj), m_info(0), m_brojPodstabala(0)
{
	for (int i = 0; i < 255; i++)
		m_niz_pokazivaca[i] = 0;
}

TrieStablo::TrieCvor::~TrieCvor()
{
	if (m_info)
		delete m_info;

	for (int i = 0; i < 255; i++)
		if (m_niz_pokazivaca[i])
			delete m_niz_pokazivaca[i];
}


TrieStablo::TrieCvor* TrieStablo::TrieCvor::pronadjiPodstablo(char deoKljuca)
{
	return m_niz_pokazivaca[deoKljuca];
}

void TrieStablo::TrieCvor::dodajPodstablo(char deoKljuca, TrieStablo::TrieCvor* cvor)
{
	if (!m_niz_pokazivaca[deoKljuca])
	{
		m_niz_pokazivaca[deoKljuca] = cvor;
		m_brojPodstabala++;
	}
}

void TrieStablo::TrieCvor::ukloniPodstablo(char deoKljuca)
{
	if (m_niz_pokazivaca[deoKljuca])
	{
		m_niz_pokazivaca[deoKljuca] = 0;
		m_brojPodstabala--;
	}
}

void TrieStablo::TrieCvor::postaviInfo(const char* tekst)
{
	if (m_info)
	{
		m_info->frek += 1;
		return;
	}

	if (tekst)
	{
		m_info = new Rec(tekst);
	}
}

Rec* TrieStablo::TrieCvor::dohvatiInfo()
{
	return m_info;
}


void TrieStablo::TrieCvor::poseti(ostream& it)
{
	if (m_info)
		it << m_info->rec << endl;

	for (int i = 0; i < 255; i++)
		if (m_niz_pokazivaca[i])
			m_niz_pokazivaca[i]->poseti(it);
}



//---------------------------------------------------------------


TrieStablo::TrieCvor* TrieStablo::pronadjiCvor(const char* kljuc)
{
	if (!m_koren)
		return 0;

	TrieCvor* tek = m_koren;

	for (int i = 0; i < strlen(kljuc) && tek; i++)
		tek = tek->pronadjiPodstablo(kljuc[i]);

	return tek;
}

Rec* TrieStablo::dohvatiStuct(const char* kljuc)
{
	TrieCvor* cvor = pronadjiCvor(kljuc);

	if (cvor)
		return cvor->dohvatiInfo();

	return 0;
}

void TrieStablo::procitajFajl(ifstream& fajl)
{
	string rec = "";
	while (fajl >> rec) {
		if (all_of(rec.begin(), rec.end(), [](char c) { return isalpha(c); })) {
			umetni(rec.c_str(), rec.c_str());
		}
		else {
			rec = (rec[0] != '(') ? rec : rec.substr(1);
			rec = (isalpha(rec.back())) ? rec : rec.substr(0, rec.length() - 1);
			if (all_of(rec.begin(), rec.end(), [](char c) { return isalpha(c); }) && !rec.empty())
				umetni(rec.c_str(), rec.c_str());
		}
	}
}

void TrieStablo::procitajDirektorijum(string put)
{
	for (auto& fajl : std::filesystem::directory_iterator(put))
	{
		string put_string = string(fajl.path().u8string());
		if (put_string.substr(put_string.find_last_of('.')) == ".txt") {
			ifstream fs{ fajl.path() };
			procitajFajl(fs);
			fs.close();
		}
	}
}

Rec* TrieStablo::pretragaRecnika(const char* kljuc, bool azuriraj)
{
	Rec* struktura = dohvatiStuct(kljuc);
	if (struktura) {
		if (azuriraj) struktura->frek++;
		return struktura;
	}
	else {
		return nullptr;
	}

}

TrieStablo::TrieStablo() : m_koren(0)
{
}

TrieStablo::~TrieStablo()
{
	if (m_koren)
		delete m_koren;
}

unordered_map<char, vector<char>> TrieStablo::kreirajMapuSuseda()
{
	unordered_map<char, vector<char>> susedi;
	susedi['q'] = vector<char>{ 'q', 'w', 'a', 's' };
	susedi['w'] = vector<char>{ 'w', 'q', 'a', 's', 'e' };
	susedi['e'] = vector<char>{ 'e', 'd', 'w', 's', 'r' };
	susedi['r'] = vector<char>{ 'r', 'e', 'd', 'f', 't' };
	susedi['t'] = vector<char>{ 't','r', 'f', 'g', 'y' };
	susedi['y'] = vector<char>{ 'y', 't', 'g', 'h', 'u' };
	susedi['u'] = vector<char>{ 'u', 'y', 'h', 'j', 'i' };
	susedi['i'] = vector<char>{ 'i', 'u', 'j', 'l', 'o' };
	susedi['o'] = vector<char>{ 'o', 'i', 'k', 'l', 'p' };
	susedi['p'] = vector<char>{ 'p', 'o', 'k', 'l' };

	susedi['a'] = vector<char>{ 'a', 'q', 'w', 's', 'z' };
	susedi['s'] = vector<char>{ 's', 'w', 'a', 'z', 'd', 'e' };
	susedi['d'] = vector<char>{ 'd', 'e', 's', 'x', 'f', 'r' };
	susedi['f'] = vector<char>{ 'f', 'r', 'd', 'c', 'g', 't' };
	susedi['g'] = vector<char>{ 'g', 't', 'f', 'v', 'h', 'y' };
	susedi['h'] = vector<char>{ 'h', 'y', 'g', 'b', 'j', 'u' };
	susedi['j'] = vector<char>{ 'j', 'u', 'h', 'n', 'k', 'i' };
	susedi['k'] = vector<char>{ 'k', 'i', 'j', 'm', 'l', 'o' };
	susedi['l'] = vector<char>{ 'l', 'o', 'p', 'k', 'm' };

	susedi['z'] = vector<char>{ 'z', 'a', 's', 'd', 'x' };
	susedi['x'] = vector<char>{ 'x', 'z', 'd', 'c' };
	susedi['c'] = vector<char>{ 'c', 'x', 'f', 'v' };
	susedi['v'] = vector<char>{ 'v', 'c', 'g', 'b' };
	susedi['b'] = vector<char>{ 'b', 'v', 'h', 'n' };
	susedi['n'] = vector<char>{ 'n', 'b', 'j', 'm' };
	susedi['m'] = vector<char>{ 'm', 'n', 'j', 'k', 'l' };
	return susedi;
}

void TrieStablo::predvidjanjeReci(string prefiks)
{

	if (Rec* struktura = pretragaRecnika(prefiks.c_str(), true)) {
		cout << "Uneta rec postoji: " << endl;
		cout << "Rec: " << struktura->rec << endl;
		cout << "Frekvencija: " << struktura->frek << endl;
		return;
	}

	priority_queue<pair<int, string>> pq;

	TrieCvor* kraj_prefiksa = pronadjiCvor(prefiks.c_str());
	sugerisiReci(kraj_prefiksa, pq);
	if (pq.size() == 1) {
		int frek = pq.top().first;
		string rec = pq.top().second;
		cout << "Prefiks je jedinstven za rec " << rec << endl;
		cout << "Frekvencija: " << frek << endl;
		umetni(rec.c_str(), rec.c_str());
	}
	else {
		unordered_set<string> skup_prefiksa;
		kreirajPrefikse(skup_prefiksa, prefiks);
		pq = priority_queue<pair<int, string>>();

		for (auto elem : skup_prefiksa) {
			if (TrieCvor* tren = pronadjiCvor(elem.c_str())) {
				sugerisiReci(tren, pq);
			}
		}

		if (pq.empty()) {
			cout << "Nemoguce je generisati rec sa datim ogranicenjima!" << endl;
		}

		cout << "Zadata rec ne postoji u recniku. Sugestije: " << endl;
		int broj_opcija = 0;
		vector<string> reci;
		for (int i = 0; i < 3 && !pq.empty(); ++i) {
			broj_opcija++;
			pair<int, string> par = pq.top();
			pq.pop();

			cout << i + 1 << ". " << par.first << " " << par.second << endl;

			reci.push_back(par.second);
		}
		try {
			cout << "Ukucajte broj preporuke: ";
			int opcija;
			string broj_string;
			getline(cin, broj_string);
			bool ima_samo_cifre = (broj_string.find_first_not_of("0123456789") == string::npos);
			if (!ima_samo_cifre || broj_string == "") throw exception("String se ne moze konvertovati u int");
			opcija = stoi(broj_string);
			if (opcija < 1 || opcija > broj_opcija) throw exception("Greska prilikom odabira reci");
			umetni(reci[opcija - 1].c_str(), reci[opcija + 1].c_str());
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
	}
}


void TrieStablo::sugerisiReci(TrieCvor* koren, priority_queue<pair<int, string>>& preporuke)
{
	if (!koren)
		return;

	stack<TrieCvor*> stek;

	stek.push(koren);
	while (!stek.empty()) {
		TrieCvor* tren = stek.top();
		stek.pop();

		if (Rec* strukt = tren->dohvatiInfo()) {
			preporuke.push(make_pair(strukt->frek, strukt->rec));
		}
		if (tren->brojPodstabala()) {
			for (int i = 122; i >= 97; --i) {
				if (TrieCvor* sled = tren->pronadjiPodstablo(i))
					stek.push(sled);
			}
		}
	}
}

void TrieStablo::kreirajPrefikse(unordered_set<string>& skup_prefiksa, string prefiks)
{
	unordered_map<char, vector<char>> susedi = TrieStablo::kreirajMapuSuseda();
	for (auto el : susedi) {
		for (char c : el.second) {
			susedi[el.first].push_back(toupper(c));
		}
	}


	int duz = prefiks.length();

	for (int i = 0; i < duz - 2; ++i) {
		vector<char> indeks_i = susedi[prefiks[i]];
		for (int j = i + 1; j < duz - 1; ++j) {
			vector<char> indeks_j = susedi[prefiks[j]];
			for (int k = j + 1; k < duz; ++k) {
				vector<char> indeks_k = susedi[prefiks[k]];
				string prefiks_kop = string(prefiks);

				for (char prvo : indeks_i) {
					for (char drugo : indeks_j) {
						for (char trece : indeks_k) {
							prefiks_kop[i] = prvo;
							prefiks_kop[j] = drugo;
							prefiks_kop[k] = trece;

							skup_prefiksa.insert(prefiks_kop);
						}
					}
				}
			}
		}
	}
}

bool TrieStablo::umetni(const char* kljuc, const char* podaci)
{
	if (!m_koren)
	{
		m_koren = new TrieCvor(0);
		m_brCvorova++;
	}

	TrieCvor* tek = m_koren;
	TrieCvor* sledeci = 0;

	for (int i = 0; i < strlen(kljuc); i++)
	{

		sledeci = tek->pronadjiPodstablo(kljuc[i]);

		if (!sledeci)
		{
			sledeci = new TrieCvor(tek);
			tek->dodajPodstablo(kljuc[i], sledeci);
			m_brCvorova++;
		}

		tek = sledeci;
	}

	bool rezultat = true;
	if (sledeci->dohvatiInfo())
		rezultat = false;
	else
		m_brKljuceva++;

	sledeci->postaviInfo(podaci);

	return rezultat;
}

bool TrieStablo::obrisi(const char* kljuc)
{
	if (!m_koren)
		return false;

	TrieCvor* tek = pronadjiCvor(kljuc);
	if (!tek)
		return false;

	tek->postaviInfo(0);
	int i = strlen(kljuc) - 1;

	while (i >= 0 && tek && tek->brojPodstabala() == 0 && !tek->dohvatiInfo())
	{
		TrieCvor* roditelj = tek->roditelj();

		delete tek;
		m_brCvorova--;

		if (roditelj)
			roditelj->ukloniPodstablo(kljuc[i--]);
		else
			m_koren = 0;
		tek = roditelj;
	}

	m_brKljuceva--;
	return true;
}

void TrieStablo::obidji(ostream& it)
{
	if (m_koren)
		m_koren->poseti(it);
	else
		it << "Stablo je prazno." << endl;
}


string* TrieStablo::dohvatiInfo(const char* kljuc)
{
	TrieCvor* cvor = pronadjiCvor(kljuc);

	if (cvor)
		return &cvor->dohvatiInfo()->rec;

	return 0;
}

bool TrieStablo::azurirajFrek(const char* kljuc, int frekvencija)
{
	if (frekvencija <= 0)
		obrisi(kljuc);

	Rec* struktura = dohvatiStuct(kljuc);
	if (struktura) {
		struktura->frek = frekvencija;

		return true;
	}
	else {
		return false;
	}
}
