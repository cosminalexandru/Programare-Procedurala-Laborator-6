#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
//#include "transformation-helper.h"
/**
 *
 * @param binaryFileName represent the name of a binary file
 */

void create_binary_file(char *binaryFileName) {
    FILE *binaryFile;
    binaryFile = fopen(binaryFileName, "wb");

    int dimension, n;
    printf("Introduceti lungimea secventei de numere:\n");
    scanf("%d", &dimension);
    printf("Introduceti n:");
    scanf("%d", &n);
    srand(time(NULL));
    for (int i = 0; i < dimension; i++) {
        int random = rand() % (2 * n) - n;
        fwrite(&random, sizeof(int), 1, binaryFile);
    }
    fclose(binaryFile);
}

/**
 *
 * @param binaryFileName represent the name of a binary file
 */
void sort(char *binaryFileName) {
    FILE *binaryFile = fopen(binaryFileName, "r+b");
    int a, b;
    fseek(binaryFile, 0, SEEK_END);
    int number = ftell(binaryFile) / sizeof(int);
    printf("Fisierul binar are %d elemente. \n", number);
    rewind(binaryFile);
    for (int i = 0; i < number - 1; i++) {
        fseek(binaryFile, i * sizeof(int), SEEK_SET);
        fread(&a, sizeof(int), 1, binaryFile);
        for (int j = i + 1; j < number; j++) {
            fseek(binaryFile, j * sizeof(int), SEEK_SET);
            fread(&b, sizeof(int), 1, binaryFile);
            if (a > b) {
                fseek(binaryFile, i * sizeof(int), SEEK_SET);
                fwrite(&b, sizeof(int), 1, binaryFile);
                fseek(binaryFile, j * sizeof(int), SEEK_SET);
                fwrite(&a, sizeof(int), 1, binaryFile);
                a = b;
            }
        }
    }

    fclose(binaryFile);
}

/**
 *
 * @param binaryFileName represent the name of a binary file
 */
void max_value(char *binaryFileName) {
    int max;
    FILE *binaryFile = fopen(binaryFileName, "rb");
    if (binaryFile == NULL) {
        printf("Fisierul nu exista!");
        exit(0);
    }

    fseek(binaryFile, (-1) * sizeof(int), SEEK_END);
    fread(&max, sizeof(int), 1, binaryFile);
    printf("Valoare maxima este: %d \n", max);
    fclose(binaryFile);
    int index = 2;
    int ok = 1;
    int aux;
    while (ok == 1) {
        fseek(binaryFile, (-1) * index * sizeof(int), SEEK_END);
        fread(&aux, sizeof(int), 1, binaryFile);
        if (aux != max)
            ok = 0;
        else {
            index++;
        }
    }
    printf("Numarul de aparitii este: %d", index - 1);
}

//int main() {
//    char binary_file_name[] = "binar.bin";
//    char text_file_name[] = "numere.txt";
//    create_binary_file(binary_file_name);
//    sort(binary_file_name);
//    binary_to_text(binary_file_name, text_file_name);
//    max_value(binary_file_name);
//    return 0;
//}