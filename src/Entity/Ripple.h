#pragma once
#include "../GameSystem/Common.h"

class Ripple
{
public:
    Ripple(int screenX, int screenY, ColorId color, int rippleLevel);
    bool Update();
    void Draw();
    int GetScreenX();
    int GetScreenY();
    float GetSize(); // 現在の半径
    ColorId GetRippleColor();
    int GetRippleLevel();
    bool IsActive();
private:
    int m_screenX;
    int m_screenY;
    float m_size;
    ColorId m_color;
    int m_rippleLevel; // 何連鎖目か
    bool m_isActive;
    static constexpr float SPEED = 3.0f;
    static constexpr float MAX_SIZE = 2.5f;
};