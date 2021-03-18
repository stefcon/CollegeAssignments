#ifndef _operand_h_
#define _operand_h_

#include "Element.h"

class Operand : public Element {
	std::string natpis;
public:
	Operand(std::string nat) : natpis(nat) {}

	Operand* kopija() const override{
		return new Operand(*this);
	}

	char dohvOzn() const override { return 'D'; }
	
	std::string dohvTekst() const override { return natpis; }
};

#endif // !_operand_h_

