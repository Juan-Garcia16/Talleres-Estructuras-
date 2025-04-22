#include <stdio.h>
#include <stdlib.h>
#define myPositiveInfinite 2147483647
#define myNegativeInfinite -2147483647
#define MAXN 10000

// Definicion de la estructura de un nodo para lista circular doblemente enlazada
struct node {
    int key;
    struct node *prev;
    struct node *next;
};

struct node *InsertElementInCircularDoublyLinkedList(struct node *tail, int element) {
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node)); 
    newNode->key = element;

    if (tail == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        tail = newNode;
    } else {
        newNode->next = tail->next;
        newNode->prev = tail;
        tail->next = newNode;
        newNode->next->prev = newNode;
        tail = newNode;
    }
    return tail;
}

struct node *DeleteFirstNodeOfCircularDoublyLinkedList(struct node *tail) {
    struct node *firstNode;
    
    if (tail == NULL)
        printf("The circular doubly linked list is empty.\n");
    else {
        if(tail == tail->next) {
            free(tail);
            tail = NULL;
        } else {
            firstNode = tail->next;
            tail->next = firstNode->next;
            firstNode->next->prev = tail;
            free(firstNode);
        }
    }
    return tail;
}

int Parent(int i) {
    return i / 2;
}

int Left(int i) {
    return i * 2;
}

int Right(int i) {
    return 2 * i + 1;
}

void Minheapify(int Q[], int i, int heapSize) {
    int l, r, least, temp;

    l = Left(i);
    r = Right(i);
    if (l <= heapSize && Q[l] < Q[i])
        least = l;
    else
        least = i;

    if (r <= heapSize && Q[r] < Q[least])
        least = r;

    if (least != i) {
        temp = Q[i];
        Q[i] = Q[least];
        Q[least] = temp;

        Minheapify(Q, least, heapSize);
    }
}

int MinPQ_Extract(int Q[], int *heapSize) {
    int min = myNegativeInfinite;

    if (*heapSize < 1)
        printf("Error: Heap underflow.\n");
    else {
        min = Q[1];
        Q[1] = Q[*heapSize];
        *heapSize = *heapSize - 1;
        Minheapify(Q, 1, *heapSize);
    }

    return min;
}

void MinPQ_DecreaseKey(int Q[], int i, int key) {
    int temp;

    if (key > Q[i])
        printf("New key is higher than current\n");
    else {
        Q[i] = key;
        while (i > 1 && Q[Parent(i)] > Q[i]) {
            temp = Q[i];
            Q[i] = Q[Parent(i)];
            Q[Parent(i)] = temp;
            i = Parent(i);
        }
    }
}

void MinPQ_Insert(int Q[], int key, int *heapSize) {
    *heapSize = *heapSize + 1;
    Q[*heapSize] = myPositiveInfinite;
    MinPQ_DecreaseKey(Q, *heapSize, key);
}

int main() {
    int n, r, c, i, indexR, indexC, pasosR, pasosC;
    int contratados[MAXN + 1], heapSize = 0, empleados;
    struct node *tail = NULL, *s1, *s2;

    while(scanf("%d %d %d", &n, &r, &c) != EOF) {
        for (i = 1; i <= n; i++)
            tail = InsertElementInCircularDoublyLinkedList(tail, i);

        s1 = tail->next;
        s2 = tail;

        while (n > 2) {
            
            if (r > n)
                pasosR = ((r - 1) % n) + 1;
            else
                pasosR = r;
            
            if (c > n)
                pasosC = ((c - 1) % n) + 1;
            else
                pasosC = c;

            for (indexR = 1; indexR < pasosR; indexR++)
                s1 = s1->next;

            for (indexC = 1; indexC < pasosC; indexC++)
                s2 = s2->prev;

            if ((s1->next == s2) && (s2->prev == s1)) { // nodos seguidos, con s1 atras de s2
                s2 = s2->prev->prev;   
                tail = s2;
                s1 = s1->next->next;
                tail = DeleteFirstNodeOfCircularDoublyLinkedList(tail);
                tail = DeleteFirstNodeOfCircularDoublyLinkedList(tail);
                n -= 2;
            } else if (s1 == s2) { // mismo nodo
                MinPQ_Insert(contratados, s1->key, &heapSize);
                s2 = s2->prev;
                s1 = s1->next;
                tail = s2;
                tail = DeleteFirstNodeOfCircularDoublyLinkedList(tail);
                n--;
            } else {
                s2 = s2->prev;
                tail = s2;
                tail = DeleteFirstNodeOfCircularDoublyLinkedList(tail);

                tail = s1->prev;
                s1 = s1->next;
                tail = DeleteFirstNodeOfCircularDoublyLinkedList(tail);
                
                n -= 2;
            }

            tail = s1; // para facilitar la eliminacion de la lista circular
        }

        while (tail != NULL) {
            MinPQ_Insert(contratados, tail->next->key, &heapSize);
            tail = DeleteFirstNodeOfCircularDoublyLinkedList(tail);
        }

        while (heapSize > 0) {
            empleados = MinPQ_Extract(contratados, &heapSize);
            printf("%d ", empleados);
        }
        printf("\n");
    }

    return 0;
}
