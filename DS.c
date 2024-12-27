#include <stdio.h>

#include <stdlib.h>

#include <string.h>



// Structure to hold student information

typedef struct Student {

    int id;

    char name[50];

    float cgpa;

    struct Student* next;

} Student;



// Function to add a student to the linked list

void addStudent(Student** head, int id, char name[], float cgpa) {

    // Create a new student node

    Student* newStudent = (Student*)malloc(sizeof(Student));

    newStudent->id = id;

    strcpy(newStudent->name, name);

    newStudent->cgpa = cgpa;

    newStudent->next = *head;

    *head = newStudent;

}



// Function to search for a student in the linked list

Student* searchStudent(Student* head, int id) {

    Student* currStudent = head;

    while (currStudent != NULL) {

        if (currStudent->id == id) {

            return currStudent;

        }

        currStudent = currStudent->next;

    }

    return NULL;

}



// Function to save the student information to a file

void saveToFile(Student* head, const char* filename) {

    FILE* file = fopen(filename, "w");

    if (file == NULL) {

        printf("Error opening file for writing.\n");

        return;

    }



    Student* currStudent = head;

    while (currStudent != NULL) {

        fprintf(file, "%d,%s,%.2f\n", currStudent->id, currStudent->name, currStudent->cgpa);

        currStudent = currStudent->next;

    }



    fclose(file);

    printf("Data saved to file successfully.\n");

}



// Function to load student information from a file

Student* loadFromFile(const char* filename) {

    FILE* file = fopen(filename, "r");

    if (file == NULL) {

        printf("Error opening file for reading.\n");

        return NULL;

    }



    Student* head = NULL;

    int id;

    char name[50];

    float cgpa;



    while (fscanf(file, "%d,%[^,],%f\n", &id, name, &cgpa) == 3) {

        addStudent(&head, id, name, cgpa);

    }



    fclose(file);

    printf("Data loaded from file successfully.\n");

    return head;

}



// Function to display student information

void displayStudent(Student* student) {

    printf("Student Information:\n");

    printf("ID: %d\n", student->id);

    printf("Name: %s\n", student->name);

    printf("CGPA: %.2f\n", student->cgpa);

}



int main() {

    Student* head = NULL;

    const char* filename = "student_data.txt";



    // Load student information from file (if available)

    head = loadFromFile(filename);



    int choice;

    int id;

    char name[50];

    float cgpa;



    do {

        printf("\nStudent Management System\n");

        printf("1. Add Student\n");

        printf("2. Search Student\n");

        printf("3. Display All Students\n");

        printf("4. Save to File\n");

        printf("0. Exit\n");

        printf("Enter your choice: ");

        scanf("%d", &choice);



        switch (choice) {

            case 1:

                printf("Enter student ID: ");

                scanf("%d", &id);

                printf("Enter student name: ");

                scanf(" %[^\n]s", name);

                printf("Enter student CGPA: ");

                scanf("%f", &cgpa);

                addStudent(&head, id, name, cgpa);

                break;

            case 2:

                printf("Enter student ID to search: ");

                scanf("%d", &id);

                {

                    Student* foundStudent = searchStudent(head, id);

                    if (foundStudent != NULL) {

                        displayStudent(foundStudent);

                    } else {

                        printf("Student not found.\n");

                    }

                }

                break;

            case 3:

                {

                    Student* currStudent = head;

                    while (currStudent != NULL) {

                        displayStudent(currStudent);

                        printf("--------------------------------------\n");

                        currStudent = currStudent->next;

                    }

                }

                break;

            case 4:

                saveToFile(head, filename);

                break;

            case 0:

                printf("Exiting the program.\n");

                break;

            default:

                printf("Invalid choice. Please try again.\n");

        }

    } while (choice != 0);



    // Free the allocated memory

    Student* currStudent = head;

    while (currStudent != NULL) {

        Student* temp = currStudent;

        currStudent = currStudent->next;

        free(temp);

    }



    return 0;

}

