#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXV 10000
#define myInfinite 2147483647
#define NIL -1
#define TRUE 1
#define FALSE 0

struct edge
{
    int vertex;
    int weight;
    int active; // Nuevo campo: 1 arista activa, 0 inactiva.
    struct edge *next;
};

struct graph
{
    int n_vertex;
    int m_edges;
    struct edge *Adj[MAXV + 1];
};

struct nodePQ
{
    int vertex;
    int distance;
};

int Parent(int i)
{
    return i >> 1; // return i / 2;
}

int Left(int i)
{
    return i << 1; // return 2 * i;
}

int Right(int i)
{
    return (i << 1) + 1; // return 2 * i + 1;
}

void MinHeapify(struct nodePQ Q[], int i, int heapSize, int positionVertex[])
{
    int l, r, least, tempPosition;
    struct nodePQ tempNode;
    l = Left(i);
    r = Right(i);

    if((l <= heapSize) && (Q[l].distance < Q[i].distance))
        least = l;
    else
        least = i;

    if((r <= heapSize) && (Q[r].distance < Q[least].distance))
        least = r;

    if(least != i)
    {
        tempPosition = positionVertex[Q[i].vertex];
        tempNode = Q[i];

        positionVertex[Q[i].vertex] = positionVertex[Q[least].vertex];
        Q[i] = Q[least];

        positionVertex[Q[least].vertex] = tempPosition;
        Q[least] = tempNode;

        MinHeapify(Q, least, heapSize, positionVertex);
    }
}

int MinPQ_Extract(struct nodePQ Q[], int *heapSize, int positionVertex[])
{
    int myMin = 0;

    if(*heapSize >= 1)
    {
        myMin = Q[1].vertex;

        positionVertex[Q[*heapSize].vertex] = 1;
        Q[1] = Q[*heapSize];

        *heapSize = *heapSize - 1;
        MinHeapify(Q, 1, *heapSize, positionVertex);
    }
    return myMin;
}

void MinPQ_DecreaseKey(struct nodePQ Q[], int i, int key, int positionVertex[])
{
    int tempPosition;
    struct nodePQ tempNode;

    if(key < Q[i].distance)
    {
        Q[i].distance = key;

        while((i > 1) && (Q[Parent(i)].distance > Q[i].distance))
        {
            tempPosition = positionVertex[Q[i].vertex];
            tempNode = Q[i];

            positionVertex[Q[i].vertex] = positionVertex[Q[Parent(i)].vertex];
            Q[i] = Q[Parent(i)];

            positionVertex[Q[Parent(i)].vertex] = tempPosition;
            Q[Parent(i)] = tempNode;

            i = Parent(i);
        }
    }
}

void MinPQ_Insert(struct nodePQ Q[], int key, int vertex, int *heapSize, int positionVertex[])
{
    *heapSize = *heapSize + 1;
    Q[*heapSize].distance = myInfinite; 
    Q[*heapSize].vertex = vertex;
    positionVertex[vertex] = *heapSize;
    MinPQ_DecreaseKey(Q, *heapSize, key, positionVertex);
}

struct graph *ReadGraph(int vertices, int edges)
{
    int idVertex, idEdge, u, v, w;
    struct graph *G;
    struct edge *tempEdge;

    G = (struct graph *) malloc(sizeof(struct graph));
    G->n_vertex = vertices;
    G->m_edges = edges;

    for(idVertex = 1; idVertex <= G->n_vertex; idVertex++)
        G->Adj[idVertex] = NULL;

    for(idEdge = 1; idEdge <= G->m_edges; idEdge++)
    {
        scanf("%d %d %d", &u, &v, &w);
        
        tempEdge = (struct edge *) malloc(sizeof(struct edge));
        tempEdge->vertex = v;
        tempEdge->weight = w;
        tempEdge->active = TRUE; //Inicializar como activa
        tempEdge->next = G->Adj[u];
        G->Adj[u] = tempEdge;

        if(u != v)
        {
            tempEdge = (struct edge *) malloc(sizeof(struct edge));
            tempEdge->vertex = u;
            tempEdge->weight = w;
            tempEdge->active = TRUE; //Inicializar como activa
            tempEdge->next = G->Adj[v];
            G->Adj[v] = tempEdge;
        }
    }
    return G;
}

struct graph *DeleteGraph(struct graph *G)
{
    int idVertex;
    struct edge *ActualEdge, *NextEdge;

    if (G == NULL) return NULL;

    for(idVertex = 1; idVertex <= G->n_vertex; idVertex++)
    {
        ActualEdge = G->Adj[idVertex];
        while(ActualEdge != NULL)
        {
            NextEdge = ActualEdge->next;
            free(ActualEdge);
            ActualEdge = NextEdge;
        }
    }
    free(G);
    return NULL;
}

