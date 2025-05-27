#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXW 1000
#define MAXH 1000
#define NIL -1
#define BLACK 0
#define GRAY 1
#define WHITE 2
#define myInfinite 2147483647

struct cell {
    int coord_x;
    int coord_y;
};

// Arreglos globales
char Maze[MAXH + 1][MAXW + 1];
int color[MAXH + 1][MAXW + 1];
int d[MAXH + 1][MAXW + 1];
int f[MAXH + 1][MAXW + 1];
struct cell pi[MAXH + 1][MAXW + 1];

void ReadMaze(int H, int W) {
    int idRow, idColumn;
    char line[MAXW + 1];
    for(idRow = 1; idRow <= H; idRow++) {
        scanf("%s", line);
        for(idColumn = 1; idColumn <= W; idColumn++)
            Maze[idRow][idColumn] = line[idColumn - 1];
    }
}

void assignMovements(struct cell arrayMov[]) {
    
    arrayMov[0].coord_x = 0;
    arrayMov[0].coord_y = 0;
    
    arrayMov[1].coord_x = 0;
    arrayMov[1].coord_y = -1;
    
    arrayMov[2].coord_x = 0;
    arrayMov[2].coord_y = 1;
    
    arrayMov[3].coord_x = -1;
    arrayMov[3].coord_y = 0;
    
    arrayMov[4].coord_x = 1;
    arrayMov[4].coord_y = 0;
}

struct cell BFS_Maze(int W, int H, struct cell s) {
    int idRow, idColumn, idHead = 1, idTail = 1, idMovement;
    struct cell NilFather, Q[(MAXH * MAXW) + 5], u, v, movements[5];

    assignMovements(movements);
    NilFather.coord_x = NIL;
    NilFather.coord_y = NIL;

    for(idRow = 1; idRow <= H; idRow++) {
        for(idColumn = 1; idColumn <= W; idColumn++) 
        {
            color[idRow][idColumn] = WHITE;
            d[idRow][idColumn] = myInfinite;
            pi[idRow][idColumn] = NilFather;
        }
    }

    color[s.coord_y][s.coord_x] = GRAY;
    d[s.coord_y][s.coord_x] = 0;
    pi[s.coord_y][s.coord_x] = NilFather;
    Q[idTail++] = s;

    while(idHead < idTail) {
        u = Q[idHead++];
        for(idMovement = 1; idMovement <= 4; idMovement++) 
        {
            v.coord_x = u.coord_x + movements[idMovement].coord_x;
            v.coord_y = u.coord_y + movements[idMovement].coord_y;
            if(v.coord_x >= 1 && v.coord_x <= W &&
               v.coord_y >= 1 && v.coord_y <= H &&
               Maze[v.coord_y][v.coord_x] == '.' &&
               color[v.coord_y][v.coord_x] == WHITE) 
            {
                color[v.coord_y][v.coord_x] = GRAY;
                d[v.coord_y][v.coord_x] = d[u.coord_y][u.coord_x] + 1;
                pi[v.coord_y][v.coord_x] = u;
                Q[idTail++] = v;
            }
        }
        color[u.coord_y][u.coord_x] = BLACK;
    }
    return u; // celda de maxima distancia
}

void solverBFS(int W, int H, struct cell source) {
    struct cell extremo = BFS_Maze(W, H, source);
    extremo = BFS_Maze(W, H, extremo);
    printf("%d\n", d[extremo.coord_y][extremo.coord_x]);
}

void DFS_Visit_Maze(int H, int W, struct cell U, int *time, struct cell arrayMov[]) {
    color[U.coord_y][U.coord_x] = GRAY;
    *time = *time + 1;
    d[U.coord_y][U.coord_x] = *time;

    for(int idAdj = 1; idAdj <= 4; idAdj++) 
    {
        struct cell V;
        V.coord_x = U.coord_x + arrayMov[idAdj].coord_x;
        V.coord_y = U.coord_y + arrayMov[idAdj].coord_y;

        if(V.coord_x >= 1 && V.coord_x <= W &&
           V.coord_y >= 1 && V.coord_y <= H &&
           color[V.coord_y][V.coord_x] == WHITE &&
           Maze[V.coord_y][V.coord_x] == '.') 
        {
            pi[V.coord_y][V.coord_x] = U;
            DFS_Visit_Maze(H, W, V, time, arrayMov);
        }
    }
    color[U.coord_y][U.coord_x] = BLACK;
    *time = *time + 1;
    f[U.coord_y][U.coord_x] = *time;
}

void DFS_Maze(int H, int W) {
    int time = 0;
    struct cell NILFather = {NIL, NIL};
    struct cell U, arrayMov[5];
    assignMovements(arrayMov);

    int depth, maxDepth = 0, trees = 0;
    struct cell root1;

    for(int idRow = 1; idRow <= H; idRow++) {
        for(int idColumn = 1; idColumn <= W; idColumn++) 
        {
            color[idRow][idColumn] = WHITE;
            pi[idRow][idColumn] = NILFather;
            d[idRow][idColumn] = myInfinite;
            f[idRow][idColumn] = myInfinite;
        }
    }

    for(int idRow = 1; idRow <= H; idRow++) {
        for(int idColumn = 1; idColumn <= W; idColumn++) 
        {
            U.coord_x = idColumn;
            U.coord_y = idRow;
            if(Maze[U.coord_y][U.coord_x] == '.' && color[U.coord_y][U.coord_x] == WHITE) 
            {
                DFS_Visit_Maze(H, W, U, &time, arrayMov);
                trees++;
                depth = ((f[U.coord_y][U.coord_x] - d[U.coord_y][U.coord_x]) / 2) + 1;
                if(depth > maxDepth) 
                {
                    maxDepth = depth;
                    root1 = U;
                }
            }
        }
    }
    printf("%d %d ", trees, maxDepth);
    solverBFS(W, H, root1);
}

void solverDFS(int H, int W) {
    DFS_Maze(H, W);
}

int main() {
    int totalCases, idCase, H, W;
    scanf("%d", &totalCases);
    for(idCase = 1; idCase <= totalCases; idCase++) 
    {
        scanf("%d %d", &H, &W);
        ReadMaze(H, W);
        printf("Case %d: ", idCase);
        solverDFS(H, W);
    }
    return 0;
}