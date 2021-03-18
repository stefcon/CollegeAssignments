#include "Air_Conditioning.h"

using namespace std;

int main() {
	Warranty garancija({ 1, 1, 2018 }, { 1,1, 2020 });
	Glitch g1("Ode karbuarator", { 2,2,2019 }), g2("Crce plivajuci zamajac", { 3, 12, 2019 });

	garancija.addGlitch(g1);

	cout << garancija << endl;
	cout << garancija.addGlitch(g2) << endl;

	garancija.getLastGlitch().setStatus(true);
	garancija.addGlitch(g2);

	cout << garancija << endl;

	Air_Conditioning klima1("Tesla", 30);
	klima1.setWarranty({ 1,1,2019 });
	cout << klima1.getWarranty() << endl;
	cout << klima1 << endl;


	


	return 0;
}