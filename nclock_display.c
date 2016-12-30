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

static void nclock_printnum(WINDOW * win, int y0, int x0, int num);
static void nclock_printcolon(WINDOW * win, int y0, int x0);
static void nclock_printslash(WINDOW * win, int y0, int x0);
static void nclock_printc(WINDOW * win, int y0, int x0, int c);

void nclock_display(WINDOW * win, MyTime t)
{
	//month
	nclock_printnum(win, 0, 0, t.month);
	nclock_printslash(win, 0, 8);

	//day
	nclock_printnum(win, 0, 12, t.day);
	nclock_printslash(win, 0, 20);

	//year
	nclock_printnum(win, 0, 24, t.year);
	
    //hours
	nclock_printnum(win, 6, 0, t.hr);
    nclock_printcolon(win, 6, 8);

    //minutes
    nclock_printnum(win, 6, 12, t.min);
    nclock_printcolon(win, 6, 20);

    //seconds
    nclock_printnum(win, 6,24, t.sec);

    wrefresh(win);
}

static void nclock_printnum(WINDOW * win, int y0, int x0, int num)
{
	nclock_printc(win, y0, x0,   num / 10);
	nclock_printc(win, y0, x0+4, num % 10);
}

static void nclock_printcolon(WINDOW * win, int y0, int x0)
{
	nclock_printc(win,y0,x0,nclock_colon_offset);
}

static void nclock_printslash(WINDOW * win, int y0, int x0)
{
	nclock_printc(win,y0,x0,nclock_slash_offset);
}



static void nclock_printc(WINDOW * win, int y0, int x0, int c)
{
    int i; for (i = 0; i < 5; i++)
    {
        mvwprintw(win, y0 + i, x0, nclock_characters[c][i]);
    }
}
