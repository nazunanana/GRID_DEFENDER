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
    const int LINE_LENGTH = 14;
    const int LINE_THICKNESS = 2;
    const int CIRCLE_RADIUS = 10;
    float m_cooldown = 0.f;
    float m_maxCooldown = 0.5f;
    Vec2 m_pos;
};