#ifndef LED_H
#define LED_H

#include "utils.h"
#include "scr_buffer.h"

int count_lines(FILE *fp);
void load_file_in_buffer(scr_buffer *buf, char *filename);

#endif
