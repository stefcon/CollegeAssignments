#ifndef _AIR_CONDITIONING_H
#define _AIR_CONDITIONING_H

#include "Device.h"

class Air_Conditioning : public Device {
public:
	Air_Conditioning(std::string name, int sq_m);

	void setWarranty(Date s) override;

	bool operator==(const Air_Conditioning& dev2);

	bool operator!=(const Air_Conditioning& dev2);
protected:

	void write(std::ostream& os) const override;

private:
	int m2;
};
#endif // !_AIR_CONDITIONING_H

