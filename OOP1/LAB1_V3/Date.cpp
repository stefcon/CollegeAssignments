#include "Date.h"

int Date::operator[](std::string ind) {
	if (ind == "dan") {
		return day;
	}
	else if (ind == "mesec") {
		return month;
	}
	else if (ind == "godina") {
		return year;
	}
	else {
		return -1;
	}
}

bool operator>(const Date& d1, const Date& d2) {
	if (d1.year > d2.year || d1.year == d2.year && d1.month > d2.month || d1.year == d2.year && d1.month > d2.month && d1.day > d2.day)
		return true;
	else
		return false;
}

bool operator<(const Date& d1, const Date& d2)
{
	if (d1.year < d2.year || d1.year == d2.year && d1.month < d2.month || d1.year == d2.year && d1.month < d2.month && d1.day < d2.day)
		return true;
	else
		return false;
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
	return os << d.day << '.' << d.month << '.' << d.year << '.';
}
