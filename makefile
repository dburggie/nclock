
INSTALLDIR = ~/bin



ARGS = -I. -Wall -D_DEBUG
CC = gcc ${ARGS}

LIB = -lncurses

OBJ = nclock_getTime.o nclock_characters.o nclock_display.o nclock_main.o
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

nclock_getTime.o: nclock_getTime.c nclock.h
	${CC} -c nclock_getTime.c

nclock_characters.o: nclock_characters.c nclock.h
	${CC} -c nclock_characters.c

nclock_display.o: nclock_display.c nclock.h
	${CC} -c nclock_display.c ${LIB}

nclock_main.o: nclock_main.c nclock.h
	${CC} -c nclock_main.c ${LIB}

