#ifndef _GLITCH_H_
#define _GLITCH_H_

#include "Date.h"

class Glitch {
	std::string desc;
	Date date;
	bool removed;
public:
	Glitch(std::string description, Date d, bool r = false) : desc(description), date(d), removed(r) {}

	std::string getDesc() const { return desc; }

	Date getDate() const { return date; }

	bool isFixed() const { return removed; }

	void setStatus(bool val) { removed = val; }

	friend std::ostream& operator<<(std::ostream& os, const Glitch& g);

};
#endif // !_GLITCH_H_

