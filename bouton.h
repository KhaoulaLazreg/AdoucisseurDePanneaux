#ifndef BOUTON_H
#define BOUTON_H
#define NB_BOUTONS 4
#include <stdbool.h>

typedef struct _bouton
{
	char *nom;
	int x;
	int y;
	int l;
	int h;
	bool ini;
}Bouton;

void BoutonAffichage(Bouton* bouton,int position,int police,int epaisseur) ;
Bouton* declarationBouton(int nbBoutons);

void inibouton(Bouton* bouton,int x,int y,int l,int h,char* nom);
void nettoieBouton(Bouton *bouton);
void tracebouton(Bouton bouton, char *nom) ;
int clic(Bouton *bouton,int x, int y,int nbBoutons);



#endif 
