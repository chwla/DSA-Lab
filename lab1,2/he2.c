#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct for hotel occupants
struct Occupant {
    char name[50];
    int age;
    char address[100];
};

// Define a struct for the hotel metadata
struct Hotel {
    char name[50];
    char address[100];
    int rooms_occupied;
    struct Occupant *occupants; // Dynamic array to hold occupants
};

// Function prototypes
void assignRoom(struct Hotel *hotel, const char *name, int age, const char *address);
void assignRoomToFirstVisitor(struct Hotel *hotel, const char *name, int age, const char *address);
void emptyRoom(struct Hotel *hotel, int room_number);
void displayVisitorInfo(struct Hotel *hotel, int room_number);

int main() {
    // Initialize The Grand Hotel
    struct Hotel grand_hotel;
    strcpy(grand_hotel.name, "The Grand Hotel");
    strcpy(grand_hotel.address, "123 Main Street");
    grand_hotel.rooms_occupied = 0;
    grand_hotel.occupants = NULL; // Initialize occupants array to NULL

    int choice;
    do {
        // Display menu
        printf("\nMenu:\n");
        printf("1. Assign a room to a new visitor\n");
        printf("2. Assign Room #0 to a new visitor\n");
        printf("3. Empty a room\n");
        printf("4. Display information of a visitor by room number\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char name[50], address[100];
                int age;
                printf("Enter visitor's name: ");
                scanf("%s", name);
                printf("Enter visitor's age: ");
                scanf("%d", &age);
                printf("Enter visitor's address: ");
                scanf("%s", address);
                assignRoom(&grand_hotel, name, age, address);
                break;
            }
            case 2: {
                char name[50], address[100];
                int age;
                printf("Enter visitor's name: ");
                scanf("%s", name);
                printf("Enter visitor's age: ");
                scanf("%d", &age);
                printf("Enter visitor's address: ");
                scanf("%s", address);
                assignRoomToFirstVisitor(&grand_hotel, name, age, address);
                break;
            }
            case 3: {
                int room_number;
                printf("Enter room number to empty: ");
                scanf("%d", &room_number);
                emptyRoom(&grand_hotel, room_number);
                break;
            }
            case 4: {
                int room_number;
                printf("Enter room number to display visitor information: ");
                scanf("%d", &room_number);
                displayVisitorInfo(&grand_hotel, room_number);
                break;
            }
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    // Free allocated memory
    free(grand_hotel.occupants);

    return 0;
}

void assignRoom(struct Hotel *hotel, const char *name, int age, const char *address) {
    // Allocate memory for occupants array
    if (hotel->occupants == NULL) {
        hotel->occupants = (struct Occupant *)malloc(sizeof(struct Occupant));
    } else {
        hotel->occupants = (struct Occupant *)realloc(hotel->occupants, (hotel->rooms_occupied + 1) * sizeof(struct Occupant));
    }

    // Assign values to the new occupant
    strcpy(hotel->occupants[hotel->rooms_occupied].name, name);
    hotel->occupants[hotel->rooms_occupied].age = age;
    strcpy(hotel->occupants[hotel->rooms_occupied].address, address);

    // Increment the number of occupied rooms
    hotel->rooms_occupied++;
}

void assignRoomToFirstVisitor(struct Hotel *hotel, const char *name, int age, const char *address) {
    // Shift existing occupants to make room for the new occupant
    if (hotel->rooms_occupied > 0) {
        hotel->occupants = (struct Occupant *)realloc(hotel->occupants, (hotel->rooms_occupied + 1) * sizeof(struct Occupant));
        for (int i = hotel->rooms_occupied - 1; i >= 0; i--) {
            hotel->occupants[i + 1] = hotel->occupants[i];
        }
    }

    // Assign values to the new occupant
    strcpy(hotel->occupants[0].name, name);
    hotel->occupants[0].age = age;
    strcpy(hotel->occupants[0].address, address);

    // Increment the number of occupied rooms
    hotel->rooms_occupied++;
}

void emptyRoom(struct Hotel *hotel, int room_number) {
    // Validate room number
    if (room_number < 0 || room_number >= hotel->rooms_occupied) {
        printf("Invalid room number!\n");
        return;
    }

    // Shift occupants behind the emptied room
    for (int i = room_number; i < hotel->rooms_occupied - 1; i++) {
        hotel->occupants[i] = hotel->occupants[i + 1];
    }

    // Decrement the number of occupied rooms
    hotel->rooms_occupied--;

    // Reallocate memory for occupants array
    if (hotel->rooms_occupied == 0) {
        free(hotel->occupants);
        hotel->occupants = NULL;
    } else {
        hotel->occupants = (struct Occupant *)realloc(hotel->occupants, hotel->rooms_occupied * sizeof(struct Occupant));
    }
}

void displayVisitorInfo(struct Hotel *hotel, int room_number) {
    // Validate room number
    if (room_number < 0 || room_number >= hotel->rooms_occupied) {
        printf("Invalid room number!\n");
        return;
    }

    // Display visitor information for the specified room
    printf("Visitor information for Room #%d:\n", room_number);
    printf("Name: %s\n", hotel->occupants[room_number].name);
    printf("Age: %d\n", hotel->occupants[room_number].age);
    printf("Address: %s\n", hotel->occupants[room_number].address);
}