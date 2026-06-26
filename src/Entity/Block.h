#pragma once

class Block
{
public:
    void Update();
    void Draw();
    void Hit();
private:
    int m_color = -1;
};