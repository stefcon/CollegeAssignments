#include "Air_Conditioning.h"

Air_Conditioning::Air_Conditioning(std::string name, int sq_m) : Device(name) {
	allowed_glitches = 2;
	m2 = sq_m;
}

void Air_Conditioning::setWarranty(Date s) {
	Date e(s.getDay(), s.getMonth(), s.getYear() + 5);
	warranty = new Warranty(s, e);
}

bool Air_Conditioning::operator==(const Air_Conditioning& dev2) {
	return Device::operator==(dev2) && this->m2 == dev2.m2;
}

bool Air_Conditioning::operator!=(const Air_Conditioning& dev2) {
	return Device::operator!=(dev2) && !(*this == dev2);
}

void Air_Conditioning::write(std::ostream& os) const {
	Device::write(os);
	os << "#klima#-" << m2;
}



