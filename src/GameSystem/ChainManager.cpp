#include "ChainManager.h"
#include "../Core/Config.h"
#include <algorithm>

/*
波紋の制御
*/

void ChainManager::Update()
{
    for (auto &r : m_ripples)
        r.Update();

    // デスポーン
    m_ripples.erase( // 後ろにつめた消滅している波紋を削除
        std::remove_if(m_ripples.begin(), m_ripples.end(),
                       [](Ripple &r)
                       { return !r.IsActive(); }), // 生きている波紋を配列の前につめる
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

// 波紋を生成
void ChainManager::GenerateRipple(int col, int row, ColorId color, int chainLevel)
{
    int screenX = ORIGIN_X + row * BOX_SIZE + BOX_SIZE / 2;
    int screenY = ORIGIN_Y + col * BOX_SIZE + BOX_SIZE / 2;
    // コンストラクタを生成してm_ripplesに追加
    m_ripples.emplace_back(screenX, screenY, color, chainLevel);
}

// 波紋を取得
std::vector<Ripple>& ChainManager::GetRipples()
{
    return m_ripples;
}
