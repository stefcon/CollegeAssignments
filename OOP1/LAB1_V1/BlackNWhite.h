#ifndef _BLACKNWHITE_H_
#define _BLACKNWHITE_H_

#include "Picture.h"

class BlackNWhite : public Picture {
public:
	BlackNWhite(int h, int w, const Time& t) : Picture(h, w, t) {}

	BlackNWhite(const BlackNWhite& b) : Picture(b) {};

	BlackNWhite(BlackNWhite&& b) : Picture(std::move(b)) {};

	BlackNWhite& operator=(const BlackNWhite& b);

	BlackNWhite& operator=(BlackNWhite&& b);

	~BlackNWhite() {}

	bool setPixel(const Pixel& p, const Position& pos) override;
};
#endif // !_BLACKNWHITE_H_

