#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
void create_table(int count ,char  seen_letters[count+1] ,char converted_formula[256]);
void pdnf_pcnf(int count ,char  seen_letters[count+1] ,char converted_formula[256]);
void fictitious_vars(int count ,char  seen_letters[count+1] ,char converted_formula[256]);
void polynomial(int count ,char  seen_letters[count+1] ,char converted_formula[256]);
char *  to_RPN( char formula[256]);
void parser(const char *path) {
    FILE *file = fopen(path, "r");

    char *formula = malloc(256);
    if (formula == NULL) {
        printf("Memory error\n");
        fclose(file);
        return;
    }
    fgets(formula , 256,file); 
    printf("There is your test -> %s\n", formula );   
    // tolower 
    for (char* i = formula ; *i != '\0';i++){
        *i = tolower(*i);
    }
    int seen[26] = {0};
    int count = 0 ;
    for (char* i = formula ; *i != '\0';i++){
        if( isalpha(*i)) {
            int index = *i - 'a';
            
            if (seen[index]==0) {
            count ++;
            seen[index]=1;
            }
        }
    }
    printf("letters encountered: %d\n", count);
    char *seen_letters = malloc(count+1);
    if (seen_letters == NULL) {
        printf("Memory error\n");
        free(formula);
        fclose(file);
        return;
    }
    int k = 0; 
    for (int i = 0 ; i < 26; i++){
        if (seen[i] == 1){
            seen_letters[k] =  'a' +  i;
            k++;
        }
    }
    seen_letters[k] = '\0';
    
    char * converted_formula = to_RPN( formula);
    fclose(file);
    if (converted_formula == NULL) {
        printf("Memory error\n");
        free(formula);
        free(seen_letters);
        return;
    }
    create_table(count , seen_letters,converted_formula);
    pdnf_pcnf(count , seen_letters,converted_formula);
    fictitious_vars(count , seen_letters,converted_formula);
    polynomial(count , seen_letters,converted_formula);
    free(converted_formula);
    free(seen_letters);
    free(formula);
}
