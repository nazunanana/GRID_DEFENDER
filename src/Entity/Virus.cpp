#include "Virus.h"
#include "../Core/Config.h"
#include "DxLib.h"

/*
敵（ウィルス）
*/

Virus::Virus(int row, ColorId color)
    : m_row(row), m_color(color) {}

void Virus::Update(float dt, float moveInterval)
{
    if (m_state == State::Despawned) return;
    else if (m_state == State::Despawning)
    {
        m_despawnTimer += dt;
        if (m_despawnTimer >= DESPAWN_TIME)
            m_state = State::Despawned;
        return;
    }

    m_moveInterval = moveInterval;
    m_moveTimer += dt;
    if (m_moveTimer > moveInterval)
    {
        m_moveTimer -= moveInterval;
        m_col++;
        if (m_col > COL_MAX) // 一番下まで到達
        {
            m_leaked = true;
            Despawn();
        }
    }
}

void Virus::Despawn()
{
    if (m_state != State::Alive)
        return;
    m_state = State::Despawning;
    m_despawnTimer = 0.0f;
}

bool Virus::IsAlive()
{
    return m_state == State::Alive;
}

bool Virus::IsDespawned()
{
    return m_state == State::Despawned;
}

bool Virus::IsVisible()
{
    if (m_state == State::Alive)
        return true;
    else if (m_state == State::Despawned)
        return false;
    // Despawningの時はオンオフが切り替わる
    else if (m_despawnTimer < BLINK_TIME)
        return false;
    return true;
}

bool Virus::ConsumeLeak()
{
    if (m_leaked)
    {
        m_leaked = false;
        return true;
    }
    return false;
}

int Virus::GetCol()
{
    return m_col;
}

int Virus::GetRow()
{
    return m_row;
}

ColorId Virus::GetColor()
{
    return m_color;
}

int Virus::GetDrawY()
{
    float speed = static_cast<float>(BOX_SIZE) / m_moveInterval; // 1秒あたりの移動px数
    float y = ORIGIN_Y + m_col * BOX_SIZE - BOX_SIZE / 2.0f + speed * m_moveTimer;
    return static_cast<int>(y);
}