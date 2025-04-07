#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define myInfinite "zzzzzzzzzz"
#define MAXN 1000000

typedef struct {
    char numero [15];

} nombres;

void myMerge (nombres A[], int p, int q, int r) {
    int i, j, k;
    int n1 = q - p + 1;
    int n2 = r - q; 
    nombres L[n1 + 2], R[n2 + 2];

    for (i = 1; i <= n1; i++) 
        L[i] = A[p + i - 1];

    for (j = 1; j <= n2; j++)
        R[j] = A[q + j];

    strcpy (L[n1 + 1].numero, myInfinite);
    strcpy (R[n2 + 1].numero, myInfinite);

    i = 1; 
    j = 1;

    for (k = p; k <= r; k++) {
        if (strcmp (L[i].numero, R[j].numero) <= 0) {
            A[k] = L[i];
            i++;
        }
        else {
            A[k] = R[j];
            j++;
        }
    }
}

void mergeSort (nombres A[], int p, int r) {
    int q;
    if (p < r) {
        q = (p + r) / 2;
        mergeSort (A, p, q);
        mergeSort (A, q + 1, r);
        myMerge (A, p, q, r);
    }
}

int binarySearch (nombres A[], int i, int j, char k[]) {

    int m;
    if (i > j) {
        return -1 * i - 1;
    }
    else {
        m = (i + j)/2;
        if (strcmp (A[m].numero, k) == 0) {
            return m;
        }
        else {
            if (strcmp (A[m].numero, k) < 0)
                return binarySearch (A, m + 1, j, k);
            else
                return binarySearch (A, i, m - 1, k);
        }
    }
}

int main () {
    int n, q, LimiteIzquierdo, LimiteDerecho, numeroPalabras;
    char aux[15], inferior[15], superior[15];
    nombres diccionario[MAXN + 1];

    scanf ("%d %d", &n, &q);

    for (int i = 1; i <= n; i++) {
        scanf ("%s", aux);
        strcpy (diccionario[i].numero, aux);
    }

    mergeSort (diccionario, 1, n);

    for (int consulta = 0; consulta < q; consulta++) {
        scanf("%s %s", inferior, superior);

        LimiteIzquierdo = binarySearch(diccionario, 0, n, inferior);
        LimiteDerecho = binarySearch(diccionario, 0, n , superior);

        if (LimiteIzquierdo < 0)
            LimiteIzquierdo = -1 * LimiteIzquierdo - 1;

        if (LimiteDerecho < 0)
            LimiteDerecho = -1 * LimiteDerecho - 2;

        numeroPalabras = LimiteDerecho - LimiteIzquierdo + 1;
        printf("%d\n", numeroPalabras);
    }

    return 0;
}