#include <clock.h>
#include <ncurses.h>

static void printnum(WINDOW * win, int offset, int num);
static void printcolon(WINDOW * win, int offset);

void nclock_display(WINDOW * win, MyTime t)
{
    //hours
    printnum(win,0,t.hr);
    printcolon(win,8);

    //minutes
    printnum(win,12,t.min);
    printcolon(win,20);

    //seconds
    printnum(win,24,t.sec);

    wrefresh(win);
}

static void printnum(WINDOW * win, int offset, int num)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        mvwprintw(win, i, offset  , nclock_characters[num / 10][i]);
        mvwprintw(win, i, offset+4, nclock_characters[num % 10][i]);
    }
}

static void printcolon(WINDOW * win, int offset)
{
    int i; for (i = 0; i < 5; i++)
    {
        mvwprintw(win, i, offset, nclock_characters[10][i]);
    }
}
