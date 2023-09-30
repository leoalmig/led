#include "scr_buffer.h"

scr_buffer*
init_screen_buffer(char *filepath, int num_of_lines)
{
    int i;

    scr_buffer *buf = (scr_buffer *)malloc(sizeof(scr_buffer));
    strcpy(buf->filepath, filepath);

    buf->lines = (buf_line *)malloc(num_of_lines * sizeof(buf_line));
    for (i = 0; i < num_of_lines; i++)
        init_line(buf->lines + i);

    buf->size = num_of_lines;
    buf->num_of_lines = 0;

    return buf;
}

void
release_screen_buffer(scr_buffer *buf)
{
    if (buf->lines)
        free(buf->lines);

    free(buf);
}

void
render_buffer(scr_buffer *buf, int start, int end)
{
    int i, line;

    for (i = start, line = 0; i < buf->num_of_lines && i < end; i++, line++) {
        move(line, 0);
        clrtoeol();
        printw("%s", buf->lines[i].content);
    }

    if (start < end) {
        move(line, 0);
        clrtoeol();
        move(line - 1, strlen(buf->lines[line - 1].content));
    }

    refresh();
}

void
insert_line_in_buffer(scr_buffer *buf, int x, int y)
{
    int i;
    for (i = buf->num_of_lines - 1; i >= y; i--)
        buf->lines[i + 1] = buf->lines[i];

    buf_line line;
    init_line(&line);

    if (x > 0) {
        int j, k;
        for (j = 0, k = x; buf->lines[y].content[k] != '\0'; j++, k++)
            line.content[j] = buf->lines[y].content[k];

        line.content[j] = '\0';
        buf->lines[y].content[x] = '\0';
        buf->lines[y].size = x;
        buf->lines[y + 1] = line;
    } else {
        buf->lines[y] = line;
    }

    (buf->num_of_lines)++;
}
