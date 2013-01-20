#include <stdlib.h>
#include <math.h>
#include "BmpGris.h"
#include "traitementImage.h"

int compareChars (const void *a, const void *b)
    {
            const unsigned char *ia = (const unsigned char *)a; // casting pointer types 
            const unsigned char *ib = (const unsigned char *)b;
            return (int)(*ia  - *ib); 
    }

DonneesImageGris *filtreMedianRelache(DonneesImageGris *image)
{
    int i, j, k;
    int borneBas = 3, borneHaut = 7;
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

/////////////////////////////////////

void calculeHisto(DonneesImageGris *image, unsigned int *histo)
{
    int i, j;
    
    for ( i = 0; i < 256; i++)
       histo[i]=0;
    
    for (i = 0; i < image->largeurImage; ++i)
    for (j = 0; j < image->hauteurImage; ++j)
        histo[image->donneesGris[i][j]]+=1;
}

DonneesImageGris *binarisationOtsu(DonneesImageGris *image)
{
    unsigned int histo[256];
    float prob[256];
    float omega[256];
    float myu[256];
    float sigma[256];
    float max_sigma;
    int i, j, seuil;
    
    DonneesImageGris *newImage = (DonneesImageGris*)calloc(1, sizeof(DonneesImageGris));
    newImage->largeurImage = image->largeurImage;
    newImage->hauteurImage = image->hauteurImage;
    
	char **newDonneesGris = inittableau2dchar(image->largeurImage, image->hauteurImage);
    newImage->donneesGris = (unsigned char **)newDonneesGris;
    
    float tailleImage = (float) (image->largeurImage * image->hauteurImage);
    
    calculeHisto(image, histo);
    
    
    for(i = 0; i < 256; i++)
        prob[i] = (float) histo[i] / tailleImage;
    
    omega[0] = prob[0];
    myu[0] = 0.0;
    
    for(i = 1; i < 256; i++)
    {
        omega[i] = omega[i - 1] + prob[i];
        myu[i] = myu[i - 1] + ((float) i * prob[i]); 
    }
    
    for(i = 0; i < 255; i++)
    {
        if((omega[i] != 0.0) && (omega[i] != 1.0))
            sigma[i] = powf(myu[255] * omega[i] - myu[i], 2.0) / (omega[i] * (1.0 - omega[i]));
        else sigma[i] = 0.0;
        
        if(sigma[i] > max_sigma)
        {
            max_sigma = sigma[i];
            seuil = i;
        }
    }
    
    for (i = 0; i < image->largeurImage; ++i)
    {
        for (j = 0; j < image->hauteurImage; ++j)
        {
            if(image->donneesGris[i][j] > seuil)
                newImage->donneesGris[i][j] = 255;
            else newImage->donneesGris[i][j] = 0;
        }
    }
    
    return newImage;
}

int minimum(int A, int B)
{
	if(A<B)
		return A;
	else
		return B;
}

int maximum(int A, int B)
{
	if(A<B)
		return B;
	else
		return A;
}

DonneesImageGris* detourageImage(Rectangle rect, DonneesImageGris* imageInitiale)
{
	unsigned int minx,miny;
	unsigned int maxx,maxy;
	int i,j;
	DonneesImageGris *ptr;
	ptr=(DonneesImageGris*)malloc(sizeof(DonneesImageGris));

	minx=minimum(rect.sommetunX,rect.sommetdeuxX);
	miny=minimum(rect.sommetunY,rect.sommetdeuxY);
	maxx=maximum(rect.sommetunX,rect.sommetdeuxX);
	maxy=maximum(rect.sommetunY,rect.sommetdeuxY);

	ptr-> largeurImage=maxx-minx;
	ptr-> hauteurImage=maxy-miny;

	for(i=1 ; i<ptr-> hauteurImage-1 ; i=i++)
	{
		for(j=1 ; j<ptr-> largeurImage-1; j++)
		{
			ptr-> donneesGris[i][j]= imageInitiale->donneesGris[i+miny][j+minx];
		}
	}
	return ptr;
}