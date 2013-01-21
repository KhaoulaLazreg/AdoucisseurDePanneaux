#include <stdlib.h>
#include <math.h>
#include <stdio.h>
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

	for(i=0 ; i<ptr-> hauteurImage ; i=i++)
	{
		for(j=0 ; j<ptr-> largeurImage; j++)
		{
			ptr-> donneesGris[i][j]= imageInitiale->donneesGris[i+miny][j+minx];
		}
	}
	return ptr;
}

DonneesImageGris* copiePartieImage(Rectangle rect, DonneesImageGris* imageInitiale, DonneesImageGris* imageRetour)
{

    unsigned int minx,miny;
    unsigned int maxx,maxy;
    int i,j;

    minx=minimum(rect.sommetunX,rect.sommetdeuxX);
    miny=minimum(rect.sommetunY,rect.sommetdeuxY);
    maxx=maximum(rect.sommetunX,rect.sommetdeuxX);
    maxy=maximum(rect.sommetunY,rect.sommetdeuxY);

    for(i=miny; i<maxy; i++)
    {
        for(j=minx ; j<maxx; j++)
        {
            imageRetour-> donneesGris[j][i]= 128;// imageInitiale->donneesGris[j][i];
        }
    }
    return imageRetour;

}


DonneesImageGris* rechercheZoneDeTexte (DonneesImageGris *donnee)
{
    float MBRL=0;
    float MTC=0;
    int hauteurfenetre,largeurfenetre;
    int i;
    int j;
    float pixelNoir=0;
    float nbTransition=0;
    Rectangle fenetre;
    int l=donnee->largeurImage,h=donnee->hauteurImage;
    // Valeurs 
    float MBRLmax = 14.8;
    float MBRLmin = 0.37;
    float MTCmax = 3.8;
    float MTCmin = 1;

    // Image avec juste le texte à retourner
    DonneesImageGris* imageTexte;
    imageTexte = (DonneesImageGris*)malloc(sizeof(DonneesImageGris));
    imageTexte->hauteurImage = h;
    imageTexte->largeurImage = l;
    
    imageTexte->donneesGris =(unsigned char **)inittableau2dchar(l, h);
    for (i = 0; i < l; ++i)
        {
           for (j= 0; j < h; ++j)
           {
               imageTexte->donneesGris[i][j]=donnee->donneesGris[i][j];
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

                        if ((donnee->donneesGris[j][i]-donnee->donneesGris[j+1][i]>150)||(donnee->donneesGris[j][i]-donnee->donneesGris[j+1][i]<-150))
                            nbTransition+=1;
                        
                        //val max: 255 val min -255
                    }   
                }
                if(nbTransition<1)
                    nbTransition=1;
                if (largeurfenetre<1)
                    largeurfenetre=1;
            MBRL=pixelNoir/(nbTransition);
            MTC= nbTransition/(largeurfenetre);

/*
int l=donnee->largeurImage,h=donnee->hauteurImage;
        
        for (i = 0; i < l; ++i)
        {
           for (j= 0; j < h; ++j)
           {
               if(donnee->donneesGris[i][j]>255)
                donnee->donneesGris[i][j]=255;
            if(donnee->donneesGris[i][j]<0)
                donnee->donneesGris[i][j]=0;
           }
        }*/
            printf("MBRL: %f  Pn: %d nT: %d MTC: %f LF: %d\n",MBRL,(int)pixelNoir,(int)nbTransition,MTC,(int)largeurfenetre);
            // Test si c'est effectivement une zone de texte
            if(MBRL<=MBRLmax && MBRL>=MBRLmin && MTC<=MTCmax && MTC>=MTCmin)
            {
            // On a une zone de texte : on met la fenetre dans l'autre image
              printf("Coucou\n");
                    fenetre.sommetunX= largeurfenetre;
                    fenetre.sommetunY= hauteurfenetre;
                    fenetre.sommetdeuxX= largeurfenetre+tailleFenetreRLSA-1;
                    fenetre.sommetdeuxY= hauteurfenetre+tailleFenetreRLSA-1;

               
               imageTexte = copiePartieImage( fenetre,donnee, imageTexte);
               printf("Coucou1\n");

            }



        }
     }
    return imageTexte;
}