#ifndef _mec_h
#define _mec_h

#include "Privilegovani.h"
#include "Par.h"

class GNijeOdigran : public exception {
public:
	GNijeOdigran() : exception("*** Mec nije jos odigran! ***") {}
};

class Mec {
	enum class Ishod { NEODIGRAN, POBEDA_DOMACIN, NERESENO, POBEDA_GOST };

	Par<Tim, Tim> timovi;
	Ishod ishod = Ishod::NEODIGRAN;
	int poeni_dom, poeni_gost;

	void azurirajTimove(Tim* pobednik, Tim* gubitnik);
public:
	Mec(Tim& domacin, Tim& gost) : timovi(domacin, gost) {}

	Par<Tim,Tim> dohvTimove() const { return timovi; }

	void odigrajMec();

	bool jeOdigran() const { return ishod != Ishod::NEODIGRAN; }

	Par<int, int> dohvPoene();

	friend ostream& operator<<(ostream& os, const Mec& m);

};

#endif // !_mec_h_