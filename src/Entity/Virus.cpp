#include "Virus.h"
#include "../Core/Config.h"
#include "DxLib.h"

/*
敵（ウィルス）
*/

Virus::Virus(int row, int color)
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

int Virus::GetColor()
{
    return m_color;
}

// unsigned int Block::ToDrawColor(int colorId)
// {
//     switch (colorId)
//     {
//     case 0:
//         return GetColor(255, 60, 200); // Magenta
//     case 1:
//         return GetColor(60, 255, 255); // Cyan
//     case 2:
//         return GetColor(255, 255, 60); // Yellow
//     default:
//         return GetColor(5, 0, 40); // 無色
//     }
// }