#pragma once

class Ripple
{
public:
    Ripple(int col, int row, float size, int expandedLevel, int color);
    void Update();
    void Draw();
private:
    static constexpr float SPEED = 0.2f;
    static constexpr int MAX_LEVEL = 2;
};