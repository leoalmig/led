#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

typedef struct buf_line {
    int size;
    char *content;
} buf_line;

typedef struct scr_buffer {
    char filepath[100];
    buf_line *lines;
} scr_buffer;

/* Initialize an empty line of size 100 */
void
init_line(buf_line *line)
{
    line->size = 100;
    line->content = (char *)malloc(100 * sizeof(char));
    line->content[0] = '\0';
}

scr_buffer*
init_screen_buffer(char *filepath, int num_of_lines)
{
    int i;

    scr_buffer *buf = (scr_buffer *)malloc(sizeof(scr_buffer));
    strcpy(buf->filepath, filepath);

    buf->lines = (buf_line *)malloc(num_of_lines * sizeof(buf_line));
    for (i = 0; i < num_of_lines; i++)
        init_line(buf->lines + i);

    return buf;
}

void
release_screen_buffer(scr_buffer *buf)
{
    free(buf);
}

int
file_exists(char *filepath)
{
    FILE *fp = fopen(filepath, "r");
    if (fp != NULL) {
        fclose(fp);
        return 1;
    }

    return 0;
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

    buf = init_screen_buffer(argv[1], 1);
    fclose(fp);

    printw("File: %s\n", buf->filepath);
    getch();

    release_screen_buffer(buf);
    endwin();

    return 0;
}
