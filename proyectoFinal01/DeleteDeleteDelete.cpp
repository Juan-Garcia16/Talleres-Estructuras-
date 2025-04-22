#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1000006
#define TRUE 1
#define FALSE 0

struct node {
    char key;
    struct node *next;
};

// Insercion usando punteros a head y tail
void InsertNode(struct node **head, struct node **tail, char letra) {
    
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    
    newNode->key = letra;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } 
    else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

struct node *DeleteConsecutiveRepeatedLetters(struct node *head) {
    if (head == NULL) return NULL;

    struct node *current = head;

    while (current != NULL && current->next != NULL) {
        if (current->key == current->next->key) {
            struct node *temp = current->next;
            current->next = temp->next;
            free(temp);
        } else {
            current = current->next;
        }
    }

    return head;
}

struct node *DeleteExtremeSpaces(struct node *head) {
    while (head != NULL && head->key == ' ') {
        struct node *temp = head;
        head = head->next;
        free(temp);
    }

    if (head == NULL) return NULL;

    struct node *current = head;
    struct node *prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    if (current->key == ' ') {
        prev->next = NULL;
        free(current);
    }

    return head;
}

void PrintList(struct node *head) {
    while (head != NULL) {
        printf("%c", head->key);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct node *head = NULL;
    struct node *tail = NULL;
    char word1[MAXN], word2[40];
    int lettersToDelete[256] = {0};

    fgets(word1, sizeof(word1), stdin);
    fgets(word2, sizeof(word2), stdin);

    word1[strcspn(word1, "\n")] = '\0';
    word2[strcspn(word2, "\n")] = '\0';

    for (int i = 0; word1[i] != '\0'; i++) {
        InsertNode(&head, &tail, word1[i]);
    }

    for (int i = 1; word2[i] != ']'; i++) {
        lettersToDelete[(int)word2[i]] = TRUE;
    }

    // Borrar letras
    struct node *current = head;
    struct node *prev = NULL;

    while (current != NULL) {
        if (lettersToDelete[(int)current->key]) {
            struct node *temp = current;
            //Condicional para ver si el que se debe borrar es la cabeza.
            if (prev == NULL) {
                head = current->next;
                current = head;
            } 
            //Eliminar cualquier otro nodo que no sea la cabeza.
            else {
                prev->next = current->next;
                current = current->next;
            }
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }

    head = DeleteConsecutiveRepeatedLetters(head);
    head = DeleteExtremeSpaces(head);

    PrintList(head);

    // Liberar memoria
    current = head;
    while (current != NULL) {
        struct node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

