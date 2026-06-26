#pragma once
#include "Block.h"
#include "Common.h"

class BlockGrid
{
public:
    void Update();
    void Draw();
    bool HitBlock(Vec2 screenPos, int& col, int& row);
    void ChangeColor(int col, int row, int color);
private:
    Block m_blocks[GameScene::COL_MAX][GameScene::ROW_MAX];
    void MakeStage();
};