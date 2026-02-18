#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("tester.txt", O_RDONLY);
    char *line;
    /*
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    */
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    return (0);
    close(fd);
}
