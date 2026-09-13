#pragma once
#include "../GameSystem/Common.h"

class Virus
{
public:
    Virus(int row, ColorId color);
    enum class State
    {
        Alive,
        Despawning,
        Despawned
    };
    void Update(float dt, float moveInterval);
    void Despawn();
    int GetCol();
    int GetRow();
    ColorId GetColor();
    bool IsAlive();
    bool IsDespawned();
    bool IsVisible();
    bool ConsumeLeak();
    int GetDrawY();
private:
    int m_col = 0;
    int m_row;
    ColorId m_color;
    float m_moveTimer = 0.0f;
    float m_moveInterval;
    State m_state = State::Alive;
    bool  m_leaked = false;
    float m_despawnTimer = 0.0f;
    static constexpr float BLINK_TIME = 0.02f; // 点滅の切り替え間隔
    static constexpr float DESPAWN_TIME = BLINK_TIME * 2; // 点滅演出の合計時間
};