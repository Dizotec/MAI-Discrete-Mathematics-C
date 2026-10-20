#include <stdio.h>
#include <locale.h>
void run_logic_analysis(char *path);

int main(void) {    
    char path[256];
    setlocale(LC_ALL,"Russian");
    printf("Enter path: ");
    if (scanf("%255s", path) != 1) {
        printf("Path error.\n");
        return 1;
    }
    run_logic_analysis(path);
    return 0;
}
