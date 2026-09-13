#pragma once
#include "../GameSystem/Common.h"

class Ripple
{
public:
    Ripple(int col, int row);
    void Update(bool &isExpand);
    void Draw(ColorId color);
    int GetCol();
    int GetRow();
    float GetScreenX();
    float GetScreenY();
    float GetSize(); // 現在の半径
    bool IsActive();
    int GetSizeLevel();
private:
    int m_col;
    int m_row;
    float m_size; // 衝撃波の大きさ
    int m_sizeLevel; // 衝撃波の大きさレベル
    bool m_isActive;
    static constexpr float SPEED = 4.0f;
    static constexpr float MAX_SIZE = 2.5f;
};