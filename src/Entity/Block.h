#pragma once

class Block
{
public:
    void Update();
    void Draw(int screenX, int screenY);
    void Hit(int color);
private:
    int m_color = -1;
    unsigned int ToDrawColor(int colorId);
};