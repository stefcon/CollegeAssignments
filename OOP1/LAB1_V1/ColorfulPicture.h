#ifndef _COLORFUL_PICTURE_H_
#define _COLORFUL_PICTURE_H_

#include "Picture.h"
#include <random>

class ColorfulPicture : public Picture {
public:
	ColorfulPicture(int h, int w, const Time& t);

	ColorfulPicture(const ColorfulPicture& p) : Picture(p) {}

	ColorfulPicture(ColorfulPicture&& p) : Picture(std::move(p)) {}
	
	ColorfulPicture& operator=(const ColorfulPicture& p);

	ColorfulPicture& operator=(ColorfulPicture&& p);

	ColorfulPicture(const Picture& p1, const Picture& p2);

	~ColorfulPicture() {}

	bool setPixel(const Pixel& p, const Position& pos) override;
};

#endif // !_COLORFUL_PICTURE_H_

