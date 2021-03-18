#include "ColorfulPicture.h"

ColorfulPicture::ColorfulPicture(int h, int w, const Time& t) : Picture(h, w ,t) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 255);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; j++) {
			while (true) {
				char r, g, b;
				r = distr(gen);
				g = distr(gen);
				b = distr(gen);
				Pixel p(r, g, b);
				if (setPixel(p, { i,j })) break;
			}
		}
	}
}

ColorfulPicture& ColorfulPicture::operator=(const ColorfulPicture& p) {
	if (this != &p) {
		clear();
		copy(p);
	}
	return *this;
}

ColorfulPicture& ColorfulPicture::operator=(ColorfulPicture&& p) {
	if (this != &p) {
		clear();
		move(p);
	}
	return *this;
}

ColorfulPicture::ColorfulPicture(const Picture& p1, const Picture& p2)
	: Picture(p1.getHeight(), p1.getWidth(), (p1.getTime() > p2.getTime()) ? p1.getTime() : p2.getTime()) 
{
	if (p1.getHeight() != p2.getHeight() || p1.getWidth() != p2.getWidth()) exit(1);

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			grid[i][j] = p1[{i, j}] + p2[{i, j}];
		}
	}
}

bool ColorfulPicture::setPixel(const Pixel& p, const Position& pos) {
	int i = pos.getRow(), j = pos.getCol();
	if (i > 0) {
		if (grid[i - 1][j] == p) return false;
	}
	if (j > 0) {
		if (grid[i][j - 1] == p) return false;
	}
	if (i < height - 1) {
		if (grid[i + 1][j] == p) return false;
	}
	if (j < width - 1) {
		if (grid[i][j + 1] == p) return false;
	}

	return Picture::setPixel(p, pos);
}
