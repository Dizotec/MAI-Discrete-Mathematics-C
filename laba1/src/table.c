#include <stdio.h>

int calc(char converted_formula[256] , int values[26]);

void create_table(int count, char seen_letters[count + 1], char converted_formula[256]) {
    int values[26] = {0}; 
    int total_rows = 1;

    for (int i = 0; i < count; i++) {
        total_rows *= 2;
        printf("%c ", seen_letters[i]);
    }
    printf("| F\n");

    for (int row = 0; row < total_rows; row++) {
        int number = row;

        for (int i = count - 1; i >= 0; i--) {
            values[seen_letters[i] - 'a'] = number % 2;
            number /= 2;
        }

        for (int i = 0; i < count; i++) {
            printf("%d ", values[seen_letters[i] - 'a']);
        }

   
        int result = calc(converted_formula, values);
        printf("| %d\n", result);
        
    }
    printf("\n");
}
