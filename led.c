#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

typedef struct scr_buffer {
    char filepath[100];
} scr_buffer;

scr_buffer*
load_file_in_buffer(char *filepath)
{
    scr_buffer *buf = (scr_buffer *)malloc(sizeof(scr_buffer));

    strcpy(buf->filepath, filepath);

    return buf;
}

void
release_buffer(scr_buffer *buf)
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

    buf = load_file_in_buffer(argv[1]);
    fclose(fp);

    printw("File: %s\n", buf->filepath);
    getch();

    release_buffer(buf);
    endwin();

    return 0;
}
