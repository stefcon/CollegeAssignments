#ifndef _GALLERY_H_
#define _GALLERY_H_

#include "Picture.h"

class Gallery {
public:
	Gallery() : head(nullptr), tail(nullptr), num(0) {}

	Gallery(const Gallery& g);

	Gallery(Gallery&& g);

	~Gallery();

	Gallery& operator=(const Gallery& g);

	Gallery& operator=(Gallery&& g);

	int getNum() const { return num; }

	int getPictureSize() const;

	virtual Gallery& operator+=(const Picture& p);

	Picture& operator[](int ind);

	friend std::ostream& operator<<(std::ostream& os, const Gallery& gal);

protected:
	struct Elem {
		Picture* picture;
		Elem* next;
		Elem(Picture * p, Elem* nxt = nullptr) : picture(p), next(nxt) {};
		~Elem() { delete picture; }
	};
	
	Elem* head, * tail;
	int num;

	void copy(const Gallery& g);
	void move(Gallery& g);
	void clear();
};

#endif // !_GALLERY_H_

