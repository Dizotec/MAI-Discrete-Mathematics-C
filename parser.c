#include <stdio.h>
#include <ctype.h>

int evaluate_line(const char *original_formula, char *var_names, int n_vars, int *current_values);

void run_logic_analysis(char *path) {
    path = "test.txt";
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Failed to open the file \n");
        return;
    }

    printf("File is open !\n");

    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file) != NULL){
        for (int i = 0; buffer[i] != '\0'; i++){
            buffer[i] = tolower(buffer[i]);
        }
    }
    // считаю кол-во переменных 
    int seen_vars[26] = {0};
    int index;
    for (int i = 0; buffer[i] != '\0'; i++){
        if (isalpha(buffer[i])){
            index = buffer[i] - 'a';
            seen_vars[index] = 1; 
        }
    }
    
    char var_names[26]; 
    int N_seen_vars = 0;

    
    for (int i = 0; i < 26; i++) {
        if (seen_vars[i] == 1) {
            var_names[N_seen_vars] = 'a' + i; // Записали букву 
            N_seen_vars++;                     // Посчитали её 
        }
    }

    // таблица истинности 
    printf("\n--- Truth Table ---\n");

    
    for (int i = 0; i < N_seen_vars; i++) {
        printf("%c\t", var_names[i]);
    }
    printf("| F\n");

    
    for (int i = 0; i < N_seen_vars; i++) printf("--------");
    printf("+\n");
    
    
    int total_rows = 1 << N_seen_vars; // сдвиг 1 на переменную по сути даёт степень двойки 
    for (int row = 0; row < total_rows; row++) {
        int current_values[N_seen_vars]; 
        for (int v = 0; v < N_seen_vars; v++) {
            // цикл отсчитывает сколько переменных мы уже посмотрели и насколько нужно сделать сдвиг 
            int bit = (row >> (N_seen_vars - 1 - v)) & 1; // row и так ведёт счёт от 0 до 2 ^ n , достаточно представить в нужном виде  (& 1 берёт последний символ)
            current_values[v] = bit; 
            printf("%d\t", bit);
        }
        
        int f_res = evaluate_line(buffer,var_names,N_seen_vars,current_values);
        printf("| %d\n", f_res);

    }

    printf("F: %s \nN of vars: %d\n", buffer, N_seen_vars);
    
    fclose(file);
}
