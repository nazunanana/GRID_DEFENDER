#include "Ripple.h"
#include "DxLib.h"
#include "../Core/Config.h"
#include "../GameSystem/Common.h"

/*
衝撃波
*/

Ripple::Ripple(int screenX, int screenY, ColorId color, int rippleLevel)
    : m_screenX(screenX), m_screenY(screenY), m_color(color), m_rippleLevel(rippleLevel)
    {
        m_size = BOX_SIZE / 2.0f;
        m_isActive = true;
    }

bool Ripple::Update()
{
    if (!m_isActive) return false;
    m_size += SPEED;

    // 最大サイズになったら消滅フラグ
    if (m_size / static_cast<float>(BOX_SIZE) >= MAX_SIZE)
        m_isActive = false;

    return true;
}

void Ripple::Draw()
{
    if (!m_isActive || m_color == ColorId::None) return;
    // 中心位置
    DrawBoxAA(m_screenX - m_size, m_screenY - m_size, m_screenX + m_size, m_screenY + m_size, RippleColor(m_color), FALSE, 2.0f);
}

int Ripple::GetScreenX()
{
    return m_screenX;
}

int Ripple::GetScreenY()
{
    return m_screenY;
}

float Ripple::GetSize()
{
    return m_size;
}

ColorId Ripple::GetRippleColor()
{
    return m_color;
}

int Ripple::GetRippleLevel()
{
    return m_rippleLevel;
}

bool Ripple::IsActive()
{
    return m_isActive;
}