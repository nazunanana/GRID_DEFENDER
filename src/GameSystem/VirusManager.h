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

    void Update(float dt);
    void Draw();
    void KillVirus(int col, int row);
    std::optional<ColorId> GetVirusColor(int col, int row);

private:
    int m_graph[static_cast<int>(ColorId::COUNT)];
    std::vector<Virus> m_viruses;
    float m_spawnTimer = 0.0f;
    float m_spawnInterval = 3.0f;
    float m_moveInterval = 2.0f;
};
