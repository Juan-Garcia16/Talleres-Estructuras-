#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node{
    int key;
    struct node *next;
};

//Insertar elemento a una lista Circular Simplemente Enlazada.
struct node *InsertElementInCircularLinkedList(struct node *tail, int element){
    struct node *newNode;
    newNode = (struct node *) malloc(sizeof (struct node)); 
    newNode->key = element;
    
    if (tail == NULL)
    {
        newNode->next = newNode;
        tail = newNode;
    }
    
    else
    {
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }
    
    return tail;
}

//Borrar el primer nodo de una lista Circular Simplemente Enlazada.
struct node *DeleteFirstNodeOfCircularLinkedList(struct node *tail){
    struct node *firstNode;
    
    if (tail == NULL)
        printf("The circular linked list is empty.\n");
    else
    {
        if(tail == tail->next)
        {
            free(tail);
            tail = NULL;
        }
        
        else
        {
            firstNode = tail->next;
            tail->next = firstNode->next;
            free(firstNode);
        }
    }
    
    return tail;
}

int MCD(int a, int b) {
    while (b != 0) 
    {
        int residuo = a % b;
        a = b;
        b = residuo;
    }
    return a;
}

int main(){
    struct node *tail, *sheet, *student, *deleteStudent;
    int n, t, mcd;
    /*
    sheet: hoja que se esta pasando
    student: estudiante que recibe la hoja para comparar el MCD de la hoja con su propio numero
    deleteStudent: puntero que sigue student para cuando sea necesario eliminar a student
    */

    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        tail = NULL;
        scanf("%d", &n);

        for (int j = 2; j <= n; j++)
            tail = InsertElementInCircularLinkedList(tail, j);

        sheet = tail->next;
        student = sheet->next;
        deleteStudent = sheet;
        while (tail != tail->next)
        {
            mcd = MCD(sheet->key, student->key);

            if (mcd > 1)
            {
                student = student->next->next;
                tail = DeleteFirstNodeOfCircularLinkedList(deleteStudent);
                sheet = tail->next;
                deleteStudent = sheet;
            }
            else
            {
                deleteStudent = deleteStudent->next;
                student = student->next;
            }
            
        }

        printf("%d\n", tail->key);
    
        free(tail);
        
    }

    return 0;
}