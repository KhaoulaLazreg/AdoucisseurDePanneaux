#include <stdlib.h>
#include <stdio.h>
#include "BmpGris.h"
#include "GfxLib.h"

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
void histoTotal(char* nom){
DonneesImageRGB *donneesRGB = lisBMPRGB(nom);
    int i,j,h,l;
    DonneesImageGris *donneesImage = (DonneesImageGris*)calloc(1, sizeof(DonneesImageGris));
    donneesImage->largeurImage = donneesRGB->largeurImage;
    donneesImage->hauteurImage = donneesRGB->hauteurImage;
    
    donneesImage->donneesGris = malloc(donneesRGB->largeurImage * sizeof(*donneesImage->donneesGris));
    
    for(i = 0; i < donneesImage->largeurImage; i++)
    donneesImage->donneesGris[i] = malloc(donneesImage->hauteurImage * sizeof(**donneesImage->donneesGris));

    
    for( i = 0; i < donneesImage->largeurImage; i++)
    for( j = 0; j < donneesImage->hauteurImage; j++)
    donneesImage->donneesGris[i][j] = 0.2126 * donneesRGB->donneesRGB[(donneesImage->largeurImage*i+j)*3]
                    + 0.7152 * donneesRGB->donneesRGB[(donneesImage->largeurImage*i+j)*3+1]
                    + 0.0722 * donneesRGB->donneesRGB[(donneesImage->largeurImage*i+j)*3+2];

    libereDonneesImageRGB(&donneesRGB);

     int max=1;
    float hauteurHisto=700;
    unsigned int gris[256];
    for ( i = 0; i < 256; i++)
    {
       gris[i]=0;
    }
   l=donneesImage->largeurImage;
     h=donneesImage->hauteurImage;
   for( i = 0; i < l; i++)
    for( j = 0; j < h; j++){
   gris[donneesImage->donneesGris[i][j]]+=1;
}
for ( i = 0; i < 255; i++)
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

  free(donneesImage); 

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
