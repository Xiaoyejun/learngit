#include<stdio.h>



#define ROW 6
#define COL 6


typedef struct Maze{
    int maze[ROW][COL];
}Maze;


void MazeInit(Maze* maze)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    int data[ROW][COL] = {
        {0 , 0 , 1 , 0 , 0 , 0},
        {0 , 0 , 1 , 1 , 1 , 0},
        {0 , 0 , 1 , 0 , 1 , 0},
        {0 , 1 , 1 , 0 , 1 , 0},
        {0 , 0 , 1 , 0 , 0 , 0},
        {0 , 0 , 1 , 0 , 0 , 0}
    };
    int i = 0;
    for(; i<ROW; i++){
        int j = 0;
        for(; j<COL; j++){
            maze->maze[i][j] = data[i][j];
        }
    }
}

void MazePrint(Maze* maze)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    int i = 0;
    for(; i<ROW; i++){
        int j = 0;
        for(; j<COL; j++){
            printf("%2d ",maze->maze[i][j]);
        }
        printf("\n");
    }
}




///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

typedef struct Point{
    int row;
    int col;
}Point;
//走的点

//判断当前点是否可以落脚
int Canstay(Maze* maze,Point cur)
{
    //边界外
    if(cur.row<0 || cur.row>=ROW || cur.col<0 || cur.col>=COL)
    {
        return 0;
    }
    //遇到了墙
    //遇到了标记点
    //如果遇到了1，表示该路可走
    if(maze->maze[cur.row][cur.col] == 1 )
    {
        return 1;
    }
    return 0;
}

//标记当前点
void mask(Maze* maze,Point cur)
{
    maze->maze[cur.row][cur.col] = 2;
}

//判断当前点是不是出口
int IsExit(Point cur,Point entry)
{
    if(cur.row == entry.row && cur.col == entry.col)
    {
        return 0;
    }
    if(cur.row == 0 || cur.col == 0 || cur.row == ROW || cur.col == COL)
    {
        return 1;
    }
    return 0;
}
//递归实现迷宫问题
void _GetPath(Maze* maze,Point cur,Point entry)
{
    //判断当前点是否可以落脚，不可以的话直接返回
    if(!Canstay(maze,cur))
    {
        return;
    }
    //标记当前点
    mask(maze,cur);
    //判断当前点是不是出口
    //  是出口，直接返回
    //  不是出口，继续
    //继续顺时针判断当前点的四个方向
    if(IsExit(cur,entry))
    {
        return;
    }
    //上
    Point up;
    up.row = cur.row - 1;
    up.col = cur.col;
    _GetPath(maze,up,entry);
    //右
    Point right;
    right.row = cur.row;
    right.col = cur.col + 1;
    _GetPath(maze,right,entry);
    //下
    Point down;
    down.row = cur.row + 1;
    down.col = cur.col;
    _GetPath(maze,down,entry);
    //左
    Point left;
    left.row = cur.row;
    left.col = cur.col - 1;
    _GetPath(maze,left,entry);
}

void GetPath(Maze* maze,Point entry)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    _GetPath(maze,entry,entry);
}

void Test() 
{
    Maze maze;
    MazeInit(&maze);
    MazePrint(&maze);
    printf("\n");
    Point entry;
    entry.row = 0;
    entry.col = 2;
    GetPath(&maze,entry);
    MazePrint(&maze);
}


int main()
{
    Test();
    return 0;
}
