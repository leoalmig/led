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
