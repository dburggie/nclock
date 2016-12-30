#include <nclock.h>
#include <ncurses.h>

/* Window Shape (31x11)
 *
 *                 1   1   2   2   2
 *     0   4   8   2   6   0   4   8
 *  0 "### ### /// ### ### /// ### ###"
 *  1 "### ### /// ### ### /// ### ###"
 *  2 "### ### /// ### ### /// ### ###"
 *  3 "### ### /// ### ### /// ### ###"
 *  4 "### ### /// ### ### /// ### ###"
 *  5 "                               "
 *  6 "### ### ::: ### ### ::: ### ###"
 *  7 "### ### ::: ### ### ::: ### ###"
 *  8 "### ### ::: ### ### ::: ### ###"
 *  9 "### ### ::: ### ### ::: ### ###"
 * 10 "### ### ::: ### ### ::: ### ###"
 */

static void printnum(WINDOW * win, int y0, int x0, int num);
static void printcolon(WINDOW * win, int y0, int x0);
static void printslash(WINDOW * win, int y0, int x0);
static void printc(WINDOW * win, int y0, int x0, int c)

void nclock_display(WINDOW * win, MyTime t)
{
	//month
	printnum(win, 0, 0, t.month);
	printslash(win, 0, 8);

	//day
	printnum(win, 0, 12, t.day);
	printslash(win, 0, 20);

	//year
	printnum(win, 0, 24, t.year);
	
    //hours
    printnum(win,0,t.hr);
    printcolon(win,6, 8);

    //minutes
    printnum(win, 6, 12,t.min);
    printcolon(win, 6, 20);

    //seconds
    printnum(win,24,t.sec);

    wrefresh(win);
}

static void printnum(WINDOW * win, int y0, int x0, int num)
{
	printc(win, y0, x0,   num / 10);
	printc(win, y0, x0+4, num % 10);
}

static void printcolon(WINDOW * win, int y0, int x0)
{
	printc(win,y0,x0,nclock_colon_offset);
}

static void printcolon(WINDOW * win, int y0, int x0)
{
	printc(win,y0,x0,nclock_slash_offset);
}



static void printc(WINDOW * win, int y0, int x0, int c)
{
    int i; for (i = 0; i < 5; i++)
    {
        mvwprintw(win, i, offset, nclock_characters[c][i]);
    }
}
