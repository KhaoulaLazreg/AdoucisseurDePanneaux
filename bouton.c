#include <stdio.h>
#include <stdlib.h>
#include"bouton.h" 
//#include "transparence.h"
#include"GfxLib.h"
#include <string.h>




//Affiche le "nom" d'un bouton
void BoutonAffichage(Bouton* bouton,int position,int police,int epaisseur) 
{
	epaisseurDeTrait(epaisseur);
	couleurCourante(0,0,0);
	int taille=tailleChaine((bouton[position]).nom, police);
	if((bouton[position]).nom!=NULL)
		afficheChaine((bouton[position]).nom, police, (bouton[position]).x+((bouton[position]).l-taille)/2, (bouton[position]).y);
}



// Declare tous les boutons
Bouton* declarationBouton(int nbBoutons)
{
	Bouton* bouton=(Bouton*)malloc(nbBoutons*sizeof(Bouton));
	if(bouton!=NULL)
	{
		inibouton(&bouton[0],421,22,210,30,"Charger"); 
		inibouton(&bouton[1],200,22,210,30,"Ouvrir");

	}
	return bouton;
}

// Initialise un bouton
void inibouton(Bouton* bouton,int x,int y,int l,int h,char* nom)
{
	
	
		bouton->ini=true;
		bouton->l=l;
		bouton->h=h;
		bouton->x=x;
		bouton->y=y;
		bouton->nom=(char*)malloc(10*sizeof(char));
		bouton->nom=nom;

}


//Libère les boutons
void nettoieBouton(Bouton *bouton)
{
	if(bouton!=NULL)
		free(bouton);
}


//Permet d'afficher le nom des boutons
void tracebouton(Bouton bouton, char *nom) 
{
	couleurCourante(0, 0, 0);
	epaisseurDeTrait(2);
	afficheChaine(bouton.nom, bouton.h, bouton.x, bouton.y);
}


//Renvoie le numero de la case (entre 1 et 63) en fonction de la position du clic souris
int clic(Bouton *bouton,int x, int y,int nbBoutons)
{
	int i;
	for(i=0;i<nbBoutons;i++)
	{
		if((bouton[i]).ini==true)
		{
			if((x>=((bouton[i]).x ))&&(x<=((bouton[i]).x  + (bouton[i]).l))) //l'abscisse du clic souris correspond à l'abscisse de la case
			{
				if((y>=((bouton[i]).y ))&&(y<=((bouton[i]).y  + (bouton[i]).h)))//l'ordonnée du clic souris correspond à l'ordonnée de la case
					return i;
			}
		}
	}
	return -1;
}


