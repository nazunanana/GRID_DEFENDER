#include <algorithm>
#include "VirusManager.h"
#include "../Core/Config.h"
#include "../Graphics/TextureManager.h"
#include "Common.h"
#include "DxLib.h"

void VirusManager::Update(float dt, int level, Difficulty difficulty)
{
    LevelUp(level, difficulty);
    m_spawnTimer += dt;
    if (m_spawnTimer > m_spawnInterval)
    {
        // スポーン
        m_spawnTimer -= m_spawnInterval;
        int row = GetRand(ROW_MAX - 1); // 出現位置
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
            int graph = TextureManager::Instance().GetVirusGraph(v.GetColor());
            if (graph == -1) continue;
            DrawExtendGraph(x, y, x + BOX_SIZE, y + BOX_SIZE, graph, TRUE);
        }
    }
}

// タップした位置にウィルスがあるかどうか
// あれば消滅させ、色を返す
std::optional<ColorId> VirusManager::GetVirusColorAtPoint(int screenX, int screenY)
{
    for (auto &v : m_viruses)
    {
        int drawX = ORIGIN_X + v.GetRow() * BOX_SIZE;
        if (v.IsAlive() && drawX < screenX && screenX < drawX + BOX_SIZE && v.GetDrawY() < screenY && screenY < v.GetDrawY() + BOX_SIZE)
        {
            std::optional<ColorId> color = v.GetColor();
            v.Despawn();
            return color;
        }
    }
    return std::nullopt;
}

// 衝撃波がウィルスに衝突したときの処理（ウイルスを退治できたかどうかを返す）
bool VirusManager::CollisionRipple(int screenX, int screenY, float size, ColorId color, int &outCol, int &outRow)
{
    // 衝撃波が届いている正方形の範囲
    float squareX0 = screenX - size;
    float squareY0 = screenY - size;
    float squareX1 = screenX + size;
    float squareY1 = screenY + size;

    for (auto &v : m_viruses)
    {
        if (!v.IsAlive() || v.GetColor() != color || v.GetCol() == 0)
            continue;

        // Virusの衝突範囲
        int virusMinX = ORIGIN_X + v.GetRow() * BOX_SIZE;
        int virusMinY = v.GetDrawY();
        int virusMaxX = virusMinX + BOX_SIZE;
        int virusMaxY = virusMinY + BOX_SIZE;

        bool overlap = virusMinX < squareX1 && squareX0 < virusMaxX && virusMinY < squareY1 && squareY0 < virusMaxY;

        int rippleSizeLevel = size / static_cast<float>(BOX_SIZE);
        if(rippleSizeLevel >=1.5f
            && virusMinX < screenX + rippleSizeLevel
            && screenX - rippleSizeLevel < virusMaxX
            && virusMinY < screenY + rippleSizeLevel
            && screenY - rippleSizeLevel < virusMaxY
            && v.GetCol() == 1) // 衝撃波とウイルスが一番上のマスですれ違った時、判定を無視
            return false;

        if (overlap)
        {
            ColorId color = v.GetColor();
            outCol = v.GetCol();
            outRow = v.GetRow();
            v.Despawn();
            return true;
        }
    }
    return false;
}

// コア到達したウィルス数を取得
int VirusManager::PopLeakCount()
{
    int count = m_leakCount;
    m_leakCount = 0;
    return count;
}

// レベルアップ時のパラメータ変化
void VirusManager::LevelUp(int level, Difficulty difficulty)
{
    // パラメータを変える
    switch(level)
    {
    case 1:
        if(difficulty == Difficulty::Normal)
        {
            m_spawnInterval = 1.0f;
            m_moveInterval = 0.5f;
        }
        else
        {
            m_spawnInterval = 0.8f;
            m_moveInterval = 0.4f;
        }
        break;
    case 2:
        if(difficulty == Difficulty::Normal)
        {
            m_spawnInterval = 0.8f;
            m_moveInterval = 0.4f;
        }
        else
        {
            m_spawnInterval = 0.7f;
            m_moveInterval = 0.35f;
        }
        break;
    case 3:
        if(difficulty == Difficulty::Normal)
        {
            m_spawnInterval = 0.7f;
            m_moveInterval = 0.35f;
        }
        else
        {
            m_spawnInterval = 0.6f;
            m_moveInterval = 0.3f;
        }
        break;
    case 4:
        if(difficulty == Difficulty::Normal)
        {
            m_spawnInterval = 0.6f;
            m_moveInterval = 0.3f;
        }
        else
        {
            m_spawnInterval = 0.5f;
            m_moveInterval = 0.25f;
        }
        break;
    default:
        if(difficulty == Difficulty::Normal)
        {
            m_spawnInterval = 0.5f;
            m_moveInterval = 0.25f;
        }
        else
        {
            m_spawnInterval = 0.4f;
            m_moveInterval = 0.2f;
        }
        break;
    }
}