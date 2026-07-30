#include "BlockGrid.h"
#include "../Core/Config.h"

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

// bool BlockGrid::HitBlock(Vec2 screenPos, int &outCol, int &outRow)
// {
//     int col = (screenPos.y - ORIGIN_Y) / BOX_SIZE;
//     int row = (screenPos.x - ORIGIN_X) / BOX_SIZE;

//     if (col < 0 || col >= COL_MAX || row < 0 || row >= ROW_MAX)
//         return false;

//     outCol = col;
//     outRow = row;
//     return true;
// }

void BlockGrid::ChangeColor(int col, int row, ColorId color)
{
    if (col < 0 || col >= COL_MAX || row < 0 || row >= ROW_MAX)
        return;

    m_blocks[col][row].Hit(color);
}

std::optional<ColorId> BlockGrid::GetBlockColorAt(int col, int row)
{
    if (col < 0 || col >= COL_MAX || row < 0 || row >= ROW_MAX)
        return std::nullopt;

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