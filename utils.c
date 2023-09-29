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

int
count_lines(FILE *fp)
{
    int count = 0;
    char ch = '\0';
    while ((ch = fgetc(fp)) != EOF)
        if (ch == '\n')
            count++;

    fseek(fp, 0, SEEK_SET);
    return count;
}
