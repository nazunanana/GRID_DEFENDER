#include "BlockGrid.h"
#include "../Core/Config.h"

/*
ブロック全体の制御
*/

void BlockGrid::Update()
{
}

void BlockGrid::Draw()
{
    for (int i = 0; i < COL_MAX; i++)
    {
        int y = ORIGIN_Y + BOX_SIZE * i;
        for (int j = 0; j < ROW_MAX; j++)
        {
            int x = ORIGIN_X + BOX_SIZE * j;
            m_blocks[i][j].Draw(x, y);
        }
    }
}

bool BlockGrid::HitBlock(Vec2 screenPos, int &outCol, int &outRow)
{
    int col = (screenPos.y - ORIGIN_Y) / BOX_SIZE;
    int row = (screenPos.x - ORIGIN_X) / BOX_SIZE;

    if (col < 0 || col >= COL_MAX || row < 0 || row >= ROW_MAX)
        return false;

    outCol = col;
    outRow = row;
    return true;
    // if (screenPos.x < ORIGIN_X || SCREEN_W - ORIGIN_X < screenPos.x || screenPos.y < ORIGIN_Y || SCREEN_H - ORIGIN_Y < screenPos.y)
    //     return false;

    // for (int i = 0; i < COL_MAX; i++)
    // {
    //     if (screenPos.y < ORIGIN_Y + BOX_SIZE * (i + 1))
    //     {
    //         for (int j = 0; j < ROW_MAX; j++)
    //         {
    //             if (screenPos.x < ORIGIN_X + BOX_SIZE * (j + 1))
    //             {
    //                 outCol = i;
    //                 outRow = j;
    //                 return true;
    //             }
    //         }
    //     }
    // }
    // return false;
}

void BlockGrid::ChangeColor(int col, int row, int color)
{
    m_blocks[col][row].Hit(color);
}
