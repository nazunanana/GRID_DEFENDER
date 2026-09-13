#pragma once
#include "../Entity/Ripple.h"
#include "../Core/Config.h"
#include <vector>

class BlockGrid;
class VirusManager;

class RippleManager
{
public:
    enum class ChainEventType // GameSceneに返す衝撃波イベント
    {
        CollisionVirus,
        CollisionBlock,
        None,
    };
    struct ChainData // 連鎖データ
    {
        std::vector<Ripple> m_ripples;
        bool active = true;
        ColorId color = ColorId::None; // 色
        int chainCount = 0; // 連鎖数
        bool passed[COL_MAX][ROW_MAX] = {}; // 通過フラグ
    };
    void Update(BlockGrid& grid, VirusManager& viruses, ChainEventType& outChainEvent, std::vector<int>& outChainCount, bool &isSameColor);
    void Draw();
    void StartChain(int col, int row, ColorId color);
    std::vector<ChainData> &GetChains(); // 生きている衝撃波の一覧（Virus当たり判定用）
private:
    std::vector<ChainData> m_chains; // 連鎖中配列
};
