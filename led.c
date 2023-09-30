#include <ncurses.h>

#include "led.h"

void
move_up(scr_buffer *buf, int *x, int *y)
{
    if (*y > 0)
        (*y)--;

    move(*y, *x);
}

void
move_down(scr_buffer *buf, int *x, int *y)
{
    if (*y < LINES && *y < buf->num_of_lines - 1)
        (*y)++;

    move(*y, *x);
}

void
move_right(scr_buffer *buf, int *x, int *y)
{
    if (*x < strlen(buf->lines[*y].content))
        (*x)++;

    move(*y, *x);
}

void
move_left(scr_buffer *buf, int *x, int *y)
{
    if (*x > 0)
        (*x)--;

    move(*y, *x);
}

int
main(int argc, char *argv[])
{
    FILE *fp;
    scr_buffer *buf;
    int size = 0;
    int x, y;

    if (argc != 2) {
        printf("Usage: %s <filepath>\n", argv[0]);
        return 1;
    }

    initscr();
    noecho();
    keypad(stdscr, true);

    if (file_exists(argv[1])) {
        fp = fopen(argv[1], "r");
        size = count_lines(fp) * 2;
    } else {
        fp = fopen(argv[1], "w");
        size = 1;
    }

    buf = init_screen_buffer(argv[1], size);
    fclose(fp);

    load_file_in_buffer(buf, argv[1]);
    render_buffer(buf, 0, LINES - 1);
    getyx(stdscr, y, x);

    while (TRUE) {
        int ch = getch();

        switch (ch) {
        case KEY_F(4):
            goto quit;
        case KEY_UP:
            move_up(buf, &x, &y);
            break;
        case KEY_DOWN:
            move_down(buf, &x, &y);
            break;
        case KEY_RIGHT:
            move_right(buf, &x, &y);
            break;
        case KEY_LEFT:
            move_left(buf, &x, &y);
            break;
        default:
            // TODO add char
        }
    }

quit:
    endwin();
    release_screen_buffer(buf);
    return 0;
}

void
load_file_in_buffer(scr_buffer *buf, char *filename)
{
    FILE *fp = fopen(filename, "r");
    char ch = '\0';
    int line;

    if (fp == NULL) {
        buf->num_of_lines = 1;
        return;
    }

    for (line = 0; line < buf->size && ch != EOF; line++) {
        ch = fgetc(fp);
        while (ch != '\n' && ch != EOF) {
            buf_line *current_line = &(buf->lines[line]);
            append_char(current_line, ch);

            ch = fgetc(fp);
        }

        buf->num_of_lines++;
    }

    fclose(fp);
}
