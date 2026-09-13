#include "Block.h"
#include "../Core/Config.h"
#include "../GameSystem/Common.h"
#include "DxLib.h"
#include <algorithm>

using namespace DxLib;

/*
ブロック
*/

void Block::Update()
{
    if (m_brightness > 0)
        m_brightness = std::max(0, m_brightness - 10);
}

void Block::Draw(int screenX, int screenY)
{
    // 塗りつぶしブロック
    DrawBox(screenX, screenY, screenX + BOX_SIZE, screenY + BOX_SIZE,
            BlockColor(m_color), TRUE);

    // 発光
    if (m_brightness > 0)
    {
        SetDrawBlendMode(DX_BLENDMODE_ADD, m_brightness);
        DrawBox(screenX, screenY, screenX + BOX_SIZE, screenY + BOX_SIZE,
                GetColor(255, 255, 255), TRUE);
        // 発光やめる
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

void Block::Hit(ColorId color)
{
    m_color = color;
    m_brightness = 120;
}

void Block::Bright()
{
    m_brightness = 25;
}

ColorId Block::GetBlockColor()
{
    return m_color;
}