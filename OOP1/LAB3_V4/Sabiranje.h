#ifndef _sabiranje_h_
#define _sabiranje_h_

#include "BOperator.h"

class Sabiranje : public BOperator {
public:
	Sabiranje* kopija() const {
		return new Sabiranje(*this);
	}

	std::string dohvTekst() const override { return "+"; }

	int dohvPrioritet() const override { return 1; }
};

#endif // !_sabiranje_h_

