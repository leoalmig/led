#ifndef BUF_LINE_H
#define BUF_LINE_H

typedef struct buf_line {
    int size;
    char *content;
} buf_line;

void init_line(buf_line *line);

#endif
