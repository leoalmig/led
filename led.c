#include <ncurses.h>

#include "led.h"

int
count_lines(FILE *fp)
{
    int count = 0;
    char ch = '\0';
    while ((ch = fgetc(fp)) != EOF)
        if (ch == '\n')
            count++;

    fseek(fp, 0, SEEK_SET);
    return count;
}

void
load_file_in_buffer(scr_buffer *buf, char *filename)
{
    FILE *fp = fopen(filename, "r");
    int size = count_lines(fp) * 2;
    char ch = '\0';
    int line;

    if (size < buf->size)
        size = buf->size;

    if (fp == NULL) {
        buf->num_of_lines = 1;
        return;
    }

    for (line = 0; line < size && ch != EOF; line++) {
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

    buf = init_screen_buffer(argv[1], BASE_NUM_OF_LINES);
    fclose(fp);

    load_file_in_buffer(buf, argv[1]);

    printw("File: %s\n", buf->filepath);
    getch();

    release_screen_buffer(buf);
    endwin();

    return 0;
}
