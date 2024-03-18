#include <stdio.h>
#include <stdlib.h>

typedef struct node* NODE;
struct node{
    int ele;
    NODE next;
    NODE prev;
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

void printList(LIST myList) {
    NODE temp = myList->head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d ", temp->ele);
        temp = temp->next;
    }
    printf("\n");
}

void reverse(LIST myList) {
    NODE current = myList->head;
    NODE prevNode = NULL;
    NODE nextNode = NULL;

    while (current != NULL) {
        // Store the next node
        nextNode = current->next;

        // Reverse the links
        current->next = prevNode;
        current->prev = nextNode;

        // Move pointers forward
        prevNode = current;
        current = nextNode;
    }

    // Update the head pointer to point to the last node
    myList->head = prevNode;
}


int main() {
    LIST myList = createNewList();

    NODE node1 = createNewNode(1);
    NODE node2 = createNewNode(2);
    NODE node3 = createNewNode(3);
    NODE node4 = createNewNode(4);
    NODE node5 = createNewNode(5);

    myList->head = node1;
    node1->next = node2;
    node2->prev = node1;
    node2->next = node3;
    node3->prev = node2;
    node3->next = node4;
    node4->prev = node3;
    node4->next = node5;
    myList->count = 5;

    printf("Linked list before rotation:\n");
    printList(myList);

    reverse(myList);

    printf("\n Reversed linked list:\n");
    printList(myList);

    return 0;
}