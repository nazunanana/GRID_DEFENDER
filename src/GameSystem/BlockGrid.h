#pragma once
#include "../Entity/Block.h"
#include "Common.h"
#include "../Core/Config.h"
#include <optional>

class BlockGrid
{
public:
    void Update();
    void Draw();
    bool HitBlock(Vec2 screenPos, int& outCol, int& outRow);
    void ChangeColor(int col, int row, ColorId color);
    std::optional<ColorId> GetBlockColorAt(int col, int row);
private:
    Block m_blocks[COL_MAX][ROW_MAX];
};