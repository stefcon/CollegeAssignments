#include "Destinacija.h"

Destinacija& Destinacija::oceni(int ocena) {
	if (ocena >= 1 && ocena <= 5) {
		prosek = (prosek * br_ocena + ocena) / (br_ocena + 1);
		br_ocena++;
	}

	return *this;
}
