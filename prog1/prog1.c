#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

// Function to add records to binary file
void addRecords(const char *filename, int n) {
    FILE *fp;
    struct Student s;

    fp = fopen(filename, "wb");

    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("\nEnter details of student %d\n", i + 1);

        printf("Roll: ");
        scanf("%d", &s.roll);

        printf("Name: ");
        scanf("%s", s.name);

        printf("Marks: ");
        scanf("%f", &s.marks);

        fwrite(&s, sizeof(struct Student), 1, fp);
    }

    fclose(fp);
}  //hello

// Function to display mth record using fseek
void displayMthRecord(const char *filename, int m) {
    FILE *fp;
    struct Student s;

    fp = fopen(filename, "rb");

    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    // Move file pointer to mth record
    fseek(fp, (m - 1) * sizeof(struct Student), SEEK_SET);

    if (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("\nMth Record:\n");
        printf("Roll  : %d\n", s.roll);
        printf("Name  : %s\n", s.name);
        printf("Marks : %.2f\n", s.marks);
    } else {
        printf("Record not found!\n");
    }

    fclose(fp);
}

// Function to delete a record
void deleteRecord(const char *filename, int rollNo) {
    FILE *fp, *temp;
    struct Student s;
    int found = 0;

    fp = fopen(filename, "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Copy all records except the one to delete
    while (fread(&s, sizeof(struct Student), 1, fp)) {

        if (s.roll == rollNo) {
            found = 1;
            continue; // skip this record
        }

        fwrite(&s, sizeof(struct Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(filename);          // delete old file
    rename("temp.dat", filename); // rename temp file

    if (found)
        printf("Record deleted successfully.\n");
    else
        printf("Record not found.\n");
}

int main() {
    int n, m, roll;

    printf("Enter number of records: ");
    scanf("%d", &n);

    addRecords("student.dat", n);

    printf("\nEnter record number to display: ");
    scanf("%d", &m);

    displayMthRecord("student.dat", m);

    printf("\nEnter roll number to delete: ");
    scanf("%d", &roll);

    deleteRecord("student.dat", roll);

    return 0;
}