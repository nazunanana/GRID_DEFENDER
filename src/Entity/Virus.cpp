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
    m_moveTimer += dt;
    if(m_moveTimer > moveInterval)
    {
        m_moveTimer -= moveInterval;
        m_col++;
        if(m_col > COL_MAX)
            Despawn();
    }
}

void Virus::Despawn()
{
    m_alive = false;
}

bool Virus::IsAlive()
{
    return m_alive;
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