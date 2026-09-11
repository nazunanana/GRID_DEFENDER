#pragma once
#include "../Entity/Virus.h"
#include "Common.h"
#include <optional>
#include <vector>

class VirusManager
{
public:
    void Update(float dt, int level, Difficulty difficulty);
    void Draw();
    std::optional<ColorId> GetVirusColorAtPoint(int screenX, int screenY);
    bool CollisionRipple(int screenX, int screenY, float size, ColorId color, int &outCol, int &outRow);
    int PopLeakCount();

private:
    std::vector<Virus> m_viruses;
    float m_spawnTimer = 0.0f;
    float m_spawnInterval = 1.0f;
    float m_moveInterval = 0.5f;
    int m_leakCount = 0;
    void LevelUp(int level, Difficulty difficulty);
};
