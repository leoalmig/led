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

    return buf;
}

void
release_screen_buffer(scr_buffer *buf)
{
    if (buf->lines)
        free(buf->lines);

    free(buf);
}
