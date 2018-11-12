#include <stdlib.h>
#include <stdio.h>
#include "transformation-helper.h"

/**
 *
 * @param textFileName represent the text file name
 */
void split_file(char *textFileName) {
    FILE *textFile = fopen(textFileName, "r");
    if (textFile == NULL) {
        printf("Fisierul nu a fost gasit!");
        exit(0);
    }

    FILE *negativeNumbers = fopen("negatives.bin", "wb");
    FILE *positiveNumbers = fopen("positives.bin", "wb");

    int n, number;
    fscanf(textFile, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(textFile, "%d", &number);
        printf("%d  ", number);
        if (number >= 0)
            fwrite(&number, sizeof(int), 1, positiveNumbers);
        else
            fwrite(&number, sizeof(int), 1, negativeNumbers);
    }
    fclose(negativeNumbers);
    fclose(positiveNumbers);

    binary_to_text("negatives.bin", "negatives.txt");
    binary_to_text("positives.bin", "positives.txt");
}

int main() {
    char numbers[] = "..//numbers.txt";
    split_file(numbers);
}

