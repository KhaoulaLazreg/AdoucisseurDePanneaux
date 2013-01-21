#include <stdlib.h>
#include <stdio.h>
#include "BmpGris.h"
#include "GfxLib.h"
#include "traitementImage.h"
#include "math.h"
/*int maxConnexite(DonneesImageGris* tab){
    int i,j,l=tab->largeurImage,h=hauteurImage;
    for (i=0;i<h;i++) 
    {
        for(j=0;j<l;i++){//attention aux incices; parcours des colonnes
            if(tab->donneesGris[j][i]
        }
    }
}

bool estConnexe(DonneesImageGris *donnee,Rectangle fenetre){
    int x0= fenetre.sommetunX,y0=fenetre.sommetunY ,x1=fenetre.sommetdeuxX ,y1=fenetre.sommetdeuxY ;
int i,j,normal=0,inverse=0,a=0,b=0;
    DonneesImageGris* val= (DonneesImageGris*)malloc(sizeof(DonneesImageGris));
    val->hauteurImage = h;
    val->largeurImage = l;
    val->donneesGris=(unsigned char **)inittableau2dchar(x1-x0, y1-y0);
    for ( i = x0; i < x1; ++i)
    {
        for (j=y0;j<y1;j++)
        {
        //traitement image normale
            val->donneesGris[a][b]=donnee->donneesGris[i][j];



        //traitement négatif

            b++;
        }
        a++;

    }


}

DonneesImageGris* rechercheConnexite (DonneesImageGris *donnee)
{

    int i;
    int j;
    Rectangle fenetre;
    int l=donnee->largeurImage,h=donnee->hauteurImage;
    // Valeurs 
int tailleMaxLettre=l/5,tailleMinLettre=l/100;
                   fenetre.sommetunX= largeurfenetre;
                    fenetre.sommetunY= hauteurfenetre;
                    fenetre.sommetdeuxX= largeurfenetre+tailleFenetreRLSA-1;
                    fenetre.sommetdeuxY= hauteurfenetre+tailleFenetreRLSA-1;

    // Image avec juste le texte à retourner
    DonneesImageGris* imageTexte= (DonneesImageGris*)malloc(sizeof(DonneesImageGris));
    imageTexte->hauteurImage = h;
    imageTexte->largeurImage = l;
    imageTexte->donneesGris =(unsigned char **)inittableau2dchar(l, h);

    for (i = 0; i < l; ++i)
        {
           for (j= 0; j < h; ++j)
           {
               imageTexte->donneesGris[i][j]=128;
           }
       }

    // On déplace la fenetre sur l'image
    for(hauteurfenetre=0 ; hauteurfenetre<donnee->hauteurImage-tailleFenetreRLSA ; hauteurfenetre+=tailleFenetreRLSA)
    {
        for(largeurfenetre=0 ; largeurfenetre<donnee->largeurImage-tailleFenetreRLSA; largeurfenetre+=tailleFenetreRLSA)
        {
    
                // On se déplace dans la fenêtre
                for(i=hauteurfenetre ; i<hauteurfenetre+tailleFenetreRLSA-1 ; i++)
                {
                    for(j=0 ; j<largeurfenetre+tailleFenetreRLSA; j++)
                    {
                        if (donnee->donneesGris[j][i]>150)
                            pixelNoir+=1;

                        if (donnee->donneesGris[j][i]-donnee->donneesGris[j+1][i]<50)
                            nbTransition+=1;
                    }   
                }




        }
     }
    return imageTexte;
}


*/





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
  /*  int seuil=0;
    int compteur=0;
    int max =(l*h)/2;

      

    char t=0;
        unsigned int gris[256];
    for ( i = 0; i < 256; i++)
    {
       gris[i]=0;
    }
for (i = 0; i < l; ++i)
{
    for (int j = 0; j < h; ++j)
    {
        gris[donnee->donneesGris[i][j]]+=1;
        
    }
}
for ( i = 0; i < 256; ++i)
{
   compteur+= gris[i];
   if(compteur>=max){
    seuil=i;
    break;
    }
}
printf("Valeur seuil: %d\n",seuil);
for (i = 0; i < l; ++i)
{
    for (int j = 0; j < h; ++j)
    {
       
        if(donnee->donneesGris[i][j]<seuil ){
           donnee->donneesGris[i][j]=0; 
        }
        else
          donnee->donneesGris[i][j]=255;   
        //if(donnee->donneesGris[i][j]>200 ){
       //    donnee->donneesGris[i][j]=255; 
      //  }
    }
}
*/
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
