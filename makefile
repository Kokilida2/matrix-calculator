CC := gcc -c -Wall -pedantic -ansi
LD := gcc

.PHONY: default
default: mymat

.PHONY: clean
clean:
	rm -f *.o mymat	

mat.o: mat.c mat.h
	$(CC) $<

handlemymat.o: handlemymat.c handlemymat.h mat.h
	$(CC) $<

mymat.o: mymat.c handlemymat.h mat.h
	$(CC) $<

mymat: mymat.o mat.o handlemymat.o
	$(LD) -o mymat $^