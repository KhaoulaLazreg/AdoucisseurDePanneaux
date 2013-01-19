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

bool ecrisBMPGris_Dans(DonneesImageGris *donneesImage, char *nom);
void histo(char * nom);
void histoTotal(char* nom);


void sobelIntensite(DonneesImageGris *donee,DonneesImageGris *resultat);
void sobelDirection(DonneesImageGris *donee,DonneesImageGris *resultat);
void intensiteetdirectiongradient(int largeur, int hauteur,
        unsigned char **tabgris, float **direction, unsigned char **intensite) ;
char **initSobelX();
char **initSobelY();
char **inittableau2dchar(int x, int y);
char **filtremasquecarre(unsigned char **tableauinit, int largeur, int hauteur,
        char **masque, int tailleMasque);


#endif
