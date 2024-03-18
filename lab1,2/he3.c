#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    FILE *fh;
    char *line = NULL;
    size_t bufsize = 0;
    int count = 0;

    fh = fopen("LOTR.txt", "r");

    if(fh == NULL){

        printf("error");
    }
    else{
        while(getline(&line, &bufsize, fh) != -1) {

            if (strstr(line, "hobbit") || strstr(line, "Hobbit")) {
                count++;
            }
    }
        printf("%d", count); 

        free(line);
        fclose(fh);
    }
}