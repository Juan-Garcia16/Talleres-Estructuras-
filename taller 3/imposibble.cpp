#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define myPositiveInfinite 2147483647
#define myNegativeInfinite -2147483647
#define MAXN 100
//#define MAXN 1000000000

int Parent(int i){
    return i/2;
}

int Left(int i){
    return i*2;
} 

int Right(int i){
    return 2*i + 1;
}

void Minheapify(int Q[], int i, int heapSize){
    int l, r, least, temp;

    l = Left(i);
    r = Right(i);
    if (l <= heapSize && Q[l] < Q[i])
        least = l;
    else
        least = i;

    if (r <= heapSize && Q[r] < Q[least])
        least = r;
    
    if (least != i)
    {
        temp = Q[i];
        Q[i] = Q[least];
        Q[least] = temp;

        Minheapify(Q, least, heapSize);
    }
}

void MinPQ_DecreaseKey(int Q[], int i, int key){
    int temp;

    if (key > Q[i])
        printf("New key is higher than current\n");
    else
    {
        Q[i] = key;
        while (i > 1 && Q[Parent(i)] > Q[i]) //i llega a la raiz, por lo cual termina el intercambio
        {
            temp = Q[i];
            Q[i] = Q[Parent(i)];
            Q[Parent(i)] = temp;
            i = Parent(i);
        }
        
    }

}

int MinPQ_Extract(int Q[], int *heapSize){
    int min = myNegativeInfinite;

    if (*heapSize < 1)
        printf("Error: Heap underflow.\n");
    else
    {
        min = Q[1];
        Q[1] = Q[*heapSize];
        *heapSize = *heapSize - 1;
        Minheapify(Q, 1, *heapSize);
    }

    return min;
}

void MinPQ_Insert(int Q[], int key, int *heapSize){
    *heapSize = *heapSize + 1;
    Q[*heapSize] = myPositiveInfinite;
    MinPQ_DecreaseKey(Q, *heapSize, key);
}


int main(){
    int n, IDnumber[MAXN + 1], element, heapSize = 0, reference, min, found = 0;
    
    while(scanf("%d", &n) && n != EOF)
    {
        for (int i = 1; i < n; i++)
        {
            scanf("%d", &element);
            MinPQ_Insert(IDnumber, element, &heapSize);
        }

        reference = IDnumber[1];

        for (int i = 1; i < n ; i++)
        {
            min = MinPQ_Extract(IDnumber, &heapSize);

            if (min == reference)
                reference++;
            else
            {
                found = 1;
                break;
            }
        }

        if (found == 0)
            printf("IMPOSSIBLE\n");
        else
            printf("%d\n", reference);
        
        while (heapSize > 0)
        {
            MinPQ_Extract(IDnumber, &heapSize);
        }
        
        found = 0;
        reference = 0;
    }
    return 0;
}



