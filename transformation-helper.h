//
// Created by Cosmin Alex on 11/12/2018.
//

/**
 *
 * @param textFileName - represent the name of a .txt file
 * @param binaryFileName - represent the name of a binary file
 */
void text_to_binary(char *textFileName, char *binaryFileName) {
    FILE *textFile, *binaryFile;
    int number;

    textFile = fopen(textFileName, "r");
    if (textFile == NULL) {
        printf("Fisier text este inexistent!");
        exit(0);
    }

    binaryFile = fopen(binaryFileName, "wb");

    while (fscanf(textFile, "%d", &number) == 1) {
        fwrite(&number, sizeof(int), 1, binaryFile);
    }
    fclose(textFile);
    fclose(binaryFile);
}

/**
 *
 * @param binaryFileName represent the name of a binary file
 * @param textFileName represent the name of a .txt file
 */

void binary_to_text(char *binaryFileName, char *textFileName) {
    FILE *textFile, *binaryFile;
    int number;

    binaryFile = fopen(binaryFileName, "rb");
    if (binaryFile == NULL) {
        printf("Fisierul binar este inexistent!");
        exit(0);
    }

    textFile = fopen(textFileName, "w");

    while (fread(&number, sizeof(int), 1, binaryFile) == 1)
        fprintf(textFile, "%d ", number);
    fclose(textFile);
    fclose(binaryFile);
}
