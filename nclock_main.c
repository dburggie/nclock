#include <nclock.h>
#include <ncurses.h>
#include <time.h>

static void window_clear(WINDOW * win, int width, int height);

int main(void)
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    int rowc, colc, xmid, ymid, x0, y0, height = 5, width = 31;

    getmaxyx(stdscr,rowc,colc);
    xmid = colc / 2;
    ymid = rowc / 2;

    // window dimensions are 31x5 so x0 = xmid - 15, y0 = wmid - 2
    x0 = xmid - 15;
    y0 = ymid - 15;
    if (x0 < 0 || y0 < 0)
    {
        endwin();
        printw("Increase your window size to at least 31x5 to view clock\n");
        printw("Press any key to quit");
        getch();
        return 0;
    }

    // init clock window
    WINDOW * win = newwin(height, width, y0, x0);

    //int ch;
    time_t epochtime = time(NULL);
    while (1)
    {
        //delay to next clock tick (or F1 key for quit)
        while ( epochtime == time(NULL) );

        //quit if we get the F1 key
        //if (ch == KEY_F(1)) return 0;

        //clear window, then display time
        window_clear(win,width,height);
        nclock_display(win, nclock_getTime());
        refresh();
    }


}

static void window_clear(WINDOW * win, int width, int height)
{
    int y, x;
    for (y = 0; y < height; y++)
        for (x = 0; x < width; x++)
            mvwaddch(win,y,x,' ');
}
