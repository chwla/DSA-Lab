#include <stdio.h>
#include <stdlib.h>

static int size = 0;
static int n = 0;

char *end_arr(char arr[]) {
    char s;
    printf("Enter the string to add at the end: ");
    scanf(" %c", &s); // Added space before %c to consume newline
    if (size >= n) {
        arr = realloc(arr, (size + 1) * sizeof(char));
        if (arr == NULL) {
            printf("Memory reallocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    arr[size++] = s;
    return arr;
}

char *beg_arr(char arr[]) {
    char s;
    printf("Enter the character to add at the beginning: ");
    scanf(" %c", &s); // Added space before %c to consume newline

    for (int i = size; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = s;
    size++;
    return arr;
}

void del_arr(char arr[], int x) {
    if (x >= size || x < 0) {
        printf("Enter a valid size!");
    } else {
        for (int i = x; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }
}

void disp_arr(char arr[]) {
    for (int i = 0; i < size; i++) {
        printf("%c", arr[i]);
    }
}

int disp_len(char arr[]) {
    return size;
}

int main() {
    printf("Enter size: ");
    scanf("%d", &n);

    char *arr = (char *)malloc(n * sizeof(char));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        printf("Enter: ");
        scanf(" %c", &arr[i]); // Added space before %c to consume newline
        size++;
    }

    int choice;
    do {
        printf("\n1. Add a char to the end of the array\n");
        printf("2. Add a char to the beginning of the array\n");
        printf("3. Delete the element at index 'x' of the array\n");
        printf("4. Display the length of the array\n");
        printf("5. Display all the elements of the array in sequence\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                arr = end_arr(arr);
                break;
            case 2:
                arr = beg_arr(arr);
                break;
            case 3:
                int x;
                printf("Enter index: ");
                scanf("%d", &x);
                del_arr(arr, x);
                break;
            case 4:
                printf("Array length: %d\n", disp_len(arr));
                break;
            case 5:
                disp_arr(arr);
                printf("\n");
                break;
            case 6:
                free(arr);
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid choice\n");
        }
    } while (1);

    return 0;
}