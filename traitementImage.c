#include <stdlib.h>
#include "BmpGris.h"

static int compareChars (void const *a, void const *b)
    {
       /* definir des pointeurs type's et initialise's
          avec les parametres */
       int const *pa = a;
       int const *pb = b;

       /* evaluer et retourner l'etat de l'evaluation (tri croissant) */
       return *pa - *pb;
    }

DonneesImageGris *filtreMedianRelache(DonneesImageGris *image)
{
    int i, j;
    
    DonneesImageGris *newImage = (DonneesImageGris*)calloc(1, sizeof(DonneesImageGris));
    newImage->largeurImage = image->largeurImage;
    newImage->hauteurImage = image->hauteurImage;
    
	char **newDonneesGris = inittableau2dchar(image->largeurImage, image->hauteurImage);
    newImage->donneesGris = (unsigned char **)newDonneesGris;
	
    for( i = 0; i < image->hauteurImage; i++)
    for( j = 0; j < image->largeurImage; j++)
	{
		char region[9] = {image->donneesGris[i-1][j-1],
						  image->donneesGris[i][j-1],
					      image->donneesGris[i+1][j-1],
						  image->donneesGris[i-1][j],
						  image->donneesGris[i][j],
                          image->donneesGris[i+1][j],
                          image->donneesGris[i-1][j+1],
                          image->donneesGris[i][j+1],
                          image->donneesGris[i+1][j+1]
						 };
        qsort(region, sizeof region / sizeof *region, sizeof *region, compareChars);
        newDonneesGris[j][i] = region[5];
	}
    
    return newImage;
}