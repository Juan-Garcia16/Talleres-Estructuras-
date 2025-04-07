#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXN 2000000
#define infinity 2147483647

int collection[MAXN + 1];

int BinarySearch(int A[], int i, int j, int k) {
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

int BinarySearchFirstOccurrence(int A[], int i, int j, int k) {
    int result, result2;
    result = BinarySearch(A, i, j, k);
    
    if (result >= 0) {
        result2 = BinarySearch(A, i, result - 1, k);
        while (result2 >= 0) {
            result = result2;
            result2 = BinarySearch(A, i, result - 1, k);
        }
    }
    return result;
}

int BinarySearchLastOccurrence(int A[], int i, int j, int k) {
    int result, result2;
    result = BinarySearch(A, i, j, k);

    if (result >= 0) {
        result2 = BinarySearch(A, result + 1, j, k);
        while (result2 >= 0) {
            result = result2;
            result2 = BinarySearch(A, result + 1, j, k);
        }
    }
    return result;
}

void myMerge (int A[], int p, int q, int r) {
    int n1 = q - p + 1, n2 = r - q, i, j, k;
    int L[n1+2], R[n2+2];
    
    for (i = 1; i <= n1; i++) L[i] = A[p+i-1];

    for (j = 1; j <= n2; j++) R[j] = A[q+j];

    L[n1+1] = infinity;
    R[n2+1] = infinity;
    i = 1;
    j = 1;

    for(k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}

void MergeSort (int A[], int p, int r) {
    int q;
    if (p < r) {
        q =  (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        myMerge(A, p, q, r); 
    }
}

int InsertarElemento(int k, int conjunto[], int n) {
    int posicion = BinarySearch(conjunto, 1, n, k), agregado = 0;
    
    if (posicion < 0) {
        posicion = (-1) * posicion - 1;
        
        if (posicion > n) {
            conjunto[n + 1] = k;
            agregado = 1;
        } else {
            conjunto[posicion] = k;
        }
    }    
    return agregado;
}

int main() {
    int conjunto[MAXN + 1], n, q, a, b, k, opcion, i;
    int consulta, nuevoTamano, izquierda, derecha, resultado;
    
    scanf("%d %d", &n, &q);
    
    for (i = 1; i <= n; i++)
        scanf("%d", &conjunto[i]);    
        
    MergeSort(conjunto, 1, n);
        
    for (consulta = 1; consulta <= q; consulta++) {
        
        scanf("%d", &opcion);
        
        if (opcion == 1) {
            scanf("%d", &k);
            nuevoTamano = InsertarElemento(k, conjunto, n);
            if (nuevoTamano == 1)
                n++;    
        } else {
            scanf("%d %d", &a, &b);
            izquierda = BinarySearchFirstOccurrence(conjunto, 1, n, a);
            derecha = BinarySearchLastOccurrence(conjunto, 1, n, b);
            
            if (izquierda < 0)
                izquierda = -1 * izquierda -1;
            
            if (derecha < 0)
                derecha = -1 * derecha - 2;
        
            resultado = derecha - izquierda + 1;
            
            printf("%d\n", resultado);   
        }
    }  
    return 0;
}