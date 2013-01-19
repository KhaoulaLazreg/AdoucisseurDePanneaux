histogramme: histogramme.c libisentlib.a
	gcc -Wall -g histogramme.c  -o  histogramme -lm libisentlib.a -lX11 -lGL -lGLU -lglut 

libisentlib.a: BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o bouton.o BmpGris.o
	ar r libisentlib.a BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o bouton.o BmpGris.o

BmpLib.o: BmpLib.c BmpLib.h OutilsLib.h
	gcc -Wall -O2 -g -c BmpLib.c

ErreurLib.o: ErreurLib.c ErreurLib.h
	gcc -Wall -O2 -g -c ErreurLib.c

ESLib.o: ESLib.c ESLib.h ErreurLib.h
	gcc -Wall -O2 -g -c ESLib.c
	
bouton.o:bouton.c bouton.h 
	gcc -Wall -O2 -g -c bouton.c
	
GfxLib.o: GfxLib.c GfxLib.h ESLib.h
	gcc -Wall -O2 -g -c GfxLib.c -I/usr/include/GL

OutilsLib.o: OutilsLib.c OutilsLib.h
	gcc -Wall -O2 -g -c OutilsLib.c
	
BmpGris.o: BmpGris.c BmpGris.h
	gcc -Wall -O2 -g -c BmpGris.c


clean:
	rm -f *~ *.o libisentlib.a
