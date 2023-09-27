#include <ncurses.h>

#include "led.h"

int
main(int argc, char *argv[])
{
    FILE *fp;
    scr_buffer *buf;

    if (argc != 2) {
        printf("Usage: %s <filepath>\n", argv[0]);
        return 1;
    }

    initscr();

    if (file_exists(argv[1]))
        fp = fopen(argv[1], "r");
    else
        fp = fopen(argv[1], "w");

    buf = init_screen_buffer(argv[1], 1);
    fclose(fp);

    printw("File: %s\n", buf->filepath);
    getch();

    release_screen_buffer(buf);
    endwin();

    return 0;
}
