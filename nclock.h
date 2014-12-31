#ifndef __CLOCK_H
#define __CLOCK_H

#include <ncurses.h>

typedef struct MyTime MyTime;

struct MyTime {
    int sec; // 0 - 60
    int min; // 0 - 59
    int hr;  // 0 - 23
};

MyTime nclock_getTime();

void nclock_display(WINDOW * win, MyTime t);

//11 chars each 5 tall, and 4 wide
extern const char nclock_characters[11][5][4];

#endif
