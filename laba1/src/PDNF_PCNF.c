#include <stdio.h>

int calc(char converted_formula[256], int values[26]);

void pdnf_pcnf(int count, char seen_letters[count + 1], char converted_formula[256]) {
    int values[26] = {0};
    int total_rows = 1;

    for (int i = 0; i < count; i++) {
        total_rows *= 2;
    }

    for (int target = 1; target >= 0; target--) {
        int groups = 0;

        if (target == 1) {
            printf("PDNF: ");
        } else {
            printf("PCNF: ");
        }

        if (count == 0) {
            printf("cannot build: formula has no variables (F = %d).\n",
                   calc(converted_formula, values));
            continue;
        }

        for (int row = 0; row < total_rows; row++) {
            int number = row;

            for (int i = count - 1; i >= 0; i--) {
                values[seen_letters[i] - 'a'] = number % 2;
                number /= 2;
            }

            int result = calc(converted_formula, values);
            if (result != target) {
                continue;
            }

            if (groups > 0) {
                if (target == 1) {
                    printf(" | ");
                } else {
                    printf(" & ");
                }
            }

            printf("(");
            for (int i = 0; i < count; i++) {
                if (i > 0) {
                    if (target == 1) {
                        printf(" & ");
                    } else {
                        printf(" | ");
                    }
                }

                if (values[seen_letters[i] - 'a'] != target) {
                    printf("!");
                }
                printf("%c", seen_letters[i]);
            }
            printf(")");
            groups++;
        }

        if (groups == 0) {
            if (target == 1) {
                printf("cannot build: function is always 0.");
            } else {
                printf("cannot build: function is always 1.");
            }
        }
        printf("\n");
    }
}
