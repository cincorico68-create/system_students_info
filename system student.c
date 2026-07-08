#include <stdio.h> 
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char name[20];
    char major[20];
    float gpa;
    
} Student;
void addStudent(Student students[], int *count);
void displayAllStudents(const Student students[], int count);
void searchByID(const Student students[], int count);
void searchByGPA(const Student students[], int count);
void searchByMajor(const Student students[], int count);

int main() {
    Student students[MAX];
    int studentCount = 0; 
    int choice;
    printf("=== Welcome, Dr. Santos, to the Large-Capacity Student Registry ===\n");
    do {
        printf("\n--- Main Menu ---\n");
        printf("1. Add New Student (Step-by-Step)\n");
        printf("2. Display All Entered Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Find Students by GPA Threshold\n");
        printf("5. Find Students by Major\n");
        printf("6. Exit System\n");
        printf("Current registered students: %d\n", studentCount);
        printf("Enter your choice (1-6): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }
        while (getchar() != '\n'); 
       switch (choice) {
            case 1:
                addStudent(students, &studentCount);
                break;
            case 2:
                displayAllStudents(students, studentCount);
                break;
            case 3:
                searchByID(students, studentCount);
                break;
            case 4:
                searchByGPA(students, studentCount);
                break;
            case 5:
                searchByMajor(students, studentCount);
                break;
            case 6:
                printf("\nExiting system. Goodbye!\n");
                break;
            default:
                printf("\nInvalid selection. Choose 1 to 6.\n");
        }
    } while (choice != 6);

    return 0;
}
void addStudent(Student students[], int *count) {
    if (*count >= MAX) {
        printf("\n[Error] System maximum capacity reached.\n");
        return;
    }
    int current = *count; 
    printf("\n--- Registering Student #%d ---\n", current + 1);
    
    printf("Step 1: Enter ID: ");
    if (scanf("%d", &students[current].id) != 1) {
        printf("[Error] Invalid ID input.\n");
        while (getchar() != '\n');
        return;
    } 
    while (getchar() != '\n'); 
    printf("Step 2: Enter Name: ");
    fgets(students[current].name, 50, stdin);
    students[current].name[strcspn(students[current].name, "\n")] = '\0'; 

    printf("Step 3: Enter Major: ");
    fgets(students[current].major, 50, stdin);
    students[current].major[strcspn(students[current].major, "\n")] = '\0';
    printf("Step 4: Enter GPA: ");
    scanf("%f", &students[current].gpa);

    while (getchar() != '\n');

    (*count)++; 
    printf("\n[Success] Student record saved successfully!\n");
}
void displayAllStudents(const Student students[], int count) {
    if (count == 0) {
        printf("\n[Notice] Registry is empty.\n");
        return;
    }
    printf("\n%-8s %-20s %-20s\n", "ID", "Name", "Major");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-8d %-20s %-20s\n", students[i].id, students[i].name, students[i].major);
    }
}


void searchByID(const Student students[], int count) {
    if (count == 0) {
        printf("\n[Notice] Registry is empty.\n");
        return;
    }
    int searchID;
    printf("\nEnter Student ID to find: ");
    scanf("%d", &searchID);
    while (getchar() != '\n');

    for (int i = 0; i < count; i++) {
        if (students[i].id == searchID) {
            printf("\nMatch Found -> Name: %s | Major: %s | GPA: %.2f\n", 
                   students[i].name, students[i].major, students[i].gpa);
            return;
        }
    }
    printf("\nID %d not found.\n", searchID);
}
void searchByGPA(const Student students[], int count) {
    if (count == 0) {
        printf("\n[Notice] Registry is empty.\n");
        return;
    }
    float threshold;
    int gpaMatches = 0;
    printf("\nEnter minimum GPA threshold: ");
    scanf("%f", &threshold);
    while (getchar() != '\n');

    printf("\nStudents with GPA >= %.2f:\n", threshold);
    for (int i = 0; i < count; i++) {
        if (students[i].gpa >= threshold) {
            printf("- %s (ID: %d | GPA: %.2f)\n", students[i].name, students[i].id, students[i].gpa);
            gpaMatches++;
        }
    }
    if (gpaMatches == 0) printf("No students match this threshold.\n");
}
