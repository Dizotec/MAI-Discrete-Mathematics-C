#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>



int priority(char c){
    switch (c){
        case '!' : return 5; 
        case '&' : return 4;
        case '|' : return 3; 
        case '/' : return 4; // Шиффер 
        case '^' : return 3; // XOR  
        case '$' : return 3;  // Пирс
        case '<' : return 2; // импликация 
        case '>' : return 2; // коимпликация
        case '=' : return 1; 
        default: return -1;
    }
}
char * to_RPN(char *formula){
   
    // ОПН не длиннее исходной формулы; оставляем место для конца строки.
    size_t capacity = strlen(formula) + 1;
    char *result = malloc(capacity);
    char *operation_stack = malloc(capacity);
    if (result == NULL || operation_stack == NULL) {
        free(result);
        free(operation_stack);
        return NULL;
    }
    size_t operatots_count = 0 ;

    size_t count_recorded = 0;
    for (char * c = formula;* c != '\0'; c++) {
        if (isalpha((unsigned char)*c) || (*c=='0') || (*c=='1')){
            result[count_recorded] = *c;
            count_recorded++;
        }
        else if (isspace((unsigned char)*c)) {
            continue; 
        }
        else if (*c == '(') {
            operation_stack[operatots_count] = *c;
            operatots_count++;
        }
        else if (*c== ')') {
            while (operation_stack[operatots_count-1] != '(') {
                operatots_count --;
                result[count_recorded]=operation_stack[operatots_count];
                count_recorded++;
            }
            operatots_count --;
        } 
        else if (*c == '!') {
            operation_stack[operatots_count] = *c;
            operatots_count++;
        }
        else {
            char lasting = *c ;
            
            while (operatots_count >0 &&  operation_stack[operatots_count-1] != '(' && priority(operation_stack[operatots_count-1]) >= priority(*c)){
                
                operatots_count --;
                result[count_recorded] = operation_stack[operatots_count];
                count_recorded++;
                

            }
            operation_stack[operatots_count] = *c;
            operatots_count ++;
           
        }
        

  
    }
    while (operatots_count >0) {
    operatots_count --;
    result[count_recorded] = operation_stack[operatots_count];
    count_recorded++;
            
    }
    result[count_recorded] = '\0';
    
    free(operation_stack);
    // result освободит parser после всех вычислений.
    return result;
}