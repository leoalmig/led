#include <ncurses.h>

int
main()
{
    initscr();
    printw("Hello!");
    getch();
    endwin();
}