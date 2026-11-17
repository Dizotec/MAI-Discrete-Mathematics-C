#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int calc(char *converted_formula, int values[26]);
char *join_expr(const char *left, char op, const char *right) {
    size_t size = strlen(left) + strlen(right) + 4;
    char *result = malloc(size);
    snprintf(result, size, "(%s%c%s)", left, op, right);
    return result;
}
char *make_not(const char *expr, char basis) {
    return join_expr(expr, basis, expr);
}
char *make_and(const char *left, const char *right, char basis) {
    if (basis == '$') {
        char *not_left = make_not(left, basis);
        char *not_right = make_not(right, basis);

        char *result = join_expr(not_left, basis, not_right);

        free(not_left);
        free(not_right);
        return result;
    } else {
        char *temp = join_expr(left, basis, right);
        char *result = make_not(temp, basis);

        free(temp);
        return result;
    }
}
char *make_or(const char *left, const char *right, char basis) {
    if (basis == '$') {
        char *temp = join_expr(left, basis, right);
        char *result = make_not(temp, basis);

        free(temp);
        return result;
    } else {
        char *not_left = make_not(left, basis);
        char *not_right = make_not(right, basis);

        char *result = join_expr(not_left, basis, not_right);

        free(not_left);
        free(not_right);
        return result;
    }
}
char *make_xor(const char *left, const char *right, char basis) {
    char *not_left = make_not(left, basis);
    char *not_right = make_not(right, basis);

    char *first = make_and(left, not_right, basis);
    char *second = make_and(not_left, right, basis);

    char *result = make_or(first, second, basis);

    free(not_left);
    free(not_right);
    free(first);
    free(second);

    return result;
}
char *make_binary(const char *left, char op,
                  const char *right, char basis) {
    char *temp;
    char *result;

    switch (op) {
        case '&':
            return make_and(left, right, basis);

        case '|':
            return make_or(left, right, basis);

        case '^':
            return make_xor(left, right, basis);

        case '/':
            temp = make_and(left, right, basis);
            result = make_not(temp, basis);
            free(temp);
            return result;

        case '$':
            temp = make_or(left, right, basis);
            result = make_not(temp, basis);
            free(temp);
            return result;

        case '=':
            temp = make_xor(left, right, basis);
            result = make_not(temp, basis);
            free(temp);
            return result;

        case '<':
            temp = make_not(left, basis);
            result = make_or(temp, right, basis);
            free(temp);
            return result;

        case '>':
            temp = make_not(right, basis);
            result = make_and(left, temp, basis);
            free(temp);
            return result;
    }

    return NULL;
}
char *convert_basis(char *formula, char basis) {
    char **stack = malloc((strlen(formula) + 1) * sizeof(char *));
    int top = 0;

    char letter[2] = {'a', '\0'};

    for (int i = 0; formula[i] != '\0'; i++) {
        if (formula[i] >= 'a' && formula[i] <= 'z') {
            letter[0] = formula[i];
            break;
        }
    }

    for (int i = 0; formula[i] != '\0'; i++) {
        char c = formula[i];

        if (c >= 'a' && c <= 'z') {
            stack[top] = malloc(2);
            stack[top][0] = c;
            stack[top][1] = '\0';
            top++;
        }
        else if (c == '0' || c == '1') {
            char *opposite = make_not(letter, basis);

            if (c == '0') {
                stack[top] = make_and(letter, opposite, basis);
            } else {
                stack[top] = make_or(letter, opposite, basis);
            }

            free(opposite);
            top++;
        }
        else if (c == '!') {
            char *old = stack[top - 1];
            stack[top - 1] = make_not(old, basis);
            free(old);
        }
        else {
            char *right = stack[--top];
            char *left = stack[--top];

            stack[top] = make_binary(left, c, right, basis);
            top++;

            free(left);
            free(right);
        }
    }

    char *result = stack[0];
    free(stack);
    return result;
}
void zhegalkin(int count, char *seen_letters, char *formula) {
    int total_rows = 1;
    int values[26] = {0};

    for (int i = 0; i < count; i++) {
        total_rows *= 2;
    }

    int *coeff = malloc(total_rows * sizeof(int));


    for (int row = 0; row < total_rows; row++) {
        int number = row;

        for (int i = count - 1; i >= 0; i--) {
            values[seen_letters[i] - 'a'] = number % 2;
            number /= 2;
        }

        coeff[row] = calc(formula, values);
    }


    for (int step = 1; step < total_rows; step *= 2) {
        for (int start = 0; start < total_rows; start += step * 2) {
            for (int j = 0; j < step; j++) {
                coeff[start + step + j] ^= coeff[start + j];
            }
        }
    }


    printf("Zhegalkin: ");
    int printed = 0;

    for (int term = 0; term < total_rows; term++) {
        if (coeff[term] == 0) {
            continue;
        }

        if (printed > 0) {
            printf(" ^ ");
        }

        if (term == 0) {
            printf("1");
        } else {
            int divisor = total_rows / 2;
            int letters_printed = 0;

            printf("(");
            for (int i = 0; i < count; i++) {
                if ((term / divisor) % 2 == 1) {
                    if (letters_printed > 0) {
                        printf(" & ");
                    }
                    printf("%c", seen_letters[i]);
                    letters_printed++;
                }

                divisor /= 2;
            }
            printf(")");
        }

        printed++;
    }

    if (printed == 0) {
        printf("0");
    }

    printf("\n");
    free(coeff);
}
void polynomial(int count ,char  seen_letters[count+1] ,char converted_formula[256]){
    printf("PDNF (if it exists) closes 1 task\nPierce's arrow:\n");
    char *result = convert_basis(converted_formula, '$');
    printf("NOR: %s\n", result);
    free(result);

    result = convert_basis(converted_formula, '/');
    printf("NAND: %s\n", result);
    zhegalkin(count, seen_letters, converted_formula);
    free(result);
}