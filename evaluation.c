#include <string.h>
#include <ctype.h>  

int apply_operation(char op, int a, int b) {
    switch (op) {
        case '&': return a && b;         
        case '|': return a || b;         
        case '^': return a != b;         
        case '=': return a == b;         
        case '>': return !a || b;        
        case '<': return a && !b;        
        case '+': return !(a || b);      // Стрелка Пирса (ИЛИ-НЕ)
        case '/': return !(a && b);      // Штрих Шеффера (И-НЕ)
        default: return 0;
    }
}

// Функция вычисления 
int evaluate_line(const char *original_formula, char *var_names, int n_vars, int *current_values) {
    char temp_formula[256];
    strcpy(temp_formula, original_formula);

    //Заменяю буквы на 0 и 1 из нашего набора
    for (int i = 0; temp_formula[i] != '\0'; i++) {
        if (isalpha(temp_formula[i])) {
            for (int v = 0; v < n_vars; v++) {
                if (var_names[v] == temp_formula[i]) {
                    temp_formula[i] = current_values[v] ? '1' : '0';
                    break;
                }
            }
        }
    }

    
    int val_stack[256]; // Стэк данных
    char op_stack[256]; // Стэк операций
    int val_top = -1;
    int op_top = -1;

    for (int i = 0; temp_formula[i] != '\0'; i++) {
        char c = temp_formula[i];

        if (c == ' ' || c == '\n' || c == '\r') continue;

        if (c == '0' || c == '1') {
            val_stack[++val_top] = c - '0'; // Стэк данных
        } 
        else if (c == '(') {
            op_stack[++op_top] = c;         
        } 
        else if (c == ')') {
            // Если закрывающая скобка — считаем всё внутри скобок, пока не дойдем до '('
            while (op_top >= 0 && op_stack[op_top] != '(') {
                char op = op_stack[op_top--];
                if (op == '!') { // Унарная операция (НЕ)
                    val_stack[val_top] = !val_stack[val_top];
                } else {         // Бинарные операции
                    int b = val_stack[val_top--];
                    int a = val_stack[val_top--];
                    val_stack[++val_top] = apply_operation(op, a, b);
                }
            }
            if (op_top >= 0) op_top--; // Выкидываю саму '(' из стэка
        } 
        else {
            /* Если это знак операции (!, &, |, ^, =, >, <, +, /)
            Перед тем как положить его, нужно выполнить всё унарное (отрицания)*/ 
            while (op_top >= 0 && op_stack[op_top] == '!') {
                char op = op_stack[op_top--];
                val_stack[val_top] = !val_stack[val_top];
            }
            op_stack[++op_top] = c; 
        }
    }

    // Досчитываю то, что осталось в стеках после прохода 
    while (op_top >= 0) {
        char op = op_stack[op_top--];
        if (op == '!') {
            val_stack[val_top] = !val_stack[val_top];
        } else {
            int b = val_stack[val_top--];
            int a = val_stack[val_top--];
            val_stack[++val_top] = apply_operation(op, a, b);
        }
    }

    return val_stack[val_top]; 
}
