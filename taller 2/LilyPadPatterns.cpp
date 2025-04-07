#include <stdio.h>
#define MAX 1200000

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

int main(){
    int n, liriosOcupados[MAX + 1], liriosLibres[MAX + 1], lirioFaltante, contador = 1, q, rana;

    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d ", &liriosOcupados[i]);
    
    scanf("%d", &q);
    
    for (int i = 1; i <= MAX + 1; i++)
    {
        lirioFaltante = BinarySearch(liriosOcupados, 1, n + 1, i);

        if (lirioFaltante < 0)
        {
            liriosLibres[contador] = i;
            contador++;
        }
        
    }

    for (int i = 1; i <= q; i++)
    {
        scanf("%d", &rana);

        int lirioConRana = liriosOcupados[rana];

        int lirioCercano = BinarySearch(liriosLibres, 1, contador - 1, lirioConRana);
        lirioCercano = -1 * lirioCercano - 1;

        int LirioVacio = liriosLibres[lirioCercano];

        liriosOcupados[rana] = LirioVacio;
        liriosLibres[lirioCercano] = lirioConRana;

        printf("%d\n", liriosOcupados[rana]);
    }

    return 0;
}