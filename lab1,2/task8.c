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

void printList(LIST myList) {
    NODE temp = myList->head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d ", temp->ele);
        temp = temp->next;
    }
    printf("\n");
}


void rotate(LIST myList, int k) {
    if (myList->head == NULL || myList->head->next == NULL || k == 0) {
        return;
    }

    int length = 1;
    NODE last = myList->head;
    NODE value = myList->head;

    while (last->next != NULL) {
        length++;
        last = last->next;
    }

    if (length < k) {
        return;
    }

    for(int i=0; i<(length-k-1); i++){
        value = value->next;
    }

    last->next = myList->head;
    myList->head = value->next;
    value->next = NULL; // This line sets the next pointer of the node pointed to by value to NULL. This step is crucial for ensuring 
                    //that the new last node's next pointer is set to NULL, effectively marking the end of the rotated list

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
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    myList->count = 5;

    printf("Linked list before rotation:\n");
    printList(myList);

    int k;
    printf("Enter the value of k: ");
    scanf("%d", &k);

    rotate(myList, k);

    printf("\nLinked list after rotation with k = %d:\n", k);
    printList(myList);

    return 0;
}