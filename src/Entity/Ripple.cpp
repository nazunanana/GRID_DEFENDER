#include "Ripple.h"
#include "DxLib.h"
#include "../Core/Config.h"
#include "../GameSystem/Common.h"

/*
衝撃波
*/

Ripple::Ripple(int col, int row)
    : m_col(col), m_row(row)
    {
        m_size = BOX_SIZE / 2.0f;
        m_isActive = true;
        m_sizeLevel = 1;
    }

void Ripple::Update(bool &isExpand)
{
    isExpand = false;
    if (!m_isActive) return;
    m_size += SPEED;

    // 衝撃波が一定の大きさを超えたら（ブロックとの衝突判定）
    if(static_cast<float>(m_size / BOX_SIZE) > m_sizeLevel)
    {
        m_sizeLevel++;
        isExpand = true;
    }
    // 最大サイズになったら消滅フラグ
    else if (static_cast<float>(m_size / BOX_SIZE) >= MAX_SIZE)
        m_isActive = false;
}

void Ripple::Draw(ColorId color)
{
    if (!m_isActive || color == ColorId::None) return;
    // 中心位置
    //DrawBoxAA(m_screenX - m_size, m_screenY - m_size, m_screenX + m_size, m_screenY + m_size, RippleColor(color), FALSE, 2.0f);
    DrawBoxAA(ORIGIN_X + m_row * m_size, ORIGIN_Y + m_col * m_size,
        ORIGIN_X + (m_row + 1) * m_size, ORIGIN_Y + (m_col + 1) * m_size, RippleColor(color), FALSE, 2.0f);
}

int Ripple::GetCol()
{
    return m_col;
}

int Ripple::GetRow()
{
    return m_row;
}

float Ripple::GetScreenX()
{
    return ORIGIN_X + GetRow() * BOX_SIZE + (BOX_SIZE / 2);
}

float Ripple::GetScreenY()
{
    return ORIGIN_Y + GetCol() * BOX_SIZE + (BOX_SIZE / 2);
}

float Ripple::GetSize()
{
    return m_size;
}

bool Ripple::IsActive()
{
    return m_isActive;
}

int Ripple::GetSizeLevel()
{
    return m_sizeLevel;
}