#ifndef SCR_BUFFER_H
#define SCR_BUFFER_H

#define BASE_NUM_OF_LINES 10

#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "buf_line.h"

typedef struct scr_buffer {
    char filepath[100];
    buf_line *lines;
    int size;
    int num_of_lines;
} scr_buffer;

scr_buffer *init_screen_buffer(char *filepath, int num_of_lines);
void release_screen_buffer(scr_buffer *buf);
void render_buffer(scr_buffer *buf, int start, int end);
void insert_line_in_buffer(scr_buffer *buf, int x, int y);

#endif
