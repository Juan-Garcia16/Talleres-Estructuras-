#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXH 105
#define MAXW 105
#define WHITE 2
#define GRAY 1
#define BLACK 0
#define myInfinite 2147483647
#define NIL -1

struct cell
{
    int coord_x;
    int coord_y;
};

void ReadMaze(char Maze[][MAXW], int W, int H)
{
    char line[MAXW];
    int idRow, idColumn;
    struct cell source;

    for(idRow=1; idRow<=H; idRow++)
    {
        scanf("%s", line);
        for(idColumn=1; idColumn<=W; idColumn++)
            Maze[idRow][idColumn] = line[idColumn - 1];
    }
}


void PrintMaze(char Maze[][MAXW], int W, int H)
{
    int idRow, idColumn;

    printf("\nThe original maze without source position:\n\n");
    for(idRow=1; idRow<=H; idRow++)
    {
        for(idColumn=1; idColumn <= W; idColumn++)
            printf("%c", Maze[idRow][idColumn]);
        printf("\n");
    }
    printf("\n");
}

void initializeMovements(struct cell movements[])
{
    movements[0].coord_x = 0;
    movements[0].coord_y = 0;
    movements[1].coord_x = 0;
    movements[1].coord_y = -1;
    movements[2].coord_x = 0;
    movements[2].coord_y = 1;
    movements[3].coord_x = -1;
    movements[3].coord_y = 0;
    movements[4].coord_x = 1;
    movements[4].coord_y = 0;
}

struct cell BFS_Maze(char Maze[][MAXW], int W, int H, struct cell s,
              int color[][MAXW], int d[][MAXW], struct cell pi[][MAXW])
{
    int idRow, idColumn, idHead = 1, idTail = 1, idMovement;
    struct cell NilFather, Q[(H * W) + 5], u, v, movements[5];

    initializeMovements(movements);
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

    printf("\n%d\n", d[u.coord_y][u.coord_x]);
    printf("\n%d %d\n", u.coord_y, u.coord_x);

    return u; //celda donde se alcanza la distancia maxima
}

void solverBFS(char Maze[][MAXW], int W, int H, struct cell source)
{
    int color[MAXH][MAXW], d[MAXH][MAXW], idRow, idColumn;
    struct cell pi[MAXH][MAXW], extremo;

    extremo = BFS_Maze(Maze, W, H, source, color, d, pi);

    extremo = BFS_Maze(Maze, W, H, extremo, color, d, pi);
    printf("\n%d\n", d[extremo.coord_y][extremo.coord_x]);
    printf("\n%d %d\n", extremo.coord_y, extremo.coord_x);

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
}

int main()
{
    char Maze[MAXH][MAXW];
    int T, W, H, idCase;
    struct cell source;

    scanf("%d", &T);
    for(idCase=1; idCase<=T; idCase++)
    {
        scanf("%d %d", &H, &W);
        ReadMaze(Maze, W, H);
        PrintMaze(Maze, W, H);
        solverBFS(Maze, W, H, {1, 1});
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