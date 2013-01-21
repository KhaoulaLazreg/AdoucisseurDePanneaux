#ifndef TRAITEMENTIMAGE_H
#define TRAITEMENTIMAGE_H

#define tailleFenetreRLSA 10

typedef struct _Rectangle {
	int sommetunX;
	int sommetunY;
	int sommetdeuxX;
	int sommetdeuxY;
} Rectangle;

DonneesImageGris *filtreMedianRelache(DonneesImageGris *image);
DonneesImageGris *binarisationOtsu(DonneesImageGris *image);
DonneesImageGris* detourageImage(Rectangle rect, DonneesImageGris* imageInitiale);
DonneesImageGris* copiePartieImage(Rectangle rect, DonneesImageGris* imageInitiale, DonneesImageGris* imageRetour);
DonneesImageGris* rechercheZoneDeTexte (DonneesImageGris *donnee);

#endif /* TRAITEMENTIMAGE_H */