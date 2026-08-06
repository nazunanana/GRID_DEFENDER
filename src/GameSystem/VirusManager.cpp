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

void VirusManager::Update(float dt, int level)
{
    LevelUp(level);
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

// タップした位置にウィルスがあるかどうか
// あれば消滅させ、色を返す
std::optional<ColorId> VirusManager::GetVirusColorAtPoint(int col, int row)
{
    for (auto &v : m_viruses)
    {
        int drawX = ORIGIN_X + v.GetRow() * BOX_SIZE;
        if (v.IsAlive() && drawX < row && row < drawX + BOX_SIZE && v.GetDrawY() < col && col < v.GetDrawY() + BOX_SIZE)
        {
            std::optional<ColorId> color = v.GetColor();
            v.Despawn();
            return color;
        }
    }
    return std::nullopt;
}

// 波紋がウィルスに衝突したかどうか
// 衝突した場合消滅させ、色を返す
std::optional<ColorId> VirusManager::CollisionRipple(int screenX, int screenY, float size, int &outCol, int &outRow)
{
    // 波紋が届いている正方形の範囲
    float squareX0 = screenX - size;
    float squareY0 = screenY - size;
    float squareX1 = screenX + size;
    float squareY1 = screenY + size;

    for (auto &v : m_viruses)
    {
        if (!v.IsAlive())
            continue;

        // Virusの衝突範囲
        int virusX0 = ORIGIN_X + v.GetRow() * BOX_SIZE;
        int virusY0 = v.GetDrawY();
        int virusX1 = virusX0 + BOX_SIZE;
        int virusY1 = virusY0 + BOX_SIZE;

        bool overlap = virusX0 < squareX1 && squareX0 < virusX1 && virusY0 < squareY1 && squareY0 < virusY1;
        if (overlap)
        {
            std::optional<ColorId> color = v.GetColor();
            outCol = v.GetCol();
            outRow = v.GetRow();
            v.Despawn();
            return color;
        }
    }
    return std::nullopt;
}

// コア到達したウィルス数を取得
int VirusManager::PopLeakCount()
{
    int count = m_leakCount;
    m_leakCount = 0;
    return count;
}

// レベルアップ時のパラメータ変化
void VirusManager::LevelUp(int level)
{
    // パラメータを変える
    switch(level)
    {
    case 1:
        m_spawnInterval = 1.0f;
        m_moveInterval = 0.5f;
        break;
    case 2:
        m_spawnInterval = 0.8f;
        m_moveInterval = 0.4f;
        break;
    case 3:
        m_spawnInterval = 0.6f;
        m_moveInterval = 0.3f;
        break;
    default:
        m_spawnInterval = 0.5f;
        m_moveInterval = 0.25f;
        break;
    }
}