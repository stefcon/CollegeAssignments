#include "GeneratorPostfiksa.h"

Izraz GeneratorPostfiksa::operator()(Izraz infiks) {
	Izraz stek;
	int rank = 0;
	Izraz postfiks;
	Element* sledeci = infiks.vidiPrvi();
	bool za_redom_operand = false;

	while (infiks.dohvBrojPod()) {
		if (sledeci->dohvOzn() == 'D') {
			//Element je operand
			if (za_redom_operand) throw GPostfiks();
			postfiks += sledeci;
			rank++;
			za_redom_operand = true;
		}
		else {
			za_redom_operand = false;
			if (sledeci->dohvOzn() == '(') {
				//Element je otvorena zagrada - stavi na stek
				stek += sledeci;

			}
			else if (sledeci->dohvOzn() == ')') {
				//Skidaj sa steka sve dok ne naidjes na '(' ili dok se ne isprazni
				//Usput se proverava na pravilnost izraza i elementi se ubacuju u postfiks
				bool nadjena_otvorena = false;
				while (stek.dohvBrojPod()) {
					Element* x = -stek;
					if (x->dohvOzn() == '(') {
						delete x;
						nadjena_otvorena = true;
						break;
					}
					postfiks += x;

					//Provera greske
					if (x->dohvOzn() == 'O') rank--;
					if (rank < 1) throw GPostfiks();
					delete x;

				}
				if (!nadjena_otvorena) throw GPostfiks();
			}
			else {
				//Ubacujemo operator na odgovarajuce mesto na steku
				while (stek.dohvBrojPod()) {
					Element* x = stek.vidiPosl();

					if (x->dohvOzn() == '(' || x->dohvOzn() == 'O'
						&& *(dynamic_cast<BOperator*>(x)) < *(dynamic_cast<BOperator*>(sledeci))) {
						break;
					}

					-stek;
					postfiks += x;

					if (x->dohvOzn() == 'O') rank--;
					if (rank < 1) throw GPostfiks();
					delete x;
				}
				stek += sledeci;
			}
		}
		delete sledeci;
		sledeci = *infiks;
		sledeci = infiks.vidiPrvi();
	}

	while (stek.dohvBrojPod()) {
		Element* x = -stek;
		postfiks += x;
		if (x->dohvOzn() == 'O') rank--;
		if (x->dohvOzn() == '(') throw GPostfiks();
		delete x;
	}

	if (rank != 1) throw GPostfiks();

	return postfiks;
}
