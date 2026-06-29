#pragma once

class Virus
{
public:
    Virus(int row, int color);
    void Update(float dt, float moveInterval);
    void Despawn();
    int GetCol();
    int GetRow();
    int GetColor();
    bool IsAlive();
private:
    int m_col = 0;
    int m_row;
    int m_color;
    float m_moveTimer = 0.0f;
    bool  m_alive = true;
};