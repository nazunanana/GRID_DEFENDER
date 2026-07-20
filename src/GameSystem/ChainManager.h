#pragma once
#include "../Entity/Ripple.h"
#include <queue>
#include <vector>

class ChainManager
{
public:
    void Update();
    void Draw();
    void GenerateRipple(int col, int row, ColorId color, int chainLevel);
    struct ExpandedRipple { int col; int row; ColorId color; int chainLevel; };
    bool HasExpandedRipple();
    ExpandedRipple PopExpandedRipple();
private:
    std::vector<Ripple> m_ripples;
    std::queue<ExpandedRipple> m_expandedRipples;
};