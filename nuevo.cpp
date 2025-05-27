#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXW 100
#define MAXH 100
#define NIL -1
#define BLACK 0
#define GRAY 1
#define WHITE 2
#define myInfinite 2147483647
#define NIL -1

struct cell
{
    int coord_x;
    int coord_y;
};

void ReadMaze(char Maze[][MAXW + 1], int H, int W)
{
    int idRow, idColumn;
    char line[W + 1];

    for(idRow = 1; idRow <= H; idRow++)
    {
        scanf("%s", line);
        for(idColumn = 1; idColumn <= W; idColumn++)
            Maze[idRow][idColumn] = line[idColumn - 1];
    }
}

void PrintMaze(char Maze[][MAXW + 1],
                     int H, int W)
{
    int idRow, idColumn;

    printf("\n");
    printf("Maze:\n");

    for(idRow = 1; idRow <= H; idRow++)
    {
        for(idColumn = 1; idColumn <= W; idColumn++)
            printf("%c", Maze[idRow][idColumn]);
        printf("\n");
    }
}

void assignMovements(struct cell arrayMov[])
{
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


struct cell BFS_Maze(char Maze[][MAXW + 1], int W, int H, struct cell s,
              int color[][MAXW + 1], int d[][MAXW + 1], struct cell pi[][MAXW + 1])
{
    int idRow, idColumn, idHead = 1, idTail = 1, idMovement;
    struct cell NilFather, Q[(H * W) + 5], u, v, movements[5];

    assignMovements(movements);
    NilFather.coord_x = NIL;
    NilFather.coord_y = NIL;

    for(idRow = 1; idRow <= H; idRow++)
    {
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
    Q[idTail] = s;
    idTail++;

    while(idHead < idTail)
    {
        u = Q[idHead];
        idHead++;
        for(idMovement = 1; idMovement <= 4; idMovement++)
        {
            v.coord_x = u.coord_x + movements[idMovement].coord_x;
            v.coord_y = u.coord_y + movements[idMovement].coord_y;

            if((v.coord_x >= 1 && v.coord_x <= W) &&
               (v.coord_y >= 1 && v.coord_y <= H) &&
               (Maze[v.coord_y][v.coord_x] == '.') &&
               (color[v.coord_y][v.coord_x] == WHITE))
            {
                color[v.coord_y][v.coord_x] = GRAY;
                d[v.coord_y][v.coord_x] = d[u.coord_y][u.coord_x] + 1;
                pi[v.coord_y][v.coord_x] = u;
                Q[idTail] = v;
                idTail++;
            }
        }
        color[u.coord_y][u.coord_x] = BLACK;
    }

    //printf("\n%d\n", d[u.coord_y][u.coord_x]);
    //printf("\n%d %d\n", u.coord_y, u.coord_x);

    return u; //celda donde se alcanza la distancia maxima
}

void solverBFS(char Maze[][MAXW + 1], int W, int H, struct cell source)
{
    int color[MAXH + 1][MAXW + 1], d[MAXH + 1][MAXW + 1], idRow, idColumn;
    struct cell pi[MAXH + 1][MAXW + 1], extremo;

    extremo = BFS_Maze(Maze, W, H, source, color, d, pi);
    //printf("\n%d\n", d[extremo.coord_y][extremo.coord_x]);
    //printf("\n%d %d\n", extremo.coord_y, extremo.coord_x);

    extremo = BFS_Maze(Maze, W, H, extremo, color, d, pi);
    printf("\n%d\n", d[extremo.coord_y][extremo.coord_x]);
    printf("\n%d %d\n", extremo.coord_y, extremo.coord_x);

    


    /*
    printf("Matrix of colors:\n\n");
    for(idRow=1; idRow<=H; idRow++)
    {
        for(idColumn=1; idColumn <= W; idColumn++)
        {
            if(color[idRow][idColumn] == WHITE)
                printf(" W");
            if(color[idRow][idColumn] == GRAY)
                printf(" G");
            if(color[idRow][idColumn] == BLACK)
                printf(" B");
        }
        printf("\n");
    }
    printf("\n");

    printf("Matrix of distances:\n\n");
    for(idRow=1; idRow<=H; idRow++)
    {
        for(idColumn=1; idColumn<=W; idColumn++)
        {
            if(d[idRow][idColumn] == myInfinite)
                printf(" IN");
            else
            {
                if(d[idRow][idColumn] < 10)
                    printf("  %d", d[idRow][idColumn]);
                else
                    printf(" %d", d[idRow][idColumn]);
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("Matrix of fathers:\n\n");
    for(idRow=1; idRow<=H; idRow++)
    {
        for(idColumn=1; idColumn<=W; idColumn++)
        {
            if(pi[idRow][idColumn].coord_x == NIL)
                printf(" [ -1, -1]");
            else
            {
                if(pi[idRow][idColumn].coord_x < 10)
                    printf(" [  %d,", pi[idRow][idColumn].coord_x);
                else
                    printf(" [ %d,", pi[idRow][idColumn].coord_x);
                if(pi[idRow][idColumn].coord_y < 10)
                    printf("  %d]", pi[idRow][idColumn].coord_y);
                else
                    printf(" %d]", pi[idRow][idColumn].coord_y);
            }
        }
        printf("\n");
    }
    printf("\n");
    */
}

void DFS_Visit_Maze(char Maze[][MAXW + 1],
              int H, int W, struct cell U, int *time,
              int color[][MAXW + 1],
              int d[][MAXW + 1],
              int f[][MAXW + 1],
              struct cell pi[][MAXW + 1],
              struct cell arrayMov[])
{
    int idAdj;
    struct cell V;

    color[U.coord_y][U.coord_x] = GRAY;
    *time = *time + 1;
    d[U.coord_y][U.coord_x] = *time;

    for(idAdj = 1; idAdj <= 4; idAdj++)
    {
        V.coord_x = U.coord_x + arrayMov[idAdj].coord_x;
        V.coord_y = U.coord_y + arrayMov[idAdj].coord_y;
        if((V.coord_x >= 1) && (V.coord_x <= W) &&
           (V.coord_y >= 1) && (V.coord_y <= H) &&
           (color[V.coord_y][V.coord_x] == WHITE) &&
           (Maze[V.coord_y][V.coord_x] == '.'))
        {
            pi[V.coord_y][V.coord_x] = U;
            DFS_Visit_Maze(Maze, H, W, V, &(*time), color, d, f, pi, arrayMov);
        }
    }
    color[U.coord_y][U.coord_x] = BLACK;
    *time = *time + 1;
    f[U.coord_y][U.coord_x] = *time;
}

void DFS_Maze(char Maze[][MAXW + 1],
              int H, int W,
              int color[][MAXW + 1],
              int d[][MAXW + 1],
              int f[][MAXW + 1],
              struct cell pi[][MAXW + 1])
{
    int idRow, idColumn, time = 0;
    struct cell NILFather, U, arrayMov[5];
    NILFather.coord_x = NIL;
    NILFather.coord_y = NIL;
    assignMovements(arrayMov);

    int depth, maxDepth = 0, trees = 0; 
    struct cell root1, root2 = {-1, -1};
    struct cell depthRoot1, depthRoot2;

    for(idRow = 1; idRow <= H; idRow++)
    {
        for(idColumn = 1; idColumn <= W; idColumn++)
        {
            color[idRow][idColumn] = WHITE;
            pi[idRow][idColumn] = NILFather;
            d[idRow][idColumn] = myInfinite;
            f[idRow][idColumn] = myInfinite;
         }
    }

    for(idRow = 1; idRow <= H; idRow++)
    {
        for(idColumn = 1; idColumn <= W; idColumn++)
        {
            U.coord_x = idColumn;
            U.coord_y = idRow;
            //printf("\n %d %d\n", U.coord_x, U.coord_y);
            if((Maze[U.coord_y][U.coord_x] == '.') &&
               (color[U.coord_y][U.coord_x] == WHITE))
            {
                DFS_Visit_Maze(Maze, H, W, U, &time, color, d, f, pi, arrayMov);
                //coodenadas funciona y,x
                trees++;
                depth = ((f[U.coord_y][U.coord_x] - d[U.coord_y][U.coord_x]) / 2) + 1;
                if(depth > maxDepth)
                {
                    maxDepth = depth;
                    root1 = U;
                }
                else if(depth == maxDepth)
                    root2 = U;
            }
        }
    }

    //printf("---------");
    //printf("\n%d\n", maxDepth);
    //printf("\n%d %d\n", root1.coord_y, root1.coord_x);

    printf("%d %d ", trees, maxDepth);
    solverBFS(Maze, W, H, root1);
    //printf("\n%d\n", d[depthRoot1.coord_y][depthRoot1.coord_x]);
    //printf("\n%d %d\n", depthRoot1.coord_y, depthRoot1.coord_x);

}

void solverDFS(char Maze[][MAXW + 1], int H, int W)
{
    int color[MAXH + 1][MAXW + 1], d[MAXH + 1][MAXW + 1];
    int f[MAXH + 1][MAXW + 1], idRow, idColumn;
    struct cell pi[MAXH + 1][MAXW + 1];

    DFS_Maze(Maze, H, W, color, d, f, pi);

    /*
    printf("\n");
    printf("Matrix of colors:\n\n");
    for(idRow = 1; idRow <= H; idRow++)
    {
        for(idColumn = 1; idColumn <= W; idColumn++)
        {
            if(color[idRow][idColumn] == WHITE)
                printf("W");
            if(color[idRow][idColumn] == GRAY)
                printf("G");
            if(color[idRow][idColumn] == BLACK)
                printf("B");
        }
        printf("\n");
    }
    printf("\n");

    printf("Matrix of discovered:\n\n");
    for(idRow = 1; idRow <= H; idRow++)
    {
        for(idColumn = 1; idColumn <= W; idColumn++)
        {
            if(d[idRow][idColumn] == myInfinite)
                printf(" IN");
            else
            {
                if(d[idRow][idColumn] < 10)
                    printf("  %d", d[idRow][idColumn]);
                else
                    printf(" %d", d[idRow][idColumn]);
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("Matrix of finalized:\n\n");
    for(idRow = 1; idRow <= H; idRow++)
    {
        for(idColumn = 1; idColumn <= W; idColumn++)
        {
            if(f[idRow][idColumn] == myInfinite)
                printf(" IN");
            else
            {
                if(f[idRow][idColumn] < 10)
                    printf("  %d", f[idRow][idColumn]);
                else
                    printf(" %d", f[idRow][idColumn]);
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("Matrix of fathers:\n\n");
    for(idRow=1; idRow<=H; idRow++)
    {
        for(idColumn=1; idColumn<=W; idColumn++)
        {
            if(pi[idRow][idColumn].coord_x == NIL)
                printf(" [ -1, -1]");
            else
            {
                if(pi[idRow][idColumn].coord_x < 10)
                    printf(" [  %d,", pi[idRow][idColumn].coord_x);
                else
                    printf(" [ %d,", pi[idRow][idColumn].coord_x);
                if(pi[idRow][idColumn].coord_y < 10)
                    printf("  %d]", pi[idRow][idColumn].coord_y);
                else
                    printf(" %d]", pi[idRow][idColumn].coord_y);
            }
        }
        printf("\n");
    }
    printf("\n");*/
}

int main()
{
    char Maze[MAXH + 1][MAXW + 1];
    int totalCases, idCase, H, W;

    scanf("%d", &totalCases);
    for(idCase = 1; idCase <= totalCases; idCase++)
    {
        scanf("%d %d", &H, &W);
        ReadMaze(Maze, H, W);
        //PrintMaze(Maze, H, W);
        printf("Case %d: ", idCase);
        solverDFS(Maze, H, W);
    }
    return 0;
}

/*
1
7 8
.....#.#
.###.#..
.#...##.
.#####..
.#.###.#
.#...#..
...####.



1
5 7
...#...
...#...
...#...
...#...
...#...
*/