# Written by Lior Shaked 326584125

CC := gcc -c -Wall -pedantic -ansi
LD := gcc
MAIN := mymat
TESTS_INPUT = tests_input.txt
TESTS_OUTPUT = tests_output.txt

.PHONY: default
default: tests

.PHONY: clean
clean:
	rm -f *.o mymat
	rm -f ${TESTS_OUTPUT}

.PHONY: tests
tests: ${TESTS_OUTPUT}
${TESTS_OUTPUT}: ${MAIN} ${TESTS_INPUT}
	@echo testing...
	cat ${TESTS_INPUT} | ./${MAIN} > $@


mat.o: mat.c mat.h
	$(CC) $<

handlemymat.o: handlemymat.c handlemymat.h mat.h
	$(CC) $<

mymat.o: mymat.c handlemymat.h mat.h
	$(CC) $<

mymat: mymat.o mat.o handlemymat.o
	$(LD) -o mymat $^