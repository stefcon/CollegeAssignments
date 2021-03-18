#ifndef _WARRANTY_H_
#define _WARRANTY_H_

#include "Glitch.h"
#include <vector>


class Warranty {
	Glitch ** glitches;
	int size;
	Date start, end;

	void AddEl(Glitch g);

	void copy(const Warranty&);
	void move(Warranty&);
	void clear();

public:
	Warranty(Date s, Date e) : start(s), end(e), size(0), glitches(nullptr) {}

	Warranty(const Warranty& w);

	Warranty(Warranty&& w);

	Warranty& operator=(const Warranty& w);

	Warranty& operator=(Warranty&& w);

	~Warranty();

	bool addGlitch(Glitch g);

	int getNum() const { return size; }

	Glitch& getLastGlitch();

	friend std::ostream& operator<<(std::ostream& os, const Warranty& w);
};
#endif // !_WARRANTY_H_

