#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


int calc(char *converted_formula, int values[26]){
    size_t capacity = strlen(converted_formula) + 1;
    if (capacity > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Formula is too long.\n");
        exit(EXIT_FAILURE);
    }
    int *stack = malloc(capacity * sizeof(*stack));
    if (stack == NULL) {
        fprintf(stderr, "Cannot allocate calculation stack.\n");
        exit(EXIT_FAILURE);
    }
    size_t stack_index = 0;
    for (char* c = converted_formula; *c !='\0' ;c++ ) {

        if (isalpha((unsigned char)*c)) {
            stack[stack_index] = values[*c-'a'];
            stack_index++;  
        }
        else if (*c == '!') {
            stack[stack_index-1] = !(stack[stack_index-1] );
            
        }
        else if (*c=='1' || *c=='0') {
            stack[stack_index] = *c- '0';
            stack_index++;  
        }
        else {
            stack_index--;
            int f_op = stack[stack_index];
            stack_index--;
            int s_op =  stack[stack_index];
            int result ; 
            switch (*c) {
                
                case '&' :{result = s_op && f_op; break;}
                case '|' :{result = s_op || f_op; break; }
                case '/' :{result = !(s_op && f_op) ;break;} // Шиффер 
                case '^' :{result = !(s_op == f_op) ;break;} // XOR  
                case '$' :{result = !(s_op || f_op) ;break;}  // Пирс
                case '<' :{result = s_op <= f_op; break;} // импликация 
                case '>' :{result = s_op > f_op ;break; }// коимпликация
                case '=' :{result = s_op == f_op; break;} 
                
            }
            stack[stack_index] = result ;
            stack_index++;

        }
    }
    // Сохраняем ответ до освобождения массива.
    int result = stack[0];
    free(stack);
    return result;
}