#include "utils.h"

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
