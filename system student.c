#include <stdio.h> 
#include <string.h>


#define MAX_CAPACITY 10000 


void addStudent(int ids[], char names[][50], char majors[][50], float gpas[], int credits[], int *count);
void displayAllStudents(int ids[], char names[][50], char majors[][50], int count);
void searchByID(int ids[], char names[][50], char majors[][50], float gpas[], int credits[], int count);
void searchByGPA(int ids[], char names[][50], float gpas[], int count);
void searchByMajor(int ids[], char names[][50], char majors[][50], int count);

int main() {
    
    int ids[MAX_CAPACITY];
    char names[MAX_CAPACITY][50];
    char majors[MAX_CAPACITY][50];
    float gpas[MAX_CAPACITY];
    int credits[MAX_CAPACITY];

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
        
                addStudent(ids, names, majors, gpas, credits, &studentCount);
                break;
            case 2:
                displayAllStudents(ids, names, majors, studentCount);
                break;
            case 3:
                searchByID(ids, names, majors, gpas, credits, studentCount);
                break;
            case 4:
                searchByGPA(ids, names, gpas, studentCount);
                break;
            case 5:
                searchByMajor(ids, names, majors, studentCount);
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


void addStudent(int ids[], char names[][50], char majors[][50], float gpas[], int credits[], int *count) {
    if (*count >= MAX_CAPACITY) {
        printf("\n[Error] System maximum capacity reached.\n");
        return;
    }

    int current = *count; 
    printf("\n--- Registering Student #%d ---\n", current + 1);
    
    printf("Step 1: Enter ID: ");
    scanf("%d", &ids[current]);
    while (getchar() != '\n');

    printf("Step 2: Enter Name: ");
    fgets(names[current], 50, stdin);
    names[current][strcspn(names[current], "\n")] = '\0';

    printf("Step 3: Enter Major: ");
    fgets(majors[current], 50, stdin);
    majors[current][strcspn(majors[current], "\n")] = '\0';

    printf("Step 4: Enter GPA: ");
    scanf("%f", &gpas[current]);

    printf("Step 5: Enter Credits Completed: ");
    scanf("%d", &credits[current]);
    while (getchar() != '\n');

    (*count)++; 
    printf("\n[Success] Student record saved successfully!\n");
}


void displayAllStudents(int ids[], char names[][50], char majors[][50], int count) {
    if (count == 0) {
        printf("\n[Notice] Registry is empty.\n");
        return;
    }
    printf("\n%-8s %-20s %-20s\n", "ID", "Name", "Major");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-8d %-20s %-20s\n", ids[i], names[i], majors[i]);
    }
}


void searchByID(int ids[], char names[][50], char majors[][50], float gpas[], int credits[], int count) {
    if (count == 0) {
        printf("\n[Notice] Registry is empty.\n");
        return;
    }
    int searchID;
    printf("\nEnter Student ID to find: ");
    scanf("%d", &searchID);
    while (getchar() != '\n');

    for (int i = 0; i < count; i++) {
        if (ids[i] == searchID) {
            printf("\nMatch Found -> Name: %s | Major: %s | GPA: %.2f | Credits: %d\n", 
                   names[i], majors[i], gpas[i], credits[i]);
            return;
        }
    }
    printf("\nID %d not found.\n", searchID);
}


void searchByGPA(int ids[], char names[][50], float gpas[], int count) {
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
        if (gpas[i] >= threshold) {
            printf("- %s (ID: %d | GPA: %.2f)\n", names[i], ids[i], gpas[i]);
            gpaMatches++;
        }
    }
    if (gpaMatches == 0) printf("No students match this threshold.\n");
}


void searchByMajor(int ids[], char names[][50], char majors[][50], int count) {
    if (count == 0) {
        printf("\n[Notice] Registry is empty.\n");
        return;
    }
    char searchMajor[50];
    int majorCount = 0;
    printf("\nEnter Major to query: ");
    fgets(searchMajor, sizeof(searchMajor), stdin);
    searchMajor[strcspn(searchMajor, "\n")] = '\0';

    printf("\nStudents in %s:\n", searchMajor);
    for (int i = 0; i < count; i++) {
        if (strcmp(majors[i], searchMajor) == 0) {
            printf("- %s (ID: %d)\n", names[i], ids[i]);
            majorCount++;
        }
    }
    printf("Total headcount for %s: %d\n", searchMajor, majorCount);
}