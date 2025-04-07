#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXN 1000000

int binarySearch(long long int A[], int i, int j, long long int k){
    int m, result = -1;

    while (i <= j) {
        m = (i + j) >> 1; 

        if (A[m] == k) {
            result = m;
            break;
        } else if (k > A[m]) {
            i = m + 1;
        } else {
            j = m - 1;
        }
    }

    if (result == -1)
        result = (-1) * i - 1;
    
    return result;
}

int main(){
    int acumulador[MAXN+1], n, i, count = 0, j = 0;
    long long int triangular[MAXN+1], result;

    // de esta forma se evita una multiplicacion y una division, por lo cual no es necesario un casting para el i*i
    for (i = 1; i <= MAXN; i++) {
        triangular[i] = triangular[i - 1] + i;
    }
    
    for (i = 2; i <= MAXN; i++)
    {   
        result = binarySearch(triangular, 1, MAXN, triangular[i] + triangular[i-1]);
        if (result > 0)
            j = result;  
        
        if (i == j)
        {
            count++;    
        }
        
        acumulador[i] = count;   
    }

    while (scanf("%d", &n) && n != 0)
    {
        printf("%d\n", acumulador[n]);
    }
    
    return 0;
}