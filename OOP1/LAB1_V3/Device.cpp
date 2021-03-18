#include "Device.h"

int Device::id_init = 0;

bool Device::operator==(const Device& dev2) {
	if (this->manufacturer == dev2.manufacturer) {
		return true;
	}
	else {
		return false;
	}
}

bool Device::operator!=(const Device& dev2)
{
	return !(*this == dev2);
}

std::ostream& operator<<(std::ostream& os, const Device& dev) {
	dev.write(os);
	return os;
}

void Device::write(std::ostream& os) const {
	os << manufacturer << ":" << id;
}

