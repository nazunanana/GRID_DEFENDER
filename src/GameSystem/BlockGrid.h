#pragma once
#include "../Entity/Block.h"
#include "Common.h"
#include "../Core/Config.h"

class BlockGrid
{
public:
    void Update();
    void Draw();
    bool HitBlock(Vec2 screenPos, int& outCol, int& outRow);
    void ChangeColor(int col, int row, int color);
private:
    Block m_blocks[COL_MAX][ROW_MAX];
    void MakeStage();
};