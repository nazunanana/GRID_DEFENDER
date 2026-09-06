#pragma once
#include "Common.h"

class Player
{
public:
    void Update(bool isInput, Vec2 pos);
    void Draw();
    Vec2 GetPos();
    bool isShoot = false;

private:
    Vec2 m_pos;
};