#include "BlockGrid.h"
#include "../Core/Config.h"
#include <algorithm>

/*
ブロック全体の制御
*/

void BlockGrid::Update()
{
    for (int i = 0; i < COL_MAX; i++)
        for (int j = 0; j < ROW_MAX; j++)
            m_blocks[i][j].Update();
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

void BlockGrid::ChangeColor(int col, int row, ColorId color, int chainCount)
{
    if (col < 0 || col >= COL_MAX || row < 0 || row >= ROW_MAX)
        return;

    if(chainCount == 3)
        AroundBright(col, row);
    if(chainCount == 5)
        AllBright(col, row);
    m_blocks[col][row].Hit(color);
}

void BlockGrid::AroundBright(int col, int row)
{
    for (int i = col-2; i <= col+2; i++)
    {
        if(i < 0 || COL_MAX <= i) continue;
        for (int j = row-2; j <= row+2; j++)
        {
            if(j < 0 || ROW_MAX <= j) continue;
            if(i == col && j == row) continue;
            int ring = std::max(std::abs(i - col), std::abs(j - row));
            m_blocks[i][j].Bright(BRIGHTNESS[ring]);
        }
    }
}

void BlockGrid::AllBright(int col, int row)
{
    for (int i = 0; i < COL_MAX; i++)
    {
        for (int j = 0; j < ROW_MAX; j++)
        {
            if(i == col && j == row) continue;
            int ring = std::max(std::abs(i - col), std::abs(j - row)) - 1;
            if(ring >= 2) ring = 2;
            m_blocks[i][j].Bright(BRIGHTNESS[ring]);
        }
    }
}

ColorId BlockGrid::GetBlockColorAt(int col, int row)
{
    if (col < 0 || col >= COL_MAX || row < 0 || row >= ROW_MAX)
        return ColorId::None;

    return m_blocks[col][row].GetBlockColor();
}

void BlockGrid::ScreenToIndex(int x, int y, int &outCol, int &outRow)
{
    int col = (y - ORIGIN_Y) / BOX_SIZE;
    int row = (x - ORIGIN_X) / BOX_SIZE;

    if (col < 0 || col >= COL_MAX || row < 0 || row >= ROW_MAX)
        return;

    outCol = col;
    outRow = row;
}