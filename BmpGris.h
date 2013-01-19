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

#endif
