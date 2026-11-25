#include <stdio.h>
#include <stdbool.h>  
#include <string.h>
void print_poly(unsigned int value);
unsigned int addition(unsigned int a, unsigned int b){
    return a ^ b;
}
unsigned int remainder_poly(unsigned int value  , unsigned int divisor , unsigned int d ){
    for (int i = 14  ;i >= d; i--){
        if (value & (1u << i)) {
            value ^= divisor << (i - d);
        }
    }
    return value;
}
unsigned int multiplyfication(unsigned int a, unsigned int b, unsigned int m){
    unsigned int result = 0;
    while (b !=0 ) {
        if (b &1){
            result ^=  a;
        }   
        b = b>>1;
        a = a<<1;
    }   
    
   
    for (int i = 14  ;i >= 8; i--){
        if (result & (1u << i)) {
            result ^= m << (i - 8);
        }
    }
    return remainder_poly(result, m, 8);
}
unsigned int reverse(unsigned int a, unsigned int m){
    if (!a) {
        puts("Reverse is not exist");
        return 0;
    }
    for (int b = 1 ; b < 256 ; b++){
        if (multiplyfication(a,b,m) == 1){
            return b;
        }
    }
    return 0;
}

void print_modules(){
    for (int m = 256 ; m < 512 ;m++) {
        bool has_divisor = 0;
        for (int divisor = 2 ; divisor< 32 ; divisor ++) {
            int tmp = divisor;
            int d = 0;
            while (tmp > 1) {
                tmp >>= 1;
                d++;
            }
            if (remainder_poly(m,divisor,d) == 0 ) {
                has_divisor = 1;
                break;
            }
        }
        if (has_divisor ==0) {
            print_poly(m);
            printf("\n");
    }
    
    }
}
void print_poly(unsigned int value) {
    if (value == 0) {
        printf("0");
        return;
    }
    if (value == 1) {
        printf("1");
        return;
    }
    unsigned int len =1;
    unsigned int tmp = value;
    unsigned short d = 0;
    while (tmp > 1) {
        tmp >>= 1;
        d++;
    }
    len += d;
    bool printed = false; 
    for (int i = len - 1 ; i>=0 ; i--){

        if (((value >> i)&1) == 1 ){
            if (printed) printf(" + ");
            if (i == 0) printf("1");
            else if (i == 1) printf("x");
            else printf("x^%d",i);
            printed = true; 
        }
    }
    
}
int main(){
    unsigned int a =(  1 << 3 ) | (  1 << 1 )  |  (  1 << 0 ) ;
    unsigned int b =  (  1 << 2 )  |  (  1 << 1 ); 
    unsigned int m = (1<<8) | (1 << 4) | (1 << 3) | ( 1 << 1) | (1 << 0); 
    printf("(a , b , m ) -> ");
    print_poly(a);
    printf("  ,  ");
    print_poly(b);
        printf("  , ");
    print_poly(m);
    
    printf("\n");
    printf("Addition (a,b):");
    print_poly(addition(a,b));
    printf("\n");
    printf("Multiplyfication (a,b) module \"m\":");
    print_poly(multiplyfication(a,b,m));
    printf("\n");
    printf("Reverse (a,m):");
    print_poly(reverse(a,m));
    printf("\n");
    print_modules();

    return 0;
}