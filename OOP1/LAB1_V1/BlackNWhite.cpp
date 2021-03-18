#include "BlackNWhite.h"

BlackNWhite& BlackNWhite::operator=(const BlackNWhite& b) {
	if (this != &b) {
		clear();
		copy(b);
	}
	return *this;
}

BlackNWhite& BlackNWhite::operator=(BlackNWhite&& b) {
	if (this != &b) {
		clear();
		move(b);
	}
	return *this;
}

bool BlackNWhite::setPixel(const Pixel& p, const Position& pos) {
	int red = p.getRed(), green = p.getGreen(), blue = p.getBlue();
	double ari = (red + green + blue) / 3.;
	if (ari > 127) {
		Picture::setPixel(Pixel(255, 255, 255), pos);
	}
	else {
		Picture::setPixel(Pixel(), pos);
	}

	return true;
}
