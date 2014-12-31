
INSTALLDIR = ~/bin

ARGS = -I. -Wall -D_DEBUG
CC = gcc ${ARGS}

LIB = -lncurses

OBJ = nclock_getTime.o nclock_characters.o nclock_display.o nclock_main.o
EXE = nclock

all: ${EXE}

install: all
	cp ${EXE} ${INSTALLDIR}

clean:
	rm ${OBJ}
	rm ${EXE}

nclock: ${OBJ} clock.h
	${CC} -o nclock ${OBJ} ${LIB}

nclock_getTime.o: getTime.c clock.h
	${CC} -c nclock_getTime.c

nclock_characters.o: characters.c clock.h
	${CC} -c nclock_characters.c

nclock_display.o: display.c clock.h
	${CC} -c nclock_display.c ${LIB}

nclock_main.o: main.c clock.h
	${CC} -c nclock_main.c ${LIB}

