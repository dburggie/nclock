#include <nclock.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

static void window_clear(WINDOW * win, int width, int height);
static void nclock_make_festive(WINDOW * win);

int main(void)
{
    initscr(); // start curses mode
    halfdelay(1); // pause looking for a tenth when looking for input
    keypad(stdscr, TRUE); // allow input from keyboard
    noecho(); // turn off echoing key presses
    curs_set(0); // turn off cursor

    // setup color green on black
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK );
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
    attrset( COLOR_PAIR(1) );
    

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
            window_clear(win,width,height);
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

static void window_clear(WINDOW * win, int width, int height)
{
    int y, x;
    for (y = 0; y < height; y++)
        for (x = 0; x < width; x++)
            mvwaddch(win,y,x,' ');
}


static int nclock_random_seed = 1;

static void nclock_make_festive(WINDOW * win)
{
	if (nclock_random_seed)
	{
		srand(time(NULL));
		nclock_random_seed = 0;
	}

	int color = 1 + (rand() % 7);
	wattrset(win, COLOR_PAIR(color));
}
