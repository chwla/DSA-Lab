#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ID_LENGTH 20
#define MAX_ENTRIES 10000

// Structure to hold student information
typedef struct {
    char id[MAX_ID_LENGTH];
    float cgpa;
} Student;

// Structure for a node in the linked list
typedef struct ListNode {
    Student data;
    struct ListNode* next;
} ListNode;

// Function to read data from file and populate dynamic array
void populateDynamicArray(Student* students, int* numEntries) {
    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    *numEntries = 0;
    while ((*numEntries < MAX_ENTRIES) && (fscanf(file, "%19[^,],%f\n", students[*numEntries].id, &students[*numEntries].cgpa) == 2)) {
        (*numEntries)++;
    }

    fclose(file);
}

// Function to populate linked list
ListNode* createNode(Student data) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendToList(ListNode** head, Student data) {
    ListNode* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        ListNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void populateLinkedList(ListNode** head) {
    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char id[MAX_ID_LENGTH];
    float cgpa;
    while (fscanf(file, "%19[^,],%f\n", id, &cgpa) == 2) {
        Student student;
        strcpy(student.id, id);
        student.cgpa = cgpa;
        appendToList(head, student);
    }

    fclose(file);
}

// Function to measure time taken for each operation
double measureTimeTaken(clock_t start, clock_t end) {
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

// Function to insert new entries at specified positions in dynamic array
void insertDynamicArray(Student* students, int* numEntries) {
    for (int i = 0; i < 10; i++) {
        // Simulate user input for new entry
        printf("Enter ID and CGPA for entry %d: ", i + 1);
        scanf("%19s %f", students[*numEntries + i].id, &students[*numEntries + i].cgpa);
        (*numEntries)++;
    }
}

// Function to insert new entries at specified positions in linked list
void insertLinkedList(ListNode** head) {
    for (int i = 0; i < 10; i++) {
        // Simulate user input for new entry
        Student student;
        printf("Enter ID and CGPA for entry %d: ", i + 1);
        scanf("%19s %f", student.id, &student.cgpa);
        appendToList(head, student);
    }
}

// Function to display contents of linked list
void displayLinkedList(ListNode* head) {
    ListNode* current = head;
    while (current != NULL) {
        printf("ID: %s, CGPA: %.2f\n", current->data.id, current->data.cgpa);
        current = current->next;
    }
}

// Function to free memory allocated for linked list
void freeLinkedList(ListNode* head) {
    while (head != NULL) {
        ListNode* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    

    // Task 10a: Populating dynamic array
    Student dynamicArray[MAX_ENTRIES];
    int numEntriesDynamicArray = 0;
    start = clock();
    populateDynamicArray(dynamicArray, &numEntriesDynamicArray);
    end = clock();
    timeTaken = measureTimeTaken(start, end);
    printf("Time taken to populate dynamic array: %f seconds\n", timeTaken);

    // Task 10a: Populating linked list
    ListNode* linkedListHead = NULL;
    start = clock();
    populateLinkedList(&linkedListHead);
    end = clock();
    timeTaken = measureTimeTaken(start, end);
    printf("Time taken to populate linked list: %f seconds\n", timeTaken);

    // Task 10b: Inserting new entries into dynamic array
    start = clock();
    insertDynamicArray(dynamicArray, &numEntriesDynamicArray);
    end = clock();
    timeTaken = measureTimeTaken(start, end);
    printf("Time taken to insert new entries into dynamic array: %f seconds\n", timeTaken);

    // Task 10b: Inserting new entries into linked list
    start = clock();
    insertLinkedList(&linkedListHead);
    end = clock();
    timeTaken = measureTimeTaken(start, end);
    printf("Time taken to insert new entries into linked list: %f seconds\n", timeTaken);

    // Task 10c: Retrieving data from specified position in dynamic array
    int pos;
    printf("Enter position to retrieve data from dynamic array: ");
    scanf("%d", &pos);
    if (pos >= 0 && pos < numEntriesDynamicArray) {
        printf("Retrieved data from dynamic array: ID: %s, CGPA: %.2f\n", dynamicArray[pos].id, dynamicArray[pos].cgpa);
    } else {
        printf("Invalid position entered.\n");
    }

    // Task 10c: Retrieving data from specified position in linked list
    printf("Enter position to retrieve data from linked list: ");
    scanf("%d", &pos);
    ListNode* current = linkedListHead;
    int count = 0;
    while (current != NULL && count < pos) {
        current = current->next;
        count++;
    }
    if (current != NULL) {
        printf("Retrieved data from linked list: ID: %s, CGPA: %.2f\n", current->data.id, current->data.cgpa);
    } else {
        printf("Invalid position entered.\n");
    }

    // Task 10d: Deleting entries from dynamic array
    start = clock();
    numEntriesDynamicArray = 0; // Resetting number of entries to simulate deletion
    end = clock();
    timeTaken = measureTimeTaken(start, end);
    printf("Time taken to delete entries from dynamic array: %f seconds\n", timeTaken);

    // Task 10d: Deleting entries from linked list
    start = clock();
    freeLinkedList(linkedListHead); // Freeing memory to simulate deletion
    end = clock();
    timeTaken = measureTimeTaken(start, end);
    printf("Time taken to delete entries from linked list: %f seconds\n", timeTaken);

    return 0;
}