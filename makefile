
INSTALLDIR = ~/bin

ARGS = -I. -Wall -D_DEBUG
CC = gcc ${ARGS}

LIB = -lncurses

OBJ = nclock.o nclock_characters.o
EXE = nclock

all: ${EXE}

install: all
	mkdir -p ${INSTALLDIR}
	cp ${EXE} ${INSTALLDIR}

clean:
	rm *.o
	rm ${EXE}

nclock: ${OBJ} nclock.h
	${CC} -o nclock ${OBJ} ${LIB}

nclock_characters.o: nclock_characters.c nclock.h
	${CC} -c nclock_characters.c

nclock.o: nclock.c nclock.h
	${CC} -c nclock.c

