#include <stdio.h>

int extended_gcd(int a, int b, int *x, int *y) {
    if (b ==0 ) {
        *x =1 ;
        *y = 0;
        return a ;  
    }
    if (b!=0) {
        int x1,y1 ;
        int g = extended_gcd(b,a % b , &x1,&y1);
        *x = y1;
        *y = x1 - (a / b ) * y1 ;
        return g; 
    }
}
int fast_pow(double a , unsigned int degree) {
    double result = 1;
    while (degree !=0) {
        if (degree % 2 !=0) {

            result *=a ;
        }
     
        a *=a; 
        degree /= 2 ;
    }
    if (degree == 0) return result;
    else return result *a;
}
int gcd(int a , int b) {
    if (a < 0 || b < 0) {
        return -1;
    }
    else {
        int tmp;
        while (b !=0) {
            tmp = a % b ;
            a = b;
            b = tmp  ;
            
        }
        return a;
    }
    
}
int inverse_mod(int a , int n) {
    if (n <= 0) return -1;
    int x,y ;
    int g = extended_gcd(a , n , &x,&y);
    if (g!=1) return -1;

    int r = x % n ;
    if (r < 0) r+=n;
    return r;
}
int mod_pow(unsigned int a , unsigned int degree, int m ) {
    long long result = 1 % m  ;
    while (degree !=0) {
        if (degree % 2 !=0) {

            result = (   result * a ) %m ;
        }
     
        a = (a * a ) % m; 
        degree /= 2 ;
    }
    if (degree == 0) return result;
    else return result *a;
}
int phi( int n ){
    int k =0;
    for (int i = 1 ; i<= n; i++) {
        if (gcd(i,n) == 1) k++;
    }
    return k;
}
int inverser_mod_pow(int a, int n){
    if (n <=0 || gcd(a,n)!=1) return -1;
    else return mod_pow(a,phi(n)-1,n); 
}

int main(){
    return 0;
}