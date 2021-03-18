#include "ColorfulPicture.h"
#include "ShadesOfGrey.h"
#include "SortedGallery.h"

using namespace std;

int main() {
	Picture obicna(2, 2, { 3, 3, 3 });
	BlackNWhite crno_bela(2, 2, { 1, 1,1 });
	ColorfulPicture sarena(2, 2, { 2, 2,2 });
	ShadesOfGrey nijanse_sive(2, 2, { 5, 5, 5 });

	SortedGallery galerija;

	galerija += obicna;
	galerija += crno_bela;
	galerija += sarena;
	galerija += nijanse_sive;

	cout << galerija << endl;

	crno_bela.setPixel({ 128, 127, 127 }, { 0,0 });

	cout << crno_bela << endl;

	ColorfulPicture sarena2(sarena, crno_bela);

	cout << sarena2 << endl;

	return 0;
}