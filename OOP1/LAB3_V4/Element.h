#ifndef _element_h_
#define _element_h_

#include <string>
#include <iostream>
class Element {
public:
	virtual Element* kopija() const = 0;

	virtual char dohvOzn() const = 0;

	virtual std::string dohvTekst() const = 0;

	friend std::ostream& operator<<(std::ostream& os, const Element& e) {
		return os << e.dohvTekst();
	}

	virtual ~Element() {}

};
#endif // !_element_h

