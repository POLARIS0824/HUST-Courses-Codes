#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define SIZE 4

typedef struct
{
    int n;
    const char* word;
} mapping;

mapping map[] = 
{
    {2, "贺"},
    {4, "翔"},
    {8, "学"},
    {16, "长"},
    {32, "祝"},
    {64, "你"},
    {128, "生"},
    {256, "日"},
    {512, "快"},
    {1024, "乐"},
    {2048, "!"}
};

void init_board(int board[SIZE][SIZE]);
void print_board(int board[SIZE][SIZE], int score);
void add_random_tile(int board[SIZE][SIZE]);
int get_empty_tiles(int board[SIZE][SIZE]);
int get_score(int board[SIZE][SIZE]);
// void left(int board[SIZE][SIZE]);
// void right(int board[SIZE][SIZE]);
// void up(int board[SIZE][SIZE]);
// void down(int board[SIZE][SIZE]);

int score = 0;

int main(void)
{
    setlocale(LC_ALL, "zh_CN.UTF-8");

    int board[SIZE][SIZE];
    init_board(board);
    add_random_tile(board);
    add_random_tile(board);
    get_score(board);
    print_board(board, score);
}

// 初始化棋盘
void init_board(int board[SIZE][SIZE])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j] = 0;
        }
    }       
}

// 获取最高分数
int get_score(int board[SIZE][SIZE])
{
    int score = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] > score)
            {
                score = board[i][j];
            }
        }
    }
    return score;
}

// 打印棋盘
void print_board(int board[SIZE][SIZE], int score)
{
    printf("Score: %d\n", score);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
            {
                printf("    -");
            }
            else
            {
                for (int k = 0; k < sizeof(map) / sizeof(mapping); k++)
                {
                    if (board[i][j] == map[k].n)
                    {
                        printf(" %s", map[k].word);
                    }
                }
            }
        }
        printf("\n");
    }
}

// 添加随机数
void add_random_tile(int board[SIZE][SIZE])
{
    if (get_empty_tiles(board) == 0)
    {
        return;
    }

    srand(time(NULL));
    int x = rand() % 4;
    int y = rand() % 4;
    int value = (rand() % 2 + 1) * 2;

    while (board[x][y] != 0)
    {
        x = rand() % 4;
        y = rand() % 4;
    }

    board[x][y] = value;
}

// 获取棋盘上的空格数量
int get_empty_tiles(int board[SIZE][SIZE])
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
            {
                count++;
            }
        }
    }
    return count;
}

// // 左移棋子
// void left(int board[SIZE][SIZE])
// {
    
// }