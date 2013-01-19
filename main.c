#include <stdlib.h> // Pour pouvoir utiliser exit
#include <stdio.h> // Pour pouvoir utiliser printf
#include <math.h> // Pour pouvoir utiliser sin et cos
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "ESLib.h" // Pour utiliser valeurAleatoire
#include <string.h>//pour ini bouton: strdup
#include "BmpGris.h"
#include "bouton.h"
#include <stdbool.h>
#include <time.h>

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 1121
#define HauteurFenetre 864
#define NB_BOUTONS 4
#define ValeurLimite 200



void gestionEvenement(EvenementGfx evenement);
void scanfgraph(char caractereClavier);
	static char *bufferSaisie = NULL;
int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	
	prepareFenetreGraphique("Histogramme", LargeurFenetre, HauteurFenetre);

	lanceBoucleEvenements();
	
	return 0;
}

void gestionEvenement(EvenementGfx evenement)
{


	static Bouton *bouton;

	static char* nom;
	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	static DonneesImageRGB *image = NULL; // L'image a afficher au centre de l'ecran
	static int numBoutonClique=-1;
	static bool imageGriseEcrite;
	static bool saisie=false;
	static DonneesImageGris *donneesImage=NULL;
	static DonneesImageGris *resultat=NULL;
	
	int i;
	switch (evenement)
	{
		case Initialisation:
			// On initialise toutes les données


bufferSaisie = (char*) malloc(ValeurLimite*sizeof(char));
    for(i = 0; i < ValeurLimite; i++)
    	bufferSaisie[i] = '\0';





		nom=(char*)malloc(600);
			nom="panneau.bmp";
			image = lisBMPRGB(nom);
			

			bouton=declarationBouton(2);
			imageGriseEcrite=false;
			
			demandeAnimation_ips(10);
			break;
			
		case Affichage:
			
			effaceFenetre (255, 255, 255);
			epaisseurDeTrait(3);
couleurCourante(40,140,40);
			afficheChaine(bufferSaisie, 25, 38, 134);	
donneesImage=lisBMPGris(nom);
resultat=lisBMPGris(nom);
sobelDirection(donneesImage,resultat);
if(ecrisBMPGris_Dans(resultat,"imageGris.bmp"))
{			
			image = lisBMPRGB("imageGris.bmp");
			
			 imageGriseEcrite=true;
}
				//ecrisImage(0,30,Lplateau,Hplateau+30, image->donneesRGB);

ecrisImage((largeurFenetre()-donneesImage->largeurImage)/2,(hauteurFenetre()-donneesImage->hauteurImage)/2,donneesImage->largeurImage,donneesImage->hauteurImage, image->donneesRGB);
			BoutonAffichage( bouton,0,25,3); 
			BoutonAffichage( bouton,1,25,3); 
		if(imageGriseEcrite)
			histo("imageGris.bmp");
			//histoTotal("./plateaujeu.bmp");
		imageGriseEcrite=false;
		libereDonneesImageGris(&donneesImage);
		libereDonneesImageRGB(&image);
			break;
			
		case Clavier:

		
			if(!saisie)
			switch (caractereClavier())
			{
				 
				case 'Q': /* Pour sortir quelque peu proprement du programme */
				case 'q':
					libereDonneesImageRGB(&image);
					exit(0);
					break;

				case 'P':
				case 'p':
					pleinEcran = !pleinEcran; // Changement de mode plein ecran
					if (pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;

			}
			else
			{scanfgraph(caractereClavier());
                 rafraichisFenetre();}
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye)
			{
				
			}
			else if (etatBoutonSouris() == GaucheRelache)
			{
				
				//	entreeCoordonneesSouris(clic(caseB,abscisseSouris(),ordonneeSouris(),NB_CASES),bouton); //TODO

				numBoutonClique=clic(bouton,abscisseSouris(),ordonneeSouris(),2);
				if(numBoutonClique==0){
					saisie=true;
					printf("bouton cliqué 0");
					 
					 
				}
				if(numBoutonClique==1){
printf("bouton cliqué 1");
					saisie=false;
					if(bufferSaisie!=NULL)
					 nom=bufferSaisie;
					bufferSaisie="";
					 
				}

				
			}
			break;
			if (etatBoutonSouris() == DroiteAppuye)
			{
			}
			break;
		
		case Souris: // Si la souris est deplacee
			break;
		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
			// Donc le systeme nous en informe

			break;
	}
}


void scanfgraph(char caractereClavier)
{
        //Concept : Court-circuiter les raccourcis clavier pour récupérer le caractère
        if (caractereClavier != 13 && bufferSaisie != NULL && strlen(bufferSaisie) < ValeurLimite-2)
        {
                // Si l'utilisateur n'appuit pas sur supprimer
                if(caractereClavier != 8)
                {
                        bufferSaisie[strlen(bufferSaisie)] = caractereClavier;
                        bufferSaisie[strlen(bufferSaisie)+1] = '\0';
                }
                // Si l'utilisateur appuit sur supprimer
                else
                        bufferSaisie[strlen(bufferSaisie)-1] = '\0';
        }
}
              



