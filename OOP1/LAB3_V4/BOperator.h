#ifndef _boperator_h_
#define _boperator_h_

#include "Element.h"

class  BOperator : public Element {
public:
	virtual int dohvPrioritet() const = 0;

	friend bool operator>(const BOperator& op1, const BOperator& op2) {
		return op1.dohvPrioritet() > op2.dohvPrioritet();
	}

	friend bool operator<(const BOperator& op1, const BOperator& op2) {
		return op1.dohvPrioritet() < op2.dohvPrioritet();
	}

	char dohvOzn() const override { return 'O'; }
};

#endif // !_operator_h_

