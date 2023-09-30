#ifndef LED_H
#define LED_H

#include "utils.h"
#include "scr_buffer.h"

void load_file_in_buffer(scr_buffer *buf, char *filename);

void move_up(scr_buffer *buf, int *x, int *y);
void move_down(scr_buffer *buf, int *x, int *y);
void move_right(scr_buffer *buf, int *x, int *y);
void move_left(scr_buffer *buf, int *x, int *y);

#endif
