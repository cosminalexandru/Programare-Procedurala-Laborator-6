#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *
 * @param sourceName the name of .c file
 **/

void print_source_code(char *sourceName) {
    FILE *textFile = fopen(sourceName, "r");
    if (textFile == NULL) {
        printf("Fisier inexistent!");
        exit(0);
    }
    int noComment = 0;
    char line[100];
    while (fgets(line, 100, textFile) != NULL) {
        if (strstr(line, "//") != NULL)
            continue;
        if (strstr(line, "/*") != NULL) {
            noComment = 1;
            continue;
        }
        if (strstr(line, "*/") != NULL) {
            noComment = 0;
            continue;
        }
        if (noComment == 0)
            printf("%s", line);

    }
}

int main() {
    char sourceName[] = "..//Problem-1.c";
    print_source_code(sourceName);
    return 0;
}