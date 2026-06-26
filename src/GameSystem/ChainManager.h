#pragma once
#include "Ripple.h"
#include <queue>
#include <vector>

class ChainManager
{
public:
    void Update();
    void Draw();
    void GenerateRipple(int col, int row, int color);
    struct ExpandedRipple { int col; int row; int color; };
    bool PopExpandedRipple(int col, int row, int color);
private:
    std::vector<Ripple> m_ripples;
    std::queue<ExpandedRipple> m_expandedRipples;
};