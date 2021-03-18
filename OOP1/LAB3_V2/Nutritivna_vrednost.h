#ifndef _nutritivna_vrednost_h_
#define _nutritivna_vrednost_h_

#include <iostream>
using namespace std;


class Nutritivna_vrednost {
	double uh, masti, proteini;
public:
	Nutritivna_vrednost(double uglj, double mast, double prot) : uh(uglj), masti(mast), proteini(prot) {} 

	double dohvUh() const { return uh; }

	double dohvMasti() const { return masti; }

	double dohvProteini() const { return proteini; }

	friend Nutritivna_vrednost operator+(const Nutritivna_vrednost& nvr1, const Nutritivna_vrednost& nvr2) {
		return Nutritivna_vrednost(nvr1.uh + nvr2.uh, nvr1.masti + nvr2.masti, nvr1.proteini + nvr2.proteini);
	}

	double brojKalorija() const {
		return 9 * masti + 4 * (uh + proteini);
	}

	friend ostream& operator<<(ostream& os, const Nutritivna_vrednost& nvr) {
		return os << "[uh: " << nvr.uh << ", ma: " << nvr.masti << ", pr: " << nvr.proteini << "]";
	}
};

#endif // !_nutritivna_vrednost_h_

