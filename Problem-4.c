
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int id;
    char nume[20], prenume[20];
    float nota;
} Student;

enum {
    CREARE = 1,
    AFISARE,
    MODIFICARE,
    ADAUGARE
};

/**
 *
 * @param nume_fisier_binar represent the name of binary file
 * @param n represent the number of the students
 */
void creare(char *nume_fisier_binar, int n) {
    FILE *binaryFile = fopen(nume_fisier_binar, "wb");
    for (int i = 0; i < n; i++) {
        Student student;
        printf("Introduceti id-ul:");
        scanf("%d", &student.id);
        printf("Introduceti numele:");
        scanf("%s", student.nume);
        printf("Introduceti prenumele:");
        scanf("%s", student.prenume);
        printf("Introduceti nota:");
        scanf("%f", &student.nota);
        fwrite(&student, sizeof(Student), 1, binaryFile);
    }

    fclose(binaryFile);
}

/**
 *
 * @param nume_fisier_binar
 * @param nume_fisier_text
 */
void afisare(char *nume_fisier_binar, char *nume_fisier_text) {
    FILE *textFile, *binaryFile;
    binaryFile = fopen(nume_fisier_binar, "rb");
    if (binaryFile == NULL) {
        printf("Fisier inexistent!");
        exit(0);
    }
    textFile = fopen(nume_fisier_text, "w");
    fseek(binaryFile, 0, SEEK_END);
    int studentsNumber = ftell(binaryFile) / sizeof(Student);
    rewind(binaryFile);
    Student students[100];
    fread(students, studentsNumber * sizeof(Student), 1, binaryFile);
    for (int i = 0; i < studentsNumber; i++) {
        fprintf(textFile, "%d %s %s %f \n", students[i].id, students[i].nume, students[i].prenume, students[i].nota);
    }
    fclose(textFile);
    fclose(binaryFile);
}


/**
 *
 * @param nume_fisier_binar
 * @param id
 * @param nota
 */
void modificare(char *nume_fisier_binar, int id, float nota) {
    FILE *binaryFile = fopen(nume_fisier_binar, "rb+");
    if (binaryFile == 0) {
        printf("Fisierul nu exista!");
        exit(0);
    }
    fseek(binaryFile, 0, SEEK_END);
    int studentsNumber = ftell(binaryFile) / sizeof(Student);
    rewind(binaryFile);
    int index = 0;
    while (index < studentsNumber) {
        Student student;
        fseek(binaryFile, index * sizeof(Student), SEEK_SET);
        fread(&student, sizeof(Student), 1, binaryFile);
        if (student.id == id) {
            student.nota = nota;
            fseek(binaryFile, index * sizeof(Student), SEEK_SET);
            fwrite(&student, sizeof(Student), 1, binaryFile);
            break;
        } else
            index++;
    }
    fclose(binaryFile);

}

/**
 *
 * @param nume_fisier_binar
 * @param student
 */
void adaugare(char *nume_fisier_binar, Student student) {
    FILE *binaryFile = fopen(nume_fisier_binar, "ab+");
    if (binaryFile == NULL) {
        printf("Fisier inexistent");
        exit(0);
    }
    fwrite(&student, sizeof(Student), 1, binaryFile);
    fclose(binaryFile);


}

int main() {
    int studentsNumber;
    char studentsFile[] = "students.bin";
    char studentsTextFile[] = "students.txt";
    int optiune;
    printf("Alegeti una din urmatoarele optiuni: 1.Creare catalog\n 2.Export studenti\n 3.Modificare nota\n 4.Adaugare");
    scanf("%d", &optiune);
    switch (optiune) {
        case CREARE : {
            printf("Introduceti numarul de studenti:");
            scanf("%d", &studentsNumber);
            creare(studentsFile, studentsNumber);
            afisare(studentsFile, studentsTextFile);
            break;
        }
        case AFISARE: {
            afisare(studentsFile, studentsTextFile);
            break;
        }

        case MODIFICARE: {
            int id;
            float nota;
            printf("Introduceti id-ul:");
            scanf("%d", &id);
            printf("Introduceti nota:");
            scanf("%f", &nota);
            modificare(studentsFile, id, nota);
            afisare(studentsFile, studentsTextFile);
            break;
        }
        case ADAUGARE: {
            Student student;
            printf("Introduceti id-ul:");
            scanf("%d", &student.id);
            printf("Introduceti numele:");
            scanf("%s", student.nume);
            printf("Introduceti prenumele:");
            scanf("%s", student.prenume);
            printf("Introduceti nota:");
            scanf("%f", &student.nota);
            adaugare(studentsFile, student);
            afisare(studentsFile, studentsTextFile);
            break;
        }
        default:
            afisare(studentsFile, studentsTextFile);
    }
    return 0;
}