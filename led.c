#include <ncurses.h>

#include "led.h"

int
main(int argc, char *argv[])
{
    FILE *fp;
    scr_buffer *buf;
    int size = 0;

    if (argc != 2) {
        printf("Usage: %s <filepath>\n", argv[0]);
        return 1;
    }

    initscr();

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

    getch();

    release_screen_buffer(buf);
    endwin();

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
