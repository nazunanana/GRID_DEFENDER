#include "RippleManager.h"
#include "../Core/Config.h"
#include <algorithm>

/*
衝撃波の制御
*/

void RippleManager::Update()
{
    for (auto &r : m_ripples)
        r.Update();

    // デスポーン
    m_ripples.erase( // 後ろにつめた消滅している衝撃波を削除
        std::remove_if(m_ripples.begin(), m_ripples.end(),
                       [](Ripple &r)
                       { return !r.IsActive(); }), // 生きている衝撃波を配列の前につめる
        m_ripples.end());
}

void RippleManager::Draw()
{
    for (auto &r : m_ripples)
    {
        if (r.IsActive())
            r.Draw();
    }
}

// 衝撃波を生成
void RippleManager::GenerateRipple(int col, int row, ColorId color, int rippleLevel)
{
    int screenX = ORIGIN_X + row * BOX_SIZE + BOX_SIZE / 2;
    int screenY = ORIGIN_Y + col * BOX_SIZE + BOX_SIZE / 2;
    // コンストラクタを生成してm_ripplesに追加
    m_ripples.emplace_back(screenX, screenY, color, rippleLevel);
}

// 衝撃波を取得
std::vector<Ripple>& RippleManager::GetRipples()
{
    return m_ripples;
}
