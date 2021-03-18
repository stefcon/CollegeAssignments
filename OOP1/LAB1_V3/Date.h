#ifndef _DATE_H_
#define _DATE_H_

#include <iostream>
#include <string>

class Date {
	int day, month, year;

public:
	Date(int d = 30, int m = 11, int y = 2019) : day(d), month(m), year(y) {}

	int getDay() const { return day; }

	int getMonth() const { return month; }

	int getYear() const { return year; }

	int operator[](std::string ind);

	friend bool operator>(const Date&, const Date&);

	friend bool operator<(const Date&, const Date&);

	friend std::ostream& operator<<(std::ostream& os, const Date& d);


};
#endif // !_DATE_H_

