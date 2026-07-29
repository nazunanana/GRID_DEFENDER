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
    bool HasLeaked();
    int GetDrawY();
private:
    int m_col = 0;
    int m_row;
    ColorId m_color;
    float m_moveTimer = 0.0f;
    float m_moveInterval;
    bool  m_alive = true;
    bool  m_leaked = false;
};