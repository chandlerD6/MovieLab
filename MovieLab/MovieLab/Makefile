# Makefile by Chandler Ditolla SID: 18731640

DESIGN = MovieLab 

LIBS   = libfilter.a libfileIO.a 

CC     = gcc
CFLAGS = -ansi -Wall -c -g
LFLAGS = -Wall

all: $(DESIGN)

MovieLab: MovieLab.o $(LIBS)
	$(CC) $(LFLAGS) -g MovieLab.o -lfilter -lfileIO -L. -o MovieLab

MovieLab.o: MovieLab.c Constants.h FileIO.h Image.h ImageList.h DIPs.h
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o 

FileIO.o: FileIO.c FileIO.h Image.h Constants.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h Image.h Movie.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

ImageList.o: ImageList.h ImageList.c Constants.h
	$(CC) $(CFLAGS) ImageList.c -o ImageList.o
 
Image.o: Image.h Image.c Constants.h
	$(CC) $(CFLAGS) Image.c -o Image.o

Movie.o: Movie.h Movie.c Constants.h
	$(CC) $(CFLAGS) Movie.c -o Movie.o

libfilter.a: Image.o ImageList.o Movie.o DIPs.o
	ar rc libfilter.a Image.o ImageList.o Movie.o DIPs.o
	ranlib libfilter.a
libfileIO.a: FileIO.o
	ar rc libfileIO.a FileIO.o
	ranlib  libfileIO.a
clean:
	rm -f *.o out.yuv $(DESIGN) $(LIBS)
