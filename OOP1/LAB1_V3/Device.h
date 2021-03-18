#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "Warranty.h"

class Device {
protected:
	static int id_init;
	int id = ++id_init, allowed_glitches = 0;

	std::string manufacturer;
	Warranty* warranty = nullptr;

	virtual void write(std::ostream& os) const;
public:
	Device(std::string name) : manufacturer(name) {}

	virtual ~Device() {
		delete warranty;
	}

	Device(const Device&) = delete;
	Device& operator=(const Device&) = delete;

	virtual void setWarranty(Date s) = 0;

	Warranty& getWarranty() { return *warranty; }

	bool operator==(const Device&);

	bool operator!=(const Device&);

	friend std::ostream& operator<<(std::ostream& os, const Device& dev);
};

#endif // !_DEVICE_H_

