#include <stdio.h>

void parser(const char * path);

int main(void) {
    // Ввод Пути 
    char path[256] ;
    printf("Enter the path to your's formula -> \n");
    //scanf("%s",&path);
    char path1[256] = "test.txt";
    parser(path1);
    
    return 0;
}
