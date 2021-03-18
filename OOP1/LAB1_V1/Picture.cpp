#include "Picture.h"

Picture::Picture(int h, int w, const Time& t) {
	height = h;
	width = w;
	time = t;
	grid = new Pixel * [height];
	for (int i = 0; i < height; i++)
		grid[i] = new Pixel[width];
}

Picture::Picture(const Picture& p) {
	copy(p);
}

Picture::Picture(Picture&& p) {
	move(p);
}

Picture::~Picture() {
	clear();
}

Picture& Picture::operator=(const Picture& p) {
	if (this != &p) {
		clear();
		copy(p);
	}
	return *this;
}

Picture& Picture::operator=(Picture&& p) {
	if (this != &p) {
		clear();
		move(p);
	}
	return *this;
}

int Picture::getSize() const
{
	return height * width * p_size;
}

const Pixel& Picture::operator[](Position pos) const {
	int row = pos.getRow(), col = pos.getCol();
	return grid[row][col];
}

bool Picture::setPixel(const Pixel& p, const Position& pos) {
	const_cast<Pixel&>((*this)[pos]) = p;
	return true;
}

void Picture::copy(const Picture& p) {
	grid = new Pixel * [height = p.height];
	for (int i = 0; i < height; ++i) {
		grid[i] = new Pixel[width = p.width];
		for (int j = 0; j < width; ++j)
			grid[i][j] = p.grid[i][j];
	}

	time = p.time;
}

void Picture::move(Picture& p) {
	grid = p.grid;
	p.grid = nullptr;
	height = p.height;
	width = p.width;
	time = p.time;
}

void Picture::clear() {
	if (!grid) return;
	for (int i = 0; i < height; ++i) {
		delete[] grid[i];
	}
	delete[] grid;
	grid = nullptr;
}

ostream& operator<<(ostream& os, const Picture& p) {
	cout << "Vreme nastanka: " << p.time << ", Velicina slike: " << p.getSize() << endl;
	for (int i = 0; i < p.height; ++i) {
		for (int j = 0; j < p.width; ++j) {
			os << p.grid[i][j];
		}
		cout << endl;
	}

	return os;
}
