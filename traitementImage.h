#ifndef TRAITEMENTIMAGE_H
#define TRAITEMENTIMAGE_H

#define tailleFenetreRLSA 10

typedef struct _Rectangle {
	int sommetunX;
	int sommetunY;
	int sommetdeuxX;
	int sommetdeuxY;
} Rectangle;
int maximum(int A, int B);
int minimum(int A, int B);
DonneesImageGris *transformeeHough(DonneesImageGris *image, double gamma);
DonneesImageGris *filtreMedianRelache(DonneesImageGris *image);
DonneesImageGris *binarisationOtsu(DonneesImageGris *image);
DonneesImageGris* detourageImage(Rectangle rect, DonneesImageGris* imageInitiale);
DonneesImageGris* copiePartieImage(Rectangle rect, DonneesImageGris* imageInitiale, DonneesImageGris* imageRetour);
DonneesImageGris* rechercheZoneDeTexte (DonneesImageGris *donnee);
DonneesImageGris *RLSA_H(DonneesImageGris *image, int maxGapSize, bool processGapsWithImageBorders);//dans rlsa.c
DonneesImageGris *RLSA_V(DonneesImageGris *image, int maxGapSize, bool processGapsWithImageBorders);//idem
DonneesImageGris *RLSA_I(DonneesImageGris *image, int maxGapSize, bool processGapsWithImageBorders);//idem
#endif /* TRAITEMENTIMAGE_H */