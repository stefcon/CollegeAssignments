#include "Mec.h"

ostream& operator<<(ostream& os, const Mec& m) {
	os << m.timovi;
	if (m.ishod != Mec::Ishod::NEODIGRAN) {
		if (m.ishod == Mec::Ishod::POBEDA_DOMACIN) {
			os << " 1";
		}
		else if (m.ishod == Mec::Ishod::NERESENO) {
			os << " x";
		}
		else {
			os << " 2";
		}
	}
	return os;
}

void Mec::azurirajTimove(Tim* pobednik, Tim* gubitnik) {
	int br1 = pobednik->dohvBroj();
	int br2 = gubitnik->dohvBroj();
	int cnt = 0;
	while (br1) {
		if ((*pobednik)[cnt]) {
			(*pobednik)[cnt]->promenaVr(10);
			br1--;
		}
		cnt++;
	}
	cnt = 0;
	while (cnt < br2) {
		if ((*gubitnik)[cnt]) {
			(*gubitnik)[cnt]->promenaVr(-10);
			br2--;
		}
		cnt++;
	}
}

void Mec::odigrajMec() {
	int ocena1 = timovi.dohvPrvi()->srednjaVr();
	int ocena2 = timovi.dohvDrugi()->srednjaVr();
	if (ocena1 > ocena2) {
		azurirajTimove(timovi.dohvPrvi(), timovi.dohvDrugi());
		ishod = Mec::Ishod::POBEDA_DOMACIN;
		poeni_dom = 3;
		poeni_dom = 0;
	}
	else if (ocena1 < ocena2) {
		azurirajTimove(timovi.dohvDrugi(), timovi.dohvPrvi());
		ishod = Mec::Ishod::POBEDA_GOST;
		poeni_dom = 0;
		poeni_dom = 3;
	}
	else {
		ishod = Mec::Ishod::NERESENO;
		poeni_dom = poeni_gost = 1;
	}
}

Par<int, int> Mec::dohvPoene() {
	if (ishod == Ishod::NEODIGRAN) throw GNijeOdigran();
	return Par<int, int>(poeni_dom, poeni_gost);
}
