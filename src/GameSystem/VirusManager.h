#pragma once
#include "../Entity/Virus.h"
#include "Common.h"
#include <optional>
#include <vector>

class VirusManager
{
public:
    VirusManager();
    ~VirusManager();

    void Update(float dt, int level);
    void Draw();
    std::optional<ColorId> GetVirusColorAtPoint(int col, int row);
    std::optional<ColorId> CollisionRipple(int screenX, int screenY, float size, int &outCol, int &outRow);
    int PopLeakCount();

private:
    int m_graph[static_cast<int>(ColorId::COUNT)];
    std::vector<Virus> m_viruses;
    float m_spawnTimer = 0.0f;
    float m_spawnInterval = 1.0f;
    float m_moveInterval = 0.5f;
    int m_leakCount = 0;
    void LevelUp(int level);
};
