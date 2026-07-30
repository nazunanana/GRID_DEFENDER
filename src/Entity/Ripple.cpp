#include "Ripple.h"
#include "DxLib.h"
#include "../Core/Config.h"

/*
波紋
*/

Ripple::Ripple(int screenX, int screenY, ColorId color, int chainLevel)
    : m_screenX(screenX), m_screenY(screenY), m_color(color), m_chainLevel(chainLevel)
    {
        m_size = BOX_SIZE / 2.0f;
        m_isActive = true;
    }

bool Ripple::Update()
{
    if (!m_isActive) return false;
    m_size += SPEED;

    // 最大サイズになったら消滅フラグ
    if (m_size / static_cast<float>(BOX_SIZE) >= MAX_LEVEL)
        m_isActive = false;

    return true;
}

void Ripple::Draw()
{
    if (!m_isActive || m_color == ColorId::None) return;
    // 中心位置
    DrawBoxAA(m_screenX - m_size, m_screenY - m_size, m_screenX + m_size, m_screenY + m_size, ToDrawColor(m_color), FALSE, 2.0f);
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

int Ripple::GetChainLevel()
{
    return m_chainLevel;
}

bool Ripple::IsActive()
{
    return m_isActive;
}

unsigned int Ripple::ToDrawColor(ColorId colorId)
{
    switch (colorId)
    {
    case ColorId::Magenta:
        return GetColor(230, 0, 126);
    case ColorId::Cyan:
        return GetColor(0, 237, 250);
    case ColorId::Purple:
        return GetColor(134, 36, 255);
    default:
        return GetColor(255, 255, 255);
    }
}