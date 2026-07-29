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
    int PopLeakCount(); // 前回呼び出し以降にコア到達したウィルス数を取得しカウントをリセット

private:
    int m_graph[static_cast<int>(ColorId::COUNT)];
    std::vector<Virus> m_viruses;
    float m_spawnTimer = 0.0f;
    float m_spawnInterval = 1.0f;
    float m_moveInterval = 0.5f;
    int m_leakCount = 0;
};
