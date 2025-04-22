#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

struct node
{
    int key;
    struct node *next;
};

void printQueue(struct node *tail)
{
    struct node *currentNode;
    if (tail == NULL)
    
        printf("NULL\n");
    
    else
    {
        currentNode = tail->next;
        while (currentNode != tail)
        {
            printf("%d -> ", currentNode->key);
            currentNode = currentNode->next;
        }
        printf("%d \n", tail->key);
    }
}

struct node *enqueue(struct node *tail, int element)
{
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = element;
    if (tail == NULL)
    {
        newNode->next = newNode;
        return newNode;
    }
    else
    {
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }
    return tail;
}

int dequeue(struct node **tail)
{
    struct node *firstNode;
    int element;
    if (*tail == (*tail)->next)
    {
        element = (*tail)->key;
        free(*tail);
        *tail = NULL;
    }
    else
    {
        firstNode = (*tail)->next;
        element = firstNode->key;
        (*tail)->next = firstNode->next;
        free(firstNode);
    }
    return element;
}

int queueEmpty(struct node *tail)
{
    return tail == NULL ? TRUE : FALSE;
}

int main()
{
    struct node *tail;
    int t, q, v, element, suma;

    scanf("%d", &t);
    while (t > 0)
    {
        tail = NULL;
        suma = 0;
        scanf("%d", &q);

        while (q > 0)
        {
            scanf("%d", &v);
            if (v == 1)
            {
                scanf("%d", &element);
                tail = enqueue(tail, element);
                suma += element;
            }
            else if (v == 2)
            {
                if (queueEmpty(tail) == 0)
                {
                    element = dequeue(&tail);
                    suma -= element;
                }
            }
            else if (v == 3)
            {
                if (queueEmpty(tail) == 1)
                
                    printf("Empty!\n");
                
                else
                
                    printf("%d\n", suma);
                
            }
            q--;
        }
        while (queueEmpty(tail) == 0)
        
            dequeue(&tail);
        
        free(tail);

        t--;
    }

    return 0;
}