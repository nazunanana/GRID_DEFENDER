#include <algorithm>
#include "VirusManager.h"
#include "../Core/Config.h"
#include "Common.h"
#include "DxLib.h"

VirusManager::VirusManager()
{
    m_graph[static_cast<int>(ColorId::Magenta)] = LoadGraph("img/magenta_virus.png");
    m_graph[static_cast<int>(ColorId::Cyan)] = LoadGraph("img/cyan_virus.png");
    m_graph[static_cast<int>(ColorId::Purple)] = LoadGraph("img/purple_virus.png");
}

VirusManager::~VirusManager()
{
    for (int graph : m_graph)
    {
        DeleteGraph(graph);
    }
}

void VirusManager::Update(float dt)
{
    m_spawnTimer += dt;
    if (m_spawnTimer > m_spawnInterval)
    {
        // スポーン
        m_spawnTimer -= m_spawnInterval;
        int row = GetRand(ROW_MAX - 1);                                                      // 出現位置
        ColorId color = static_cast<ColorId>(GetRand(static_cast<int>(ColorId::COUNT) - 1)); // 出現カラー
        m_viruses.emplace_back(row, color);
    }

    for (auto &v : m_viruses)
    {
        // ウィルスの状態を更新
        v.Update(dt, m_moveInterval);
        // ウィルスのコア到達数を集計
        if (!v.IsAlive() && v.HasLeaked())
            m_leakCount++;
    }

    // デスポーン
    m_viruses.erase( // 後ろにつめた死んでいるVirusを削除
        std::remove_if(m_viruses.begin(), m_viruses.end(),
                       [](Virus &v)
                       { return !v.IsAlive(); }), // 生きているVirusを配列の前につめる
        m_viruses.end());
}

void VirusManager::Draw()
{
    for (auto &v : m_viruses)
    {
        if (v.IsAlive())
        {
            int x = ORIGIN_X + v.GetRow() * BOX_SIZE;
            int y = v.GetDrawY();
            int graph = m_graph[static_cast<int>(v.GetColor())];
            DrawExtendGraph(x, y, x + BOX_SIZE, y + BOX_SIZE, graph, TRUE);
        }
    }
}

void VirusManager::KillVirus(int col, int row)
{
    for (auto &v : m_viruses)
    {
        if (v.IsAlive() && v.GetCol() == col && v.GetRow() == row)
            return v.Despawn();
    }
}

std::optional<ColorId> VirusManager::GetVirusColor(int col, int row)
{
    for (auto &v : m_viruses)
    {
        if (v.IsAlive() && v.GetCol() == col && v.GetRow() == row)
            return v.GetColor();
    }
    return std::nullopt;
}

int VirusManager::PopLeakCount()
{
    int count = m_leakCount;
    m_leakCount = 0;
    return count;
}