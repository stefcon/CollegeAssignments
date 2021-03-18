#include "Datum.h"

int Datum::izbrojPrestupne() const {
	int godine = god;
	if (mes <= 2) {
		godine--;
	}
	return godine / 4 + godine / 400 - godine / 100;
}

Datum::Datum(int d, int m, int g) : dan(d), mes(m), god(g) {
	char daniMeseca[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (god % 4 == 0 && god % 100 != 0 || god % 400 == 0) daniMeseca[1]++;
	if (dan < 0 || mes < 0 || god < 0 || mes > 12 || dan > daniMeseca[mes - 1]) throw GDatum();
}

int operator-(const Datum& d1, const Datum& d2)
{
	int br1, br2;
	const char daniMeseca[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	br1 = d1.god * 365 + d1.dan;
	for (int i = 0; i < d1.mes - 1; ++i) {
		br1 += daniMeseca[i];
	}
	br1 += d1.izbrojPrestupne();

	br2 = d2.god * 365 + d2.dan;
	for (int i = 0; i < d2.mes - 1; ++i) {
		br2 += daniMeseca[i];
	}
	br2 += d2.izbrojPrestupne();

	return abs(br1 - br2);
}
