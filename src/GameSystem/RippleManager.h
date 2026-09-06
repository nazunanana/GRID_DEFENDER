#pragma once
#include "../Entity/Ripple.h"
#include <vector>

class RippleManager
{
public:
    void Update();
    void Draw();
    void GenerateRipple(int col, int row, ColorId color, int rippleLevel);
    std::vector<Ripple>& GetRipples(); // 生きている衝撃波の一覧（Virus当たり判定用）
private:
    std::vector<Ripple> m_ripples;
};
