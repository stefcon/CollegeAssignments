#include "Aranzman.h"

Aranzman& Aranzman::dodeliSmestaj(Smestaj& smestaj) {
	if (smestaj.dohvDest().dohvNaziv() != destinacija.dohvNaziv() ||
		smestaj.dohvDest().dohvOpis() != destinacija.dohvOpis() ||
		smestaj.dohvDest().dohvProsek() != destinacija.dohvProsek()) {
		throw GSmestajLokacija();
	}
	this->smestaj = &smestaj;
}

Aranzman& Aranzman::dodeliPrevoz(Prevoz& prevoz) {
	if (prevoz.dohvDest().dohvNaziv() != destinacija.dohvNaziv() ||
		prevoz.dohvDest().dohvOpis() != destinacija.dohvOpis() ||
		prevoz.dohvDest().dohvProsek() != destinacija.dohvProsek()) {
		throw GPrevozLokacija();
	}
	this->prevoz = &prevoz;
}