void Prim(struct graph *G, int d[], int pi[], int s)
{
    int u, v, w, heapSize = 0;
    struct nodePQ Q[MAXV + 1];
    int positionVertex[MAXV + 1], inQueue[MAXV + 1];
    struct edge *tempEdge;
    
    // Inicializacion de d y pi para cada ejecucion de Prim
    for(u = 1; u <= G->n_vertex; u++)
    {
        pi[u] = NIL;
        inQueue[u] = TRUE;
        d[u] = myInfinite;
    }
    
    // Insertar todos los vertices en la cola de prioridad
    for(u = 1; u <= G->n_vertex; u++) {
        if (u == s) {
            MinPQ_Insert(Q, 0, s, &heapSize, positionVertex);
            d[s] = 0;
        } else {
            MinPQ_Insert(Q, myInfinite, u, &heapSize, positionVertex);
        }
    }

    while(heapSize >= 1)
    {
        u = MinPQ_Extract(Q, &heapSize, positionVertex);
        inQueue[u] = FALSE;

        if(d[u] == myInfinite)
            break; 

        tempEdge = G->Adj[u];
        while(tempEdge != NULL)
        {
            //Solo considerar aristas activas
            if (tempEdge->active == TRUE) { 
                v = tempEdge->vertex;
                w = tempEdge->weight;

                if((inQueue[v] == TRUE) && (d[v] > w))
                {
                    d[v] = w; 
                    pi[v] = u;
                    MinPQ_DecreaseKey(Q, positionVertex[v], d[v], positionVertex);
                }
            }
            tempEdge = tempEdge->next;
        }
    }
}

void MarkMSTEdgesInactive(struct graph *G, int d[], int pi[]) {
    int v_curr, u_parent;
    struct edge *tempEdge;

    for (v_curr = 1; v_curr <= G->n_vertex; v_curr++) {
    
        if (pi[v_curr] != NIL && d[v_curr] != myInfinite) {
            u_parent = pi[v_curr];
            int edge_weight = d[v_curr];

            // Buscar la arista (u_parent, v_curr) y marcarla
            tempEdge = G->Adj[u_parent];
            while (tempEdge != NULL) {
                if (tempEdge->vertex == v_curr && tempEdge->weight == edge_weight) {
                    tempEdge->active = FALSE; // Marcar como inactiva
                    break;
                }
                tempEdge = tempEdge->next;
            }

            // Buscar la arista (v_curr, u_parent) y marcarla
            tempEdge = G->Adj[v_curr];
            while (tempEdge != NULL) {
                if (tempEdge->vertex == u_parent && tempEdge->weight == edge_weight) {
                    tempEdge->active = FALSE; // Marcar como inactiva
                    break;
                }
                tempEdge = tempEdge->next;
            }
        }
    }
}

void solver(struct graph *G, int source)
{
    int d[MAXV + 1], pi[MAXV + 1], CountTrees = 0;
    long long VecWeightMST[MAXV + 1], current_mst_weight;

    while(TRUE) // Bucle principal para encontrar y eliminar MSTs
    {
        //Ejecutar Prim para encontrar el MST del grafo actual
        Prim(G, d, pi, source);

        //Calcular el peso del MST encontrado y verificar si todos los vertices fueron alcanzados
        int vertices_reached_by_prim = 0;
        int edges_in_current_mst = 0; // Contar las aristas que realmente se unieron al MST
        current_mst_weight = 0;

        for (int i = 1; i <= G->n_vertex; i++) {
            if (d[i] != myInfinite) { 
                vertices_reached_by_prim++;
            }
            if (pi[i] != NIL) { 
                edges_in_current_mst++;
                current_mst_weight += d[i];
            }
        }
        
        // Manejar el caso especial de un grafo con un solo vertice
        if (G->n_vertex == 1) {
            if (vertices_reached_by_prim == 1) { 
                current_mst_weight = 0; 
                CountTrees++;
                VecWeightMST[CountTrees] = current_mst_weight;
            }
            break;
        }

        if (edges_in_current_mst < (G->n_vertex - 1) || vertices_reached_by_prim < G->n_vertex) {
            break; // El grafo se ha desconectado
        }
        
        CountTrees++;
        VecWeightMST[CountTrees] = current_mst_weight;
        
        MarkMSTEdgesInactive(G, d, pi);
    }
    
    printf("%d\n", CountTrees);
    for(int i = 1; i <= CountTrees; i++)
    {
        printf("%lld\n", VecWeightMST[i]);
    }
}

int main()
{
    int vertices, edges, source = 1; 
    struct graph *G;
    
    scanf("%d %d", &vertices, &edges);
    G = ReadGraph(vertices, edges);  
    solver(G, source);   
    G = DeleteGraph(G); 
    return 0;
}