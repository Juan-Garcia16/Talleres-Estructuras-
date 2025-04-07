#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define myPositiveInfinite 2147483647
#define myNegativeInfinite -2147483647
#define MAXN 500001

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
    int dataMin[MAXN + 1], dataMax[MAXN + 1], n, i, element, heapSizeMin = 0, heapSizeMax = 0, temp;
    double mean;
    long long int median;

    while (scanf("%d", &n) && n > 0)
    {
        median = 0;
        for(i = 1; i <= n; i++)
        {
            scanf("%d", &element);

            if (heapSizeMax == 0 || element <= (-1 * dataMax[1]))
                MinPQ_Insert(dataMax, -1*element, &heapSizeMax);
            else
                MinPQ_Insert(dataMin, element, &heapSizeMin);
        
            if (heapSizeMax > heapSizeMin + 1)
            {
                temp = -1 * MinPQ_Extract(dataMax, &heapSizeMax);
                MinPQ_Insert(dataMin, temp, &heapSizeMin);
            }
            else if(heapSizeMin > heapSizeMax)
            {
                temp = MinPQ_Extract(dataMin, &heapSizeMin);
                MinPQ_Insert(dataMax, -1 * temp, &heapSizeMax);
            }
            
            median += -1 * dataMax[1];
        }

        mean = (double)median / n;
        printf("%.2lf\n", mean);
        
        while (heapSizeMax > 0)
        {
            MinPQ_Extract(dataMax, &heapSizeMax);
        }
        while (heapSizeMin > 0)
        {
            MinPQ_Extract(dataMin, &heapSizeMin);
        }
    }
    return 0;
}
