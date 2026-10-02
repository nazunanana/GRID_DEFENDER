#include "RippleManager.h"
#include "BlockGrid.h"
#include "VirusManager.h"
#include "../Core/Config.h"
#include <algorithm>

/*
衝撃波の制御
*/

void RippleManager::Update(BlockGrid &blockMgr, VirusManager &virusMgr, ChainEventType &outChainEvent, std::vector<int> &outChainCount, bool &isSameColor)
{
    for (auto &c : m_chains)
    {
        // 発生する衝撃波を保存
        std::vector<Ripple> spawnedRipples;

        // 衝撃波ループ
        for (auto &r : c.m_ripples)
        {
            bool isExpand;
            r.Update(isExpand);

            // 衝突するウイルスのout引数
            int col, row;
            ColorId virusColor;

            // ウイルスと衝突した場合、退治する
            if (virusMgr.CollisionRipple(r.GetScreenX(), r.GetScreenY(), r.GetSize(), virusColor, col, row))
            {
                c.chainCount++;
                outChainCount.push_back(c.chainCount);
                outChainEvent = ChainEventType::CollisionVirus;
                if(virusColor == c.color) // もし同色ウイルスと衝突したら
                {
                    isSameColor = true;
                    blockMgr.ChangeColor(col, row, c.color, c.chainCount); // 抗体生成
                    c.passed[col][row] = true;
                }
                isSameColor = false;
            }

            // 同色抗体から衝撃波生成する処理
            if (!isExpand)
                continue;
            int offset = r.GetSizeLevel() - 1;
            for (int dc = -offset; dc <= offset; dc++)
            {
                for (int dr = -offset; dr <= offset; dr++)
                {
                    if (std::abs(dc) < offset && std::abs(dr) < offset)
                        continue; // 走査するマスの内側はスルー

                    col = dc + r.GetCol();
                    row = dr + r.GetRow();

                    if (col < 0 || COL_MAX <= col || row < 0 || ROW_MAX <= row)
                        continue; // 盤面外
                    if (c.passed[col][row])
                        continue; // 中継済み
                    if (blockMgr.GetBlockColorAt(col, row) != c.color)
                        continue; // 同色抗体でない

                    spawnedRipples.emplace_back(col, row);
                    c.passed[col][row] = true;
                    if (outChainEvent != ChainEventType::CollisionVirus)
                        outChainEvent = ChainEventType::CollisionBlock;
                }
            }
        }

        // 衝撃波のスポーン
        c.m_ripples.insert(c.m_ripples.end(), spawnedRipples.begin(), spawnedRipples.end());

        // 衝撃波のデスポーン
        c.m_ripples.erase( // 後ろにつめた消滅している衝撃波を削除
            std::remove_if(c.m_ripples.begin(), c.m_ripples.end(),
                           [](Ripple &r)
                           { return !r.IsActive(); }), // 生きている衝撃波を配列の前につめる
            c.m_ripples.end());

        // 衝撃波がなくなったらm_chainsのactiveをfalse
        if (c.m_ripples.empty())
            c.active = false;
    }
    // chainのデスポーン
    m_chains.erase(
        std::remove_if(m_chains.begin(), m_chains.end(),
                       [](ChainData &c)
                       { return !c.active; }), // 生きている衝撃波を配列の前につめる
        m_chains.end());
}

void RippleManager::Draw()
{
    for (auto &c : m_chains)
        for (auto &r : c.m_ripples)
        {
            if (r.IsActive())
                r.Draw(c.color);
        }
}

// 連鎖の開始
void RippleManager::StartChain(int col, int row, ColorId color)
{
    auto &chain = m_chains.emplace_back();
    chain.passed[col][row] = true;
    chain.color = color;
    chain.m_ripples.emplace_back(col, row);
}

// 連鎖情報を取得
std::vector<RippleManager::ChainData> &RippleManager::GetChains()
{
    return m_chains;
}