#include <stdio.h>
#include <ctype.h>
void run_logic_analysis(char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Failed to open the file \n");
        return;
    }

    printf("File is open !\n");


    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file) != NULL){
        for (int i =0 ; buffer[i] != '\0';i++){
            buffer[i] = tolower(buffer[i]);
        }
    }
    int seen_vars[26]= {0};
    for (int i = 0; buffer[i]!='\0';i++){
        
    }
    printf(buffer);
    fclose(file);
}   