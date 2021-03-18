#ifndef _PUBLICATION_H_
#define _PUBLICATION_H_

#include "Notice.h"


class Publication : public Notice {
public:

	Publication(User* u, string txt);

private:
	string text;

	void write(ostream& os) const override;
};
#endif // !_PUBLICATION_H_

