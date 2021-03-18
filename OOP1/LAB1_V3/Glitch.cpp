#include "Glitch.h"

std::ostream& operator<<(std::ostream& os, const Glitch& g) {
	return os << g.date << '-' << g.desc;
}
