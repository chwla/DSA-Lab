#include <stdio.h>
#include <stdlib.h>

typedef struct node* NODE;
struct node{
    int ele;
    NODE next;
};

typedef struct linked_list* LIST;
struct linked_list{
    int count;
    NODE head;
};

LIST createNewList() {
    LIST myList = (LIST) malloc(sizeof(struct linked_list));
    if (myList == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    myList->count = 0;
    myList->head = NULL;
    return myList;
}

NODE createNewNode(int value) {
    NODE myNode = (NODE) malloc(sizeof(struct node));
    if (myNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    myNode->ele = value;
    myNode->next = NULL;
    return myNode;
}

void insertAfter(int searchEle, NODE newNode, LIST myList) {
    if (myList->head == NULL) {
        printf("List is empty. Inserting at the beginning.\n");
        myList->head = newNode;
    } else {
        NODE temp = myList->head;
        while (temp != NULL && temp->ele != searchEle) {
            temp = temp->next;
        }
        if (temp == NULL) {
            printf("Element %d not found in the list. Inserting at the end.\n", searchEle);
            temp = myList->head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        } else {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
    myList->count++;
}

void insertFirst(int value, LIST myList) {
    NODE newNode = createNewNode(value);
    newNode->next = myList->head;
    myList->head = newNode;
    myList->count++;
}

void deleteAt(int position, LIST myList) {
    if (myList->head == NULL || position < 0 || position >= myList->count) {
        printf("Invalid position. Nothing to delete.\n");
        return;
    }
    NODE temp = myList->head;
    if (position == 0) {
        myList->head = temp->next;
        free(temp);
    } else {
        for (int i = 0; temp != NULL && i < position - 1; i++) {
            temp = temp->next;
        }
        if (temp == NULL || temp->next == NULL) {
            printf("Invalid position. Nothing to delete.\n");
            return;
        }
        NODE nextNode = temp->next->next;
        free(temp->next);
        temp->next = nextNode;
    }
    myList->count--;
}

void deleteFirst(LIST myList) {
    deleteAt(0, myList);
}

int search(int data, LIST myList) {
    NODE temp = myList->head;
    int position = 0;
    while (temp != NULL) {
        if (temp->ele == data) {
            return position;
        }
        temp = temp->next;
        position++;
    }
    return -1;
}

void printList(LIST myList) {
    NODE temp = myList->head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d ", temp->ele);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(LIST myList) {
    NODE temp = myList->head;
    while (temp != NULL) {
        NODE nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
    free(myList);
}

int main() {
    LIST myList = createNewList();

    insertAfter(2, createNewNode(3), myList);
    insertFirst(1, myList);
    insertAfter(3, createNewNode(4), myList);
    printList(myList);

    int position = search(3, myList);
    if (position != -1) {
        printf("Element 3 found at position %d.\n", position);
    } else {
        printf("Element 3 not found in the list.\n");
    }

    deleteAt(1, myList);
    printList(myList);

    deleteFirst(myList);
    printList(myList);

    freeList(myList);

   
}