#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXN 100000
#define BLACK 0
#define GRAY 1
#define WHITE 2
#define NIL -1
#define RED 1
#define BLACK 0
#define NILKey "zzzzzzzzzz"
#define MAXS 12

struct student
{
    char name[MAXS];
    int maxH;
};

struct edge
{
    int vertex;
/*  int weight;  */
    struct edge *next;
};

struct graph
{
    int n_vertex; //cuantos vertices tiene
    int m_edges; //cuantas arista tiene
    struct edge *Adj[MAXN + 1]; //arreglo punteros de lista de adyascencia
};

struct nodeRBTree
{
    char key[MAXS];
    int color;
    int position;
    struct nodeRBTree *left;
    struct nodeRBTree *right;
    struct nodeRBTree *p;
};

void myMerge (char A[MAXN + 1][12], int p, int q, int r) {
    int n1 = q - p + 1, n2 = r - q, i, j, k;
    char L[n1+2][11], R[n2+2][11];
    
    for (i = 1; i <= n1; i++) strcpy(L[i], A[p+i-1]);

    for (j = 1; j <= n2; j++) strcpy(R[j], A[q+j]);

    strcpy(L[n1+1], NILKey);
    strcpy(R[n2+1], NILKey);
    i = 1;
    j = 1;

    for(k = p; k <= r; k++) {
        
        int cmp = strcmp(L[i], R[j]);
        
        if (cmp <= 0) {
            strcpy(A[k], L[i]);
            i++;
        } else {
            strcpy(A[k], R[j]);
            j++;
        }
    }
}

void MergeSort (char A[MAXN + 1][12], int p, int r) {
    int q;
    if (p < r) {
        q =  (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        myMerge(A, p, q, r); 
    }
}

void InorderTreeWalk(struct nodeRBTree *x)
{
    if (strcmp(x->key, NILKey) != 0)
    {
        InorderTreeWalk(x->left);
        if (x->color == BLACK)
            printf("( %s, %d BLACK ) ", x->key, x->position);
        else
            printf("( %s, %d RED ) ", x->key, x->position);
        InorderTreeWalk(x->right);
    }
}

struct nodeRBTree *TreeSearch(struct nodeRBTree *x, char kName[])
{
    while ((strcmp(x->key, NILKey) != 0) && (strcmp(kName, x->key) != 0))
    {
        if (strcmp(kName, x->key) < 0)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

struct nodeRBTree *TreeMinimum(struct nodeRBTree *x)
{
    while (strcmp(x->left->key, NILKey) != 0)
        x = x->left;
    return x;
}

struct nodeRBTree *TreeMaximum(struct nodeRBTree *x)
{
    while (strcmp(x->right->key, NILKey) != 0)
        x = x->right;
    return x;
}

struct nodeRBTree *TreeSuccessor(struct nodeRBTree *x)
{
    struct nodeRBTree *y;
    if (strcmp(x->right->key, NILKey) != 0)
        return TreeMinimum(x->right);
    y = x->p;
    while ((strcmp(y->key, NILKey) != 0) && (x == y->right))
    {
        x = y;
        y = y->p;
    }
    return y;
}

struct nodeRBTree *TreePredecessor(struct nodeRBTree *x)
{
    struct nodeRBTree *y;
    if (strcmp(x->left->key, NILKey) != 0)
        return TreeMaximum(x->left);
    y = x->p;
    while ((strcmp(y->key, NILKey) != 0) && (x == y->left))
    {
        x = y;
        y = y->p;
    }
    return y;
}

struct nodeRBTree *LeftRotate(struct nodeRBTree *T, struct nodeRBTree *x)
{
    struct nodeRBTree *y;
    y = x->right;
    x->right = y->left;
    y->left->p = x;
    y->p = x->p;
    if (strcmp(x->p->key, NILKey) == 0)
        T = y;
    else
    {
        if (x == x->p->left)
            x->p->left = y;
        else
            x->p->right = y;
    }
    y->left = x;
    x->p = y;
    return T;
}

struct nodeRBTree *RightRotate(struct nodeRBTree *T, struct nodeRBTree *x)
{
    struct nodeRBTree *y;
    y = x->left;
    x->left = y->right;
    y->right->p = x;
    y->p = x->p;
    if (strcmp(x->p->key, NILKey) == 0)
        T = y;
    else
    {
        if (x == x->p->right)
            x->p->right = y;
        else
            x->p->left = y;
    }
    y->right = x;
    x->p = y;
    return T;
}

struct nodeRBTree *AssignNilLeaf()
{
    struct nodeRBTree *w;
    w = (struct nodeRBTree *)malloc(sizeof(struct nodeRBTree));
    w->color = BLACK;
    strcpy(w->key, NILKey);
    w->position = -1;
    w->left = NULL;
    w->right = NULL;
    return w;
}

struct nodeRBTree *RB_InsertFixup(struct nodeRBTree *T, struct nodeRBTree *z)
{
    struct nodeRBTree *y;
    while (z->p->color == RED)
    {
        if (z->p == z->p->p->left)
        {
            y = z->p->p->right;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if (z == z->p->right)
                {
                    z = z->p;
                    T = LeftRotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                T = RightRotate(T, z->p->p);
            }
        }
        else
        {
            y = z->p->p->left;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if (z == z->p->left)
                {
                    z = z->p;
                    T = RightRotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                T = LeftRotate(T, z->p->p);
            }
        }
    }
    T->color = BLACK;
    return T;
}

struct nodeRBTree *RB_Insert(struct nodeRBTree *T, char kName[], int position)
{
    struct nodeRBTree *x, *y, *z;
    z = (struct nodeRBTree *)malloc(sizeof(struct nodeRBTree));
    z->color = RED;
    strcpy(z->key, kName);
    z->position = position;
    z->left = AssignNilLeaf();
    z->left->p = z;
    z->right = AssignNilLeaf();
    z->right->p = z;

    
    if (strcmp(T->key, NILKey) != 0)
        y = T->p;
    else
        y = T;
    x = T;
    while (strcmp(x->key, NILKey) != 0)
    {
        y = x;
        if (strcmp(z->key, x->key) < 0)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if (strcmp(y->key, NILKey) == 0)
        T = z; /* Empty tree . */
    else
    {
        free(x);
        if (strcmp(z->key, y->key) < 0)
            y->left = z;
        else
            y->right = z;
    }
    T = RB_InsertFixup(T, z);
    return T;
}

struct nodeRBTree *RB_DeleteFixup(struct nodeRBTree *T, struct nodeRBTree *x)
{
    struct nodeRBTree *w;
    while ((x != T) && (x->color == BLACK))
    {
        if (x == x->p->left)
        {
            w = x->p->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                T = LeftRotate(T, x->p);
                w = x->p->right;
            }
            if ((w->left->color == BLACK) && (w->right->color == BLACK))
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    T = RightRotate(T, w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                T = LeftRotate(T, x->p);
                x = T;
            }
        }
        else
        {
            w = x->p->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                T = RightRotate(T, x->p);
                w = x->p->left;
            }
            if ((w->right->color == BLACK) && (w->left->color == BLACK))
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    T = LeftRotate(T, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                T = RightRotate(T, x->p);
                x = T;
            }
        }
    }
    x->color = BLACK;
    return T;
}

struct nodeRBTree *RB_Delete(struct nodeRBTree *T, struct nodeRBTree *z)
{
    struct nodeRBTree *x, *y;
    if ((strcmp(z->left->key, NILKey) == 0) || (strcmp(z->right->key, NILKey) == 0))
        y = z;
    else
        y = TreeSuccessor(z);
    if (strcmp(y->left->key, NILKey) != 0)
        x = y->left;
    else
        x = y->right;
    x->p = y->p;
    if (strcmp(y->p->key, NILKey) == 0)
        T = x;
    else
    {
        if (y == y->p->left)
            y->p->left = x;
        else
            y->p->right = x;
    }
    if (y != z)
    {
        strcpy(z->key, y->key);
        z->position = y->position;
        /* Copy all information fields from y to z. */
    }
    if (y->color == BLACK)
        T = RB_DeleteFixup(T, x);
    if (y == y->left->p)
        free(y->left);
    if (y == y->right->p)
        free(y->right);
    free(y);
    return T;
}

struct graph *ReadGraph(int vertices, int edges, struct nodeRBTree *T)
{
    int idVertex, idEdge, u, v; //vertice u, vertice v
    struct graph *G;
    struct edge *tempEdge; //arista temporal para moverse recorriendo la lista de adyascencua
    char uStudent[MAXS], vStudent[MAXS];
    struct nodeRBTree *z;

    G = (struct graph *) malloc(sizeof(struct graph));
    G->n_vertex = vertices; //total vertices
    G->m_edges = edges; //total aristas

    for(idVertex = 1; idVertex <= G->n_vertex; idVertex++)
        G->Adj[idVertex] = NULL; 

    for(idEdge = 1; idEdge <= G->m_edges; idEdge++)
    {   
        //busqueda en el arbol de los estudiantes a relacionar para poder mapearlos segun sus vertices asignados en el grafo
        scanf("%s %s", uStudent, vStudent);
        z = TreeSearch(T, uStudent);
        u = z->position;
        z = TreeSearch(T, vStudent);
        v = z->position;

        tempEdge = (struct edge *) malloc(sizeof(struct edge));
        tempEdge->vertex = v; // a donde esta llegando
        tempEdge->next = G->Adj[u]; //siemrpe todo se va metiendo en la cabeza de la lista
        G->Adj[u] = tempEdge; //actualizar la cabeza de la lista

        if(u != v) //si son diferentes, se inserta la lista que va de v a u
        {
            tempEdge = (struct edge *) malloc(sizeof(struct edge));
            tempEdge->vertex = u;
            tempEdge->next = G->Adj[v];
            G->Adj[v] = tempEdge; //lista de adyascencia vertice v
        }
    }
    return G; //puntero al padre
}

struct graph *DeleteGraph(struct graph *G)
{
    int idVertex;
    struct edge *ActualEdge, *NextEdge;

    for(idVertex = 1; idVertex <= G->n_vertex; idVertex++)
    {
        ActualEdge = G->Adj[idVertex]; //cabeza de la lsita
        while(ActualEdge != NULL)
        {
            NextEdge = ActualEdge->next;
            free(ActualEdge);
            ActualEdge = NextEdge;
        }
    }
    free(G);
    G = NULL;
    return G;
}

void DFS_Visit(struct graph *G, int u, int *time, int color[], int pi[], int d[], int f[], struct student temp[],int *indexMax)
{
    struct edge *tempEdge; //para recorrer la lista de adyasencia
    int v;

    if(temp[*indexMax].maxH < temp[u].maxH) //obtener el #vertice del estudiante que trabaja mas horas en el arbol
        *indexMax = u;

    color[u] = GRAY;
    *time = *time + 1;
    d[u] = *time;
    tempEdge = G->Adj[u];

    while (tempEdge != NULL)
    {
        v = tempEdge->vertex;
        if (color[v] == WHITE)
        {
            pi[v] = u;
            DFS_Visit(G, v, &(*time), color, pi, d, f, temp,indexMax);
        }
        tempEdge = tempEdge->next;
    }
    color[u] = BLACK;
    *time = *time + 1;
    f[u] = *time;
    
}

void DFS(struct graph *G, int color[], int pi[], int d[], int f[], struct student temp[],int i)
{
    //indexMax para guardar la posicion de los esclavos de cada arbol en relacion con el arreglo de estudiantes
    int u, time = 0, indexMax, indexSlaves = 0;
    char slaves[MAXN + 1][MAXS];

    for (u = 1; u <= G->n_vertex; u++)
    {
        color[u] = WHITE;
        pi[u] = NIL;
    }
    
    printf("Case %d:\n", i);
    for (u = 1; u <= G->n_vertex; u++)
    {
        if (color[u] == WHITE){
            indexMax = u;
            DFS_Visit(G, u, &time, color, pi, d, f, temp, &indexMax); 
            strcpy(slaves[indexSlaves], temp[indexMax].name);
            indexSlaves++;
        }    
    }
    MergeSort(slaves, 0, indexSlaves - 1);
    for (int j = 0; j < indexSlaves; j++)
        printf("%s\n", slaves[j]);
}

void solver(struct graph *G, struct student temp[], int i)
{
    //color, padres, descubiertos, finalizados
    int color[MAXN + 1], pi[MAXN + 1], d[MAXN + 1], f[MAXN + 1];
    DFS(G, color, pi, d, f, temp, i);
}

int main()
{
    int t, N, M, maxH;
    char name[MAXS];
    struct graph *G;
    struct student temp[MAXN + 1];
    struct nodeRBTree *T = AssignNilLeaf();

    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        scanf("%d %d", &N, &M);
        for (int j = 1; j <= N; j++)
        {
            scanf("%s %d", name, &maxH);
            strcpy(temp[j].name, name);
            temp[j].maxH = maxH;
            T = RB_Insert(T, name, j);
        }

        G = ReadGraph(N, M, T);
        solver(G, temp, i);
        G = DeleteGraph(G);
        while (strcmp(T->key, NILKey) != 0) //Limpiar el arbol
            T = RB_Delete(T, T);
    }
    return 0;
}