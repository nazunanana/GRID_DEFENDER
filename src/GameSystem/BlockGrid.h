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
    // bool HitBlock(Vec2 screenPos, int& outCol, int& outRow);
    void ChangeColor(int col, int row, ColorId color, int chainCount);
    void AroundBright(int col, int row);
    void AllBright(int col, int row);
    ColorId GetBlockColorAt(int col, int row);
    void ScreenToIndex(int x, int y, int &outCol, int &outRow);
private:
    static constexpr int BRIGHTNESS[3] = { 180, 100, 30 };
    Block m_blocks[COL_MAX][ROW_MAX];
};