#ifndef __CLOCK_H
#define __CLOCK_H

#include <ncurses.h>

typedef struct MyTime MyTime;

struct MyTime {
	int day; // 0 - 31
	int month; //0 - 11
	int year; // 0 - 99
    int sec; // 0 - 60
    int min; // 0 - 59
    int hr;  // 0 - 23
};

MyTime nclock_getTime();

void nclock_display(WINDOW * win, MyTime t);

//11 chars each 5 tall, and 4 wide
extern const int nclock_colon_offset;
extern const int nclock_slash_offset;
extern const char nclock_characters[12][5][4];

#endif
