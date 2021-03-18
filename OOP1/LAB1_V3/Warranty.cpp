#include "Warranty.h"

void Warranty::AddEl(Glitch g) {
	Glitch** tmp = new Glitch * [size + 1];
	for (int i = 0; i < size; ++i)
		tmp[i] = glitches[i];
	delete glitches;
	tmp[size] = new Glitch(g);
	size++;
	glitches = tmp;
}

void Warranty::copy(const Warranty& w) {
	if (w.glitches) {
		Glitch** glitches = new Glitch * [size = w.size];
		for (int i = 0; i < size; ++i) {
			glitches[i] = w.glitches[i];
		}
	}
	size = w.size;
	start = w.start;
	end = w.end;
}

void Warranty::move(Warranty& w) {
	glitches = w.glitches;
	w.glitches = nullptr;
	size = w.size;
	start = w.start;
	end = w.end;
}

void Warranty::clear() {
	for (int i = 0; i < size; ++i) {
		delete glitches[i];
	}
	delete glitches;
	glitches = nullptr;

}

Warranty::Warranty(const Warranty& w) {
	copy(w);
}

Warranty::Warranty(Warranty&& w) {
	move(w);
}

Warranty& Warranty::operator=(const Warranty& w) {
	if (this != &w) {
		clear();
		copy(w);
	}
	return *this;
}

Warranty& Warranty::operator=(Warranty&& w) {
	if (this != &w) {
		clear();
		move(w);
	}
	return *this;
}

Warranty::~Warranty() {
	clear();
}

bool Warranty::addGlitch(Glitch g) {
	if (size == 0 || glitches[size - 1]->isFixed() && g.getDate() < end && g.getDate() > start) {
		AddEl(g);
		return true;
	}
	else
		return false;
}

Glitch& Warranty::getLastGlitch() {
	if (size == 0) exit(1);
	return *glitches[size - 1];
}

std::ostream& operator<<(std::ostream& os, const Warranty& w) {
	return os << w.start << '-' << w.end << '-' << "broj kvarova:" << w.size;
}
