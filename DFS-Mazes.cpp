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
            if((Maze[U.coord_y][U.coord_x] == '.') &&
               (color[U.coord_y][U.coord_x] == WHITE))
            {
                DFS_Visit_Maze(Maze, H, W, U, &time, color, d, f, pi, arrayMov);
            }
        }
    }
}

void solver(char Maze[][MAXW + 1], int H, int W)
{
    int color[MAXH + 1][MAXW + 1], d[MAXH + 1][MAXW + 1];
    int f[MAXH + 1][MAXW + 1], idRow, idColumn;
    struct cell pi[MAXH + 1][MAXW + 1];

    DFS_Maze(Maze, H, W, color, d, f, pi);

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
    printf("\n");
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
        PrintMaze(Maze, H, W);
        solver(Maze, H, W);
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
*/