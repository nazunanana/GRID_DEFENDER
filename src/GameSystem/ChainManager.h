#pragma once
#include "../Entity/Ripple.h"
#include <vector>

class ChainManager
{
public:
    void Update();
    void Draw();
    void GenerateRipple(int col, int row, ColorId color, int chainLevel);
    std::vector<Ripple>& GetRipples(); // 生きている波紋の一覧（Virus当たり判定用）
private:
    std::vector<Ripple> m_ripples;
};
