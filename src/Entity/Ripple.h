#pragma once

class Ripple
{
public:
    Ripple(int col, int row, float size, int expandedLevel, int color);
    void Update();
    void Draw();
private:
    int m_col;
    int m_row;
    float m_size;
    int m_expandedLevel;
    int m_color;
    static constexpr float SPEED = 0.2f;
    static constexpr int MAX_LEVEL = 2;
};