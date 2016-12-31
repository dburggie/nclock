#include <nclock.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

static void nclock_window_clear(WINDOW * win, int width, int height);
static void nclock_make_festive(WINDOW * win);
static void nclock_printnum(WINDOW * win, int y0, int x0, int num);
static void nclock_printcolon(WINDOW * win, int y0, int x0);
static void nclock_printslash(WINDOW * win, int y0, int x0);
static void nclock_printc(WINDOW * win, int y0, int x0, int c);

int main(void)
{
	//init ncurses
	initscr();
	halfdelay(1); // hang for up to a tenth when looking for input
	keypad(stdscr, TRUE); // allow input from keyboard
	noecho(); // turn off echoing key presses
	curs_set(0); // turn off cursor

	// setup color and set default color
	if (has_colors())
	{
		start_color();
		init_pair(1, COLOR_GREEN, COLOR_BLACK );
		init_pair(2, COLOR_RED, COLOR_BLACK);
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);
		init_pair(4, COLOR_BLUE, COLOR_BLACK);
		init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(6, COLOR_CYAN, COLOR_BLACK);
		init_pair(7, COLOR_WHITE, COLOR_BLACK);
		attrset( COLOR_PAIR(1) );
	}

	int rowc, colc, xmid, ymid, x0, y0, height = 11, width = 31;
	getmaxyx(stdscr,rowc,colc);
	xmid = colc / 2;
	ymid = rowc / 2;

	// window dimensions are 31x11 so x0 = xmid - 15, y0 = wmid - 5
	x0 = xmid - 15;
	y0 = ymid - 5;
	if (x0 < 0 || y0 < 0)
	{
		endwin();
		printw("Your terminal window is %ix%i.\n", colc, rowc);
		printw("Increase your window size to at least 31x11 to view clock\n");
		printw("Press any key to quit");
		getch();
		endwin();
		return 0;
	}

	// init clock window
	WINDOW * win = newwin(height, width, y0, x0);
	wattrset(win, COLOR_PAIR(1));
	
	int ch;
	time_t epochtime = time(NULL);
	while ( (ch = getch()) != KEY_F(2) )
	{
		if (epochtime != time(NULL))
		{
			//clear window, then display time
			nclock_window_clear(win,width,height);
			if (nclock_display(win, nclock_getTime())) {
				nclock_make_festive(win);
			}
			wrefresh(win);
			refresh();
			epochtime = time(NULL);
		}
	}

	attroff(COLOR_PAIR(1));
	wattroff(win, COLOR_PAIR(1));
	endwin();
	
	return 0;
}

MyTime nclock_getTime()
{
	MyTime t;

	time_t et = time(NULL);
	struct tm *tmptr = localtime(&et);
	t.day = tmptr->tm_mday;
	t.month = tmptr->tm_mon + 1; //tm_mon counts months since january
	t.year = tmptr->tm_year % 100; //want two digits, counts years since 1900
	t.sec = tmptr->tm_sec;
	t.min = tmptr->tm_min;
	t.hr  = tmptr->tm_hour;

	return t;
}

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

int nclock_display(WINDOW * win, MyTime t)
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

	if ((t.day + t.month) == 1) return 1; //return 1 on january first
	//if (t.day == 30 && t.month == 12) return 1;
	return 0;
}

static void nclock_window_clear(WINDOW * win, int width, int height)
{
	int y, x;
	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++)
			mvwaddch(win,y,x,' ');
}

static int nclock_random_unseeded = 1;
static void nclock_make_festive(WINDOW * win)
{
	if (has_colors())
	{
		if (nclock_random_unseeded)
		{
			srand(time(NULL));
			nclock_random_unseeded = 0;
		}

		int color = 1 + (rand() % 7);
		wattrset(win, COLOR_PAIR(color));
	}
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
