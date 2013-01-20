typedef struct _Rectangle {
	int sommetunX;
	int sommetunY;
	int sommetdeuxX;
	int sommetdeuxY;
} Rectangle;

DonneesImageGris *filtreMedianRelache(DonneesImageGris *image);
DonneesImageGris *binarisationOtsu(DonneesImageGris *image);