#include <stdio.h>
#include <string.h>
struct Student {
    int id;
    char name[30];
    int marks;
};
void addRecord() {
    FILE *fp = fopen("students.txt", "a");
    struct Student s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Marks: ");
    scanf("%d", &s.marks);
    fprintf(fp, "%d\t%s\t%d\n", s.id, s.name, s.marks);
    fclose(fp);
    printf("Record added successfully.\n");
}
void displayRecords() {
    FILE *fp = fopen("students.txt", "r");
    struct Student s;
    int found = 0, serial = 1;
    printf("\n---------------------------------------------------------\n");
    printf("S.No\tID\tName\t\tMarks\n");
    printf("---------------------------------------------------------\n");
    while (fscanf(fp, "%d\t%[^\t]\t%d", &s.id, s.name, &s.marks) != EOF) {
        found = 1;
        printf("%d\t%d\t%-15s\t%d\n", serial++, s.id, s.name, s.marks);
    }
    if (!found) printf("No records found.\n");
    fclose(fp);
}
void searchByID() {
    FILE *fp = fopen("students.txt", "r");
    struct Student s;
    int id, found = 0;
    printf("Enter ID to search: ");
    scanf("%d", &id);
    while (fscanf(fp, "%d\t%[^\t]\t%d", &s.id, s.name, &s.marks) != EOF) {
        if (s.id == id) {
            found = 1;
            printf("\n---------------------------------------------------------\n");
            printf("S.No\tID\tName\t\tMarks\n");
            printf("---------------------------------------------------------\n");
            printf("1\t%d\t%-15s\t%d\n", s.id, s.name, s.marks);
            break;
        }
    }
    if (!found) printf("Record not found.\n");
    fclose(fp);
}
void updateRecord() {
    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Student s;
    int id, found = 0;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    while (fscanf(fp, "%d\t%[^\t]\t%d", &s.id, s.name, &s.marks) != EOF) {
        if (s.id == id) {
            found = 1;
            printf("Enter new Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter new Marks: ");
            scanf("%d", &s.marks);
        }
        fprintf(temp, "%d\t%s\t%d\n", s.id, s.name, s.marks);
    }
    fclose(fp);
    fclose(temp);
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found) printf("Record updated.\n");
    else printf("Record not found.\n");
}
void deleteRecord() {
    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Student s;
    int id, found = 0;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    while (fscanf(fp, "%d\t%[^\t]\t%d", &s.id, s.name, &s.marks) != EOF) {
        if (s.id == id) {
            found = 1;
            continue;
        }
        fprintf(temp, "%d\t%s\t%d\n", s.id, s.name, s.marks);
    }
    fclose(fp);
    fclose(temp);
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found) printf("Record deleted.\n");
    else printf("Record not found.\n");
}
int main() {
    int choice;
    while (1) {
        printf("\n1. Add Record\n2. Display Records\n3. Search by ID\n4. Update Record\n5. Delete Record\n6. Exit\nEnter choice: ");
        scanf("%d", &choice);
        if (choice == 1) addRecord();
        else if (choice == 2) displayRecords();
        else if (choice == 3) searchByID();
        else if (choice == 4) updateRecord();
        else if (choice == 5) deleteRecord();
        else if (choice==6) break;
        else printf("Invalid choice.\n");
    }
    return 0;
}
