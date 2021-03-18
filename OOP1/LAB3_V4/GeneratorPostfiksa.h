#ifndef _generator_postfiksa_h_
#define _generator_postfiksa_h_


#include "Operand.h"
#include "Sabiranje.h"
#include "Mnozenje.h"
#include "Leva_zagrada.h"
#include "Desna_zagrada.h"
#include "Izraz.h"

class GPostfiks : public exception {
public:
	GPostfiks() : exception("*** Nije moguce generisati ispravan izraz u postfiksnom obliku! ***") {}
};

class GeneratorPostfiksa {

	GeneratorPostfiksa() {};

public:
	static GeneratorPostfiksa& dohvObjekat() {
		static GeneratorPostfiksa objekat;
		return objekat;
	}

	GeneratorPostfiksa(const GeneratorPostfiksa&) = delete;
	GeneratorPostfiksa& operator=(const GeneratorPostfiksa&) = delete;

	Izraz operator()(Izraz infiks);
};


#endif // !_generator_postfiksa_h_

