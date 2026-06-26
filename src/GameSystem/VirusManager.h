#pragma once
#include "../Entity/Virus.h"
#include <optional>
#include <vector>

class VirusManager
{
public:
    void Update();
    void Draw();
    void KillVirus(int col, int row);
    std::optional<int> GetVirusColor(int col, int row);
private:
    std::vector<Virus> m_viruses;
    int m_spawnInterval = 3.0f;
};
