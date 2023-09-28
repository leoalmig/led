#include <stdlib.h>

#include "buf_line.h"

/* Initialize an empty line of size 100 */
void
init_line(buf_line *line)
{
    line->size = 100;
    line->content = (char *)malloc(100 * sizeof(char));
    line->content[0] = '\0';
}

void
increase_line_length(buf_line *line)
{
    int new_size = line->size * 2;
    char *temp = (char *)malloc(new_size * sizeof(char));
    strcpy(temp, line->content);
    free(line->content);
    line->content = temp;
    line->size = new_size;
}

void
append_char(buf_line *line, char ch)
{
    int i;
    int last_idx = strlen(line->content);

    if (strlen(line->content) >= line->size - 2)
        increase_line_length(line);

    line->content[last_idx] = ch;
    line->content[last_idx + 1] = '\0';
}
