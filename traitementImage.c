#include <stdlib.h>
#include "BmpGris.h"

int compareChars (const void *a, const void *b)
    {
            const unsigned char *ia = (const unsigned char *)a; // casting pointer types 
            const unsigned char *ib = (const unsigned char *)b;
            return (int)(*ia  - *ib); 
    }

DonneesImageGris *filtreMedianRelache(DonneesImageGris *image)
{
    int i, j, k;
    int borneBas = 2, borneHaut = 8;
    bool valeurTrouvee = false;
    
    DonneesImageGris *newImage = (DonneesImageGris*)calloc(1, sizeof(DonneesImageGris));
    newImage->largeurImage = image->largeurImage;
    newImage->hauteurImage = image->hauteurImage;
    
	char **newDonneesGris = inittableau2dchar(image->largeurImage, image->hauteurImage);
    newImage->donneesGris = (unsigned char **)newDonneesGris;
	
    for( i = 1; i < image->hauteurImage-1; i++)
    for( j = 1; j < image->largeurImage-1; j++)
	{
		char region[9] = {image->donneesGris[j-1][i-1],
						  image->donneesGris[j-1][i],
                          image->donneesGris[j-1][i+1],
						  image->donneesGris[j][i-1],
						  image->donneesGris[j][i],
                          image->donneesGris[j][i+1],
					      image->donneesGris[j+1][i-1],
                          image->donneesGris[j+1][i],
                          image->donneesGris[j+1][i+1]
						 };
        qsort(region, sizeof region / sizeof *region, sizeof *region, compareChars);
        
        for(k = borneBas; k <= borneHaut; k++)
        {
            if(region[k] == image->donneesGris[j][i])
            {
                newDonneesGris[j][i] = image->donneesGris[j][i];
                valeurTrouvee = true;
            }
        }
        
        if(!valeurTrouvee)
            newDonneesGris[j][i] = region[5];
        
        valeurTrouvee = false;
	}
    
    libereDonneesImageGris(&image);
    return newImage;
}