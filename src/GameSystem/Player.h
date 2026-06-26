#pragma once
#include "../Input/input.h"

class Player
{
public:
    void Update();
    void Draw();
    bool isShoot = false;
private:
    float m_cooldown = 0.f;
    float m_maxCooldown = 0.5f;
};