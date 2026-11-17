#include <stdio.h>

int calc(char converted_formula[256], int values[26]);

void fictitious_vars(int count, char seen_letters[count + 1], char converted_formula[256]) {
    int values[26] = {0};
    int total_rows = 1;
    int found = 0;

    for (int i = 0; i < count; i++) {
        total_rows *= 2;
    }

    printf("Fictitious variables: ");

  
    for (int v = 0; v < count; v++) {
        int index = seen_letters[v] - 'a';
        int is_fictitious = 1;

    
        for (int row = 0; row < total_rows; row++) {
            int number = row;

            for (int i = count - 1; i >= 0; i--) {
                values[seen_letters[i] - 'a'] = number % 2;
                number /= 2;
            }

            int before = calc(converted_formula, values);

         
            values[index] = !values[index];
            int after = calc(converted_formula, values);
            values[index] = !values[index];

            if (before != after) {
                is_fictitious = 0;
                break;
            }
        }

        if (is_fictitious) {
            printf("%c ", seen_letters[v]);
            found = 1;
        }
    }

    if (!found) {
        printf("none");
    }
    printf("\n");
}
