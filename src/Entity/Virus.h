#pragma once

class Virus
{
public:
    Virus(int col, int row, int color);
    void Update();
    void Draw();
    void Despawn();
private:
    int m_col;
    int m_row;
    int m_color;
    float m_moveTimer = 2.0f;
    bool  m_alive = false;
};