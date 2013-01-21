#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "BmpGris.h"
#include "traitementImage.h"
DonneesImageGris *RLSA_I(DonneesImageGris *image, int maxGapSize, bool processGapsWithImageBorders){
	int i,j;
	DonneesImageGris *imageH ;
		DonneesImageGris *imageV ;

	DonneesImageGris *imageI = (DonneesImageGris*)calloc(1, sizeof(DonneesImageGris));
    imageI->largeurImage = image->largeurImage;
    imageI->hauteurImage = image->hauteurImage;
	char **newDonneesGris = inittableau2dchar(image->largeurImage, image->hauteurImage);
    imageI->donneesGris = (unsigned char **)newDonneesGris;
////
    
     for( i = 0; i < image->largeurImage; i++)
    for( j = 0; j < image->hauteurImage; j++){
    	imageI->donneesGris[i][j]=255;
    }
imageH=RLSA_H(image, maxGapSize, processGapsWithImageBorders);
imageV=RLSA_V(image, maxGapSize, processGapsWithImageBorders);

     for( i = 0; i < image->largeurImage; i++)
    for( j = 0; j < image->hauteurImage; j++){
    	if(imageV->donneesGris[i][j]==255&&imageH->donneesGris[i][j]==255)
    		imageI->donneesGris[i][j]=image->donneesGris[i][j];
    }
    //negatif(imageI);
//imageI=RLSA_H(imageI, (int)(maxGapSize*0.6), processGapsWithImageBorders);
    libereDonneesImageGris(&imageV);
     libereDonneesImageGris(&imageH);
return imageI;
}
DonneesImageGris *RLSA_H(DonneesImageGris *image, int maxGapSize, bool processGapsWithImageBorders)
{
	int videMax = maximum(1, minimum(1000, maxGapSize));
	
	DonneesImageGris *newImage = (DonneesImageGris*)calloc(1, sizeof(DonneesImageGris));
    newImage->largeurImage = image->largeurImage;
    newImage->hauteurImage = image->hauteurImage;
    
	char **newDonneesGris = inittableau2dchar(image->largeurImage, image->hauteurImage);
    newImage->donneesGris = (unsigned char **)newDonneesGris;
	
	unsigned char *ligneCourante = (unsigned char*)malloc(image->largeurImage * sizeof(unsigned char));
	unsigned char *finLigne = ligneCourante + image->largeurImage * sizeof(unsigned char);
	
	for( int y = 0; y < image->hauteurImage; y++)
	{
		for(int x = 0; x < image->largeurImage; x++)
		{
			ligneCourante[x] = image->donneesGris[x][y];
		}
		
		unsigned char *ptr = ligneCourante;
		
		while(ptr < finLigne)
		{
			unsigned char *debutVide = ptr;
			
			while((ptr < finLigne) && (*ptr == 0))
				ptr++;
			
			if(ptr - debutVide <= videMax)
			{
				if((processGapsWithImageBorders) || ((debutVide != ligneCourante) && (ptr != finLigne)))
				{
					while(debutVide < ptr)
					{
						*debutVide = 255;//remplacement
						debutVide++;
					}
				}
			}
			
			while((ptr < finLigne) && (*ptr != 0))
				ptr++;
		}
		
		for(int x = 0; x < image->largeurImage; x++)
		{
			newImage->donneesGris[x][y] = ligneCourante[x];
		}
	}
	
	free(ligneCourante);
	
	return newImage;
}

DonneesImageGris *RLSA_V(DonneesImageGris *image, int maxGapSize, bool processGapsWithImageBorders)
{
	int videMax = maximum(1, minimum(1000, maxGapSize));
	
	DonneesImageGris *newImage = (DonneesImageGris*)calloc(1, sizeof(DonneesImageGris));
    newImage->largeurImage = image->largeurImage;
    newImage->hauteurImage = image->hauteurImage;
    
	char **newDonneesGris = inittableau2dchar(image->largeurImage, image->hauteurImage);
    newImage->donneesGris = (unsigned char **)newDonneesGris;
	
	for( int x = 0; x < image->largeurImage; x++)
	{
		for(int y = 0; y < image->hauteurImage; y++)
		{
			newImage->donneesGris[x][y] = image->donneesGris[x][y];
		}
		
		unsigned char *ptr = newImage->donneesGris[x];
		unsigned char *finColonne = ptr + image->hauteurImage * sizeof(unsigned char);
		
		while(ptr < finColonne)
		{
			unsigned char *debutVide = ptr;
			
			while((ptr < finColonne) && (*ptr == 0))
				ptr++;
			
			if(ptr - debutVide <= videMax)
			{
				if((processGapsWithImageBorders) || ((debutVide != newImage->donneesGris[x]) && (ptr != finColonne)))
				{
					while(debutVide < ptr)
					{
						*debutVide = 255;//remplacement
						debutVide++;
					}
				}
			}

			
			while((ptr < finColonne) && (*ptr != 0))
				ptr++;
		}
	}
	
	return newImage;
}