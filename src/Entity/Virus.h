#pragma once
#include "../GameSystem/Common.h"

class Virus
{
public:
    Virus(int row, ColorId color);
    void Update(float dt, float moveInterval);
    void Despawn();
    int GetCol();
    int GetRow();
    ColorId GetColor();
    bool IsAlive();
private:
    int m_col = 0;
    int m_row;
    ColorId m_color;
    float m_moveTimer = 0.0f;
    bool  m_alive = true;
};