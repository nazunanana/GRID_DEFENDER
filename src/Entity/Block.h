#pragma once
#include "../GameSystem/Common.h"

class Block
{
public:
    void Update();
    void Draw(int screenX, int screenY);
    void Hit(ColorId color);
    ColorId GetBlockColor();
private:
    ColorId m_color = ColorId::None;
    unsigned int ToDrawColor(ColorId colorId);
};