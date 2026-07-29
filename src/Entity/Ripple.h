#pragma once
#include "../GameSystem/Common.h"

class Ripple
{
public:
    Ripple(int col, int row, int screenX, int screenY, ColorId color, int chainLevel);
    bool Update();
    void Draw();
    int GetExpandedLevel();
    int GetCol();
    int GetRow();
    ColorId GetRippleColor();
    int GetChainLevel();
    bool IsActive();
private:
    int m_col;
    int m_row;
    int m_screenX;
    int m_screenY;
    float m_size;
    int m_expandedLevel;
    ColorId m_color;
    int m_chainLevel; // この波紋が何連鎖目かを表す
    bool m_isActive;
    unsigned int ToDrawColor(ColorId colorId);
    static constexpr float SPEED = 3.0f;
    static constexpr float MAX_LEVEL = 2.5f;
};