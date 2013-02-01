#include <stdlib.h>
#include <stdio.h>
#include "BmpGris.h"
#include "GfxLib.h"
#include "traitementImage.h"
#include "math.h"


DonneesImageGris *texteG(DonneesImageGris *resultat){
   
resultat =RLSA_I(resultat, resultat->largeurImage*0.06, false);
 

return  resultat;
}

DonneesImageGris *texteH(DonneesImageGris *resultat){
    negatif(resultat);
DonneesImageGris* un =RLSA_I(resultat, resultat->largeurImage*0.06, false);
 
DonneesImageGris* deux= RLSA_I(resultat, resultat->largeurImage*0.06, false);

int tempo=0;
 int i,j;

    for(i=0;i< resultat->largeurImage;i++)
        for(j=0;j< resultat->hauteurImage;j++){
            resultat->donneesGris[i][j]=255;
            if(un->donneesGris[i][j]==0||deux->donneesGris[i][j]==0)
                tempo=0;
            else{
          tempo=un->donneesGris[i][j]+deux->donneesGris[i][j];
            if(tempo>255)
                tempo=255;
        }
                resultat->donneesGris[i][j]=tempo;;
            

}
negatif(resultat);
resultat=RLSA_H(resultat, (int)(resultat->largeurImage*0.06), false);
negatif(resultat);
//resultat=transformeeHough(resultat,0.5);

return  resultat;
}
DonneesImageGris *texteJ(DonneesImageGris *resultat){
    negatif(resultat);
DonneesImageGris* un =RLSA_I(resultat, resultat->largeurImage*0.06, false);
 
DonneesImageGris* deux= RLSA_I(resultat, resultat->largeurImage*0.06, false);

int tempo=0;
 int i,j;

    for(i=0;i< resultat->largeurImage;i++)
        for(j=0;j< resultat->hauteurImage;j++){
            resultat->donneesGris[i][j]=255;
            if(un->donneesGris[i][j]==0||deux->donneesGris[i][j]==0)
                tempo=0;
            else{
          tempo=un->donneesGris[i][j]+deux->donneesGris[i][j];
            if(tempo>255)
                tempo=255;
        }
                resultat->donneesGris[i][j]=tempo;;
            

}

//resultat=transformeeHough(resultat,0.5);

return  resultat;
}



void negatif(DonneesImageGris *im) //sur image binaire
{
    int i,j;

    for(i=0;i< im->largeurImage;i++)
        for(j=0;j< im->hauteurImage;j++){
            if (im->donneesGris[i][j]==0)
            {
                im->donneesGris[i][j]=255;
            }
            else 
                im->donneesGris[i][j]=0;
}
}



void libereDonneesImageGris(DonneesImageGris **structure)
{
    if (structure != NULL)
    {
	if (*structure != NULL)
	{
	    free((*structure)->donneesGris);
	    free(*structure);
	}
	
	*structure = NULL;
    }
}

DonneesImageGris *lisBMPGris(char *nom)
{
    DonneesImageRGB *donneesRGB = lisBMPRGB(nom);
    int i,j;
    DonneesImageGris *donneesImage = (DonneesImageGris*)calloc(1, sizeof(DonneesImageGris));
    donneesImage->largeurImage = donneesRGB->largeurImage;
    donneesImage->hauteurImage = donneesRGB->hauteurImage;
    
    donneesImage->donneesGris = malloc(donneesRGB->largeurImage * sizeof(*donneesImage->donneesGris));
    
    for(i = 0; i < donneesImage->largeurImage; i++)
	donneesImage->donneesGris[i] = malloc(donneesImage->hauteurImage * sizeof(**donneesImage->donneesGris));

    
    for( i = 0; i < donneesImage->hauteurImage; i++)
    for( j = 0; j < donneesImage->largeurImage; j++)
	donneesImage->donneesGris[j][i] = 0.2126 * donneesRGB->donneesRGB[(donneesImage->largeurImage*i+j)*3]
					+ 0.7152 * donneesRGB->donneesRGB[(donneesImage->largeurImage*i+j)*3+1]
					+ 0.0722 * donneesRGB->donneesRGB[(donneesImage->largeurImage*i+j)*3+2];

    libereDonneesImageRGB(&donneesRGB);
    
    return donneesImage;
}

bool ecrisBMPGris_Dans(DonneesImageGris *donneesImage, char *nom)
{
    int l=donneesImage->largeurImage;
    int h=donneesImage->hauteurImage;
    DonneesImageRGB *donneesRGB = (DonneesImageRGB*)calloc(1, sizeof(DonneesImageRGB));
    donneesRGB->largeurImage = l;
    donneesRGB->hauteurImage = h;
    donneesRGB->donneesRGB = (unsigned char *)malloc((unsigned int)l*(unsigned int)h*3);
    int i,j;

    for( i = 0; i < h; i++)
    for( j = 0; j < l; j++)
    {
	donneesRGB->donneesRGB[(l*i+j)*3] = donneesImage->donneesGris[j][i];
	donneesRGB->donneesRGB[(l*i+j)*3+1] = donneesImage->donneesGris[j][i];
	donneesRGB->donneesRGB[(l*i+j)*3+2] = donneesImage->donneesGris[j][i];
    

    }
    
    ecrisBMPRGB_Dans(donneesRGB, nom);
    
    libereDonneesImageRGB(&donneesRGB);
    
    return true;
}

void histo(char * nom){

 DonneesImageRGB *donneesRGB = lisBMPRGB(nom);
     int i,j,max=1;
    float hauteurHisto=800;
    unsigned int gris[256];
    for ( i = 0; i < 256; i++)
    {
       gris[i]=0;
    }
  int l=donneesRGB->largeurImage;
    int h=donneesRGB->hauteurImage;
   for( i = 0; i < l; i++)
    for( j = 0; j < h; j++){
   gris[donneesRGB->donneesRGB[(l*i+j)*3]]+=1;
}
for ( i = 0; i < 256; i++)
{
    if(max<gris[i])
    max=gris[i];
}


epaisseurDeTrait(3);
couleurCourante(40,140,40);
for ( i = 0; i < 255; ++i)
{
    ligne((float)(25+4*i), (float)(50), (float)(25+4*i), (float)50+hauteurHisto*( (float) gris[i] /(float)max   )         );
}


  libereDonneesImageRGB(&donneesRGB); 
}

void sobelDirection(DonneesImageGris *donnee,DonneesImageGris *resultat){
    
    int i, j,l=donnee->largeurImage,h=donnee->hauteurImage;
    char **gradx;
    char **grady;
    char **masque;
    float temp=0;
    donnee=binarisationOtsu(donnee);

    masque = initSobelX();
    gradx = filtremasquecarre(donnee->donneesGris, l, h, masque, 3);
    masque = initSobelY();
    grady = filtremasquecarre(donnee->donneesGris, l, h, masque, 3);
    char t;
    for (i = 3; i < h - 3; i++) {
        for (j = 3; j < l- 3; j++) {

             temp=atan((double) grady[j][i] / (double) gradx[j][i]);
             if(temp<0)
             {
               t= (char)((1.57+temp)*81.48) ;//128/(pi/2)
             }
             else{
                t=127+ (char)(  temp/(1.57)*128 );
             }
           resultat->donneesGris[j][i] =t;
        }
    }
}

void applicationLaplacien(DonneesImageGris *donnee,DonneesImageGris *resultat){
    donnee=binarisationOtsu(donnee);
    int i, j;
    char **laplacien;
    
    char **masque;
    
     masque = initSobelX();
   laplacien= filtremasquecarre(donnee->donneesGris, donnee->largeurImage, donnee->hauteurImage, masque, 3);
     for (i = 3; i < donnee->hauteurImage - 3; i++) {
        for (j = 3; j < donnee->largeurImage- 3; j++) {
            resultat->donneesGris[j][i] = laplacien[j][i]; //valeur dans le masque
        }
    }
}
void applicationContraste(DonneesImageGris *donnee,DonneesImageGris *resultat){
    
    int i, j;
    char **contraste;
    
    char **masque;
    
     masque = initSobelX();
   contraste= filtremasquecarre(donnee->donneesGris, donnee->largeurImage, donnee->hauteurImage, masque, 3);
     for (i = 3; i < donnee->hauteurImage - 3; i++) {
        for (j = 3; j < donnee->largeurImage- 3; j++) {
            resultat->donneesGris[j][i] = contraste[j][i]; //valeur dans le masque
        }
    }
}
void sobelIntensite(DonneesImageGris *donnee,DonneesImageGris *resultat){
    
    int i, j,l=donnee->largeurImage,h=donnee->hauteurImage;
    char **gradx;
    char **grady;
    char **masque;
    float temp=0;
    int var=0;
    int max=0;
    
   donnee=binarisationOtsu(donnee);
     masque = initSobelX();
    gradx = filtremasquecarre(donnee->donneesGris, donnee->largeurImage, donnee->hauteurImage, masque, 3);
    masque = initSobelY();
    grady = filtremasquecarre(donnee->donneesGris, donnee->largeurImage, donnee->hauteurImage, masque, 3);
    for (i = 3; i < h - 3; i++) {
        for (j = 3; j < l- 3; j++) {
          var=60+sqrt(
                    gradx[j][i] * gradx[j][i] + grady[j][i] * grady[j][i]); //valeur dans le masque
          if(var>=255)
            var=255;
            if(var>=max)
                max=var;

             resultat->donneesGris[j][i] = var;
        }
    }


    for (i = 3; i < l- 3; i++) {
        for (j = 3; j < h- 3; j++) {
          

             resultat->donneesGris[i][j] = (resultat->donneesGris[i][j]/max)*255 ;
        }
    }

}/*
void intensiteetdirectiongradient(int largeur, int hauteur,
        unsigned char **tabgris, float **direction, unsigned char **intensite) //gradient intensité == contour
{
    int i, j;
    char **gradx;
    char **grady;
    char **masque;
    int max = 0;

    masque = initSobelX();
    gradx = filtremasquecarre(tabgris, largeur, hauteur, masque, 3);
    masque = initSobelY();
    grady = filtremasquecarre(tabgris, largeur, hauteur, masque, 3);
    for (i = 10; i < hauteur - 10; i++) {
        for (j = 10; j < largeur - 10; j++) {
            intensite[j][i] = sqrt(
                    gradx[j][i] * gradx[j][i] + grady[j][i] * grady[j][i]); //valeur dans le masque
            direction[j][i] = atan((double) grady[j][i] / (double) gradx[j][i]);
            max = maximum(intensite[j][i], max);
        }
    }
//printf("max intensite:%d \n",max);
//libere gradx et grady
}*/

char **initLaplacien() {
    char **masque;

    masque = inittableau2dchar(3, 3);
    masque[0][0] = -1;
    masque[0][1] = -1;
    masque[0][2] = -1;
    masque[1][0] = -1;
    masque[1][1] = 8;
    masque[1][2] = -1;
    masque[2][0] = -1;
    masque[2][1] = -1;
    masque[2][2] = -1;
    return masque;
}

char **initContraste() {
    char **masque;

    masque = inittableau2dchar(3, 3);
    masque[0][0] = 2;
    masque[0][1] = 5;
    masque[0][2] = 2;
    masque[1][0] = 5;
    masque[1][1] = 20;
    masque[1][2] = 5;
    masque[2][0] = 2;
    masque[2][1] = 5;
    masque[2][2] = 2;
    return masque;
}

char **initSobelY() {
    char **masque;

    masque = inittableau2dchar(3, 3);
    masque[0][0] = 1;
    masque[0][1] = 2;
    masque[0][2] = 1;
    masque[1][0] = 0;
    masque[1][1] = 0;
    masque[1][2] = 0;
    masque[2][0] = -1;
    masque[2][1] = -2;
    masque[2][2] = -1;
    return masque;
}
char **initSobelX() {
    char **masque;

    masque = inittableau2dchar(3, 3);
    masque[0][0] = -1;
    masque[0][1] = 0;
    masque[0][2] = 1;
    masque[1][0] = -2;
    masque[1][1] = 0;
    masque[1][2] = 2;
    masque[2][0] = -1;
    masque[2][1] = 0;
    masque[2][2] = 1;
    return masque;
}
char **inittableau2dchar(int x, int y) {
    int erreur = 0;
    int i, j;
    char **ptr;
    ptr = (char**) malloc(x * sizeof(*ptr));
    if (ptr == NULL ) {

        return NULL ;
    }
    for (i = 0; i < x; i++) {
        ptr[i] = (char*) malloc(y * sizeof(char));
        if (ptr[i] == NULL ) {
            erreur = i;
            i = x;
        }
    }
    if (erreur > 0) {
        for (i = 0; i < erreur; i++) {
            free(ptr[i]);
        }
        free(ptr);
        return NULL ;
    }
    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++) {
            ptr[i][j] = 0;
        }
    }
    return ptr;
}

char **filtremasquecarre(unsigned char **tableauinit, int largeur, int hauteur,
        char **masque, int tailleMasque) {
    int i, j;
    int x, y;

    char **tableaufin; //tableau de char renvoyé a la fin pour pupisen egale nvx de gris
    tableaufin = inittableau2dchar(largeur, hauteur);
    if (tableaufin != NULL ) //si tableau alloué on le remplie ligne par ligne
    {
        for (i = tailleMasque / 2; i < hauteur - (tailleMasque / 2 + 1); i++) {
            for (j = tailleMasque / 2; j < largeur - (tailleMasque / 2 + 1);
                    j++) {
                tableaufin[j][i] = 0;
                for (x = -tailleMasque / 2; x <= tailleMasque / 2; x++) {
                    for (y = -tailleMasque / 2; y <= tailleMasque / 2; y++) {
                        if ((tableaufin[j][i]
                                + tableauinit[j + x][i + y]
                                        * masque[x + tailleMasque / 2][y
                                                + tailleMasque / 2]) > 255) {
                            tableaufin[j][i] = 255;
                        } else {
                            tableaufin[j][i] = tableaufin[j][i]
                                    + tableauinit[j + x][i + y]
                                            * masque[x + tailleMasque / 2][y
                                                    + tailleMasque / 2];
                        }

                    }
                }
            }
        }
    }
    return tableaufin;
}
