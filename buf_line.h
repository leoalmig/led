#ifndef BUF_LINE_H
#define BUF_LINE_H

#include <string.h>

typedef struct buf_line {
    int size;
    char *content;
} buf_line;

void init_line(buf_line *line);
void insert_char(buf_line *line, char ch, int index);
void append_char(buf_line *line, char ch);

#endif
