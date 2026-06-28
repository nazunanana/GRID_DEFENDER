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
    for(int i = 0; i < COL_MAX; i++)
    {
        int y = ORIGIN_Y + BOX_SIZE * i;
        for(int j = 0; j < ROW_MAX; j++)
        {
            int x = ORIGIN_X + BOX_SIZE * j;
            m_blocks[i][j].Draw(x, y);
        }
    }
}

bool BlockGrid::HitBlock(Vec2 screenPos, int& outCol, int& outRow)
{
    return false;
}

void BlockGrid::ChangeColor(int col, int row, int color)
{

}
