#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE *fptr1, *fptr2;
    char *line = NULL;
    size_t bufsize = 0;

    fptr1 = fopen("test1.txt", "r");
    fptr2 = fopen("test2.txt", "w");
    
    if(fptr1 == NULL){
        printf("Error opening file");
        return 1;
    }
    while(getline(&line, &bufsize, fptr1) != -1){
        
        fprintf(fptr2, "%s",line);
    }
    fclose(fptr1);
    fclose(fptr2);

    fptr1 = fopen("test1.txt", "w");
    fclose(fptr1);

    return 0;
}