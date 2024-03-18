//printing the file itself

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fptr;
    char *line = NULL;
    size_t bufsize = 0;

    fptr = fopen(__FILE__, "r");
    if (fptr == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while (getline(&line, &bufsize, fptr) != -1) {
        printf("%s", line);
    }

    free(line);
    fclose(fptr);

    return 0;
}
