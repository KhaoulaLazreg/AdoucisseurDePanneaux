#ifndef BMPGRIS_H
#define BMPGRIS_H

#include "BmpLib.h"

typedef struct
{
	int largeurImage;
	int hauteurImage;
	unsigned char **donneesGris;
} DonneesImageGris;

void libereDonneesImageGris(DonneesImageGris **structure);

DonneesImageGris *lisBMPGris(char *nom);
DonneesImageGris *texteG(DonneesImageGris *resultat);
DonneesImageGris *texteH(DonneesImageGris *resultat);
DonneesImageGris *texteJ(DonneesImageGris *resultat);
bool ecrisBMPGris_Dans(DonneesImageGris *donneesImage, char *nom);
void histo(char * nom);
void negatif(DonneesImageGris *im);
void applicationLaplacien(DonneesImageGris *donnee,DonneesImageGris *resultat);
void applicationContraste(DonneesImageGris *donnee,DonneesImageGris *resultat);
void sobelIntensite(DonneesImageGris *donee,DonneesImageGris *resultat);
void sobelDirection(DonneesImageGris *donee,DonneesImageGris *resultat);
void intensiteetdirectiongradient(int largeur, int hauteur,
        unsigned char **tabgris, float **direction, unsigned char **intensite) ;
char **initSobelX();
char **initSobelY();
char **initLaplacien() ;
char **initContraste();
char **inittableau2dchar(int x, int y);
char **filtremasquecarre(unsigned char **tableauinit, int largeur, int hauteur,
        char **masque, int tailleMasque);


#endif
