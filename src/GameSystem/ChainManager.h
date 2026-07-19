#pragma once
#include "../Entity/Ripple.h"
#include <queue>
#include <vector>

class ChainManager
{
public:
    void Update();
    void Draw();
    void GenerateRipple(int col, int row, ColorId color);
    struct ExpandedRipple { int col; int row; ColorId color; };
    bool HasExpandedRipple();
    ExpandedRipple PopExpandedRipple();
private:
    std::vector<Ripple> m_ripples;
    std::queue<ExpandedRipple> m_expandedRipples;
};