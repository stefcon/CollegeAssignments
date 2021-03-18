#include "Sastojak.h"

Nutritivna_vrednost Sastojak::dohvNutrVr() const {
	return Nutritivna_vrednost(namirnica.dohvNutrVr().dohvUh() * kolicina / 100,
		namirnica.dohvNutrVr().dohvMasti() * kolicina / 100,
		namirnica.dohvNutrVr().dohvProteini() * kolicina / 100);
}

double Sastojak::dohvKalorije() const {
	return (namirnica.dohvNutrVr().brojKalorija() * kolicina) / 100;
}
