#include "ChainManager.h"
#include "../Core/Config.h"
#include <algorithm>

/*
波紋の制御
*/

void ChainManager::Update()
{
    // 状態を更新
    for (auto &r : m_ripples)
    {
        if (r.Update()) // expandedLevelが更新されたかどうか
        {
            int offset = r.GetExpandedLevel() - 1; // 発生源から何マス離れるか
            for (int dc = -offset; dc <= offset; dc++)
            {
                for (int dr = -offset; dr <= offset; dr++)
                {
                    //if (std::abs(dc) < offset && std::abs(dr) < offset) continue;
                    int col = dc + r.GetCol();
                    int row = dr + r.GetRow();
                    if(col < 0 || COL_MAX <= col || row < 0 || ROW_MAX <= row) continue;
                    m_expandedRipples.push({ col, row, r.GetRippleColor() });
                }
            }
        }
    }

    // デスポーン
    m_ripples.erase( // 後ろにつめた消滅している波紋を削除
        std::remove_if(m_ripples.begin(), m_ripples.end(),
                       [](Ripple &r)
                       { return !r.IsActive(); }), // 生きているVirusを配列の前につめる
        m_ripples.end());
}

void ChainManager::Draw()
{
    for (auto &r : m_ripples)
    {
        if (r.IsActive())
            r.Draw();
    }
}

void ChainManager::GenerateRipple(int col, int row, ColorId color)
{
    int screenX = ORIGIN_X + row * BOX_SIZE + BOX_SIZE / 2;
    int screenY = ORIGIN_Y + col * BOX_SIZE + BOX_SIZE / 2;
    // コンストラクタを生成してm_ripplesに追加
    m_ripples.emplace_back(col, row, screenX, screenY, color);
}

bool ChainManager::HasExpandedRipple()
{
    return !m_expandedRipples.empty();
}

ChainManager::ExpandedRipple ChainManager::PopExpandedRipple()
{
    ExpandedRipple out = m_expandedRipples.front();
    m_expandedRipples.pop();
    return out;
}