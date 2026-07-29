#include "Block.h"
#include "../Core/Config.h"
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
            ToDrawColor(m_color), TRUE);

    // 発光
    if (m_brightness > 0)
    {
        SetDrawBlendMode(DX_BLENDMODE_ADD, m_brightness);
        DrawBox(screenX, screenY, screenX + BOX_SIZE, screenY + BOX_SIZE,
                GetColor(255, 255, 255), TRUE);
        // 発光やめる
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    // ブロック枠線
    // DrawBox(screenX, screenY, screenX + BOX_SIZE, screenY + BOX_SIZE,
    //         GetColor(70, 70, 120), FALSE);
    // ブロック枠線を足す
    // if(screenX == ORIGIN_X)
    //     DrawBox(0, screenY, BOX_SIZE, screenY + BOX_SIZE,
    //         GetColor(200, 200, 200), FALSE);
    // else if(screenX == ORIGIN_X + BOX_SIZE * (ROW_MAX - 1))
    //     DrawBox(screenX + BOX_SIZE, screenY, screenX + BOX_SIZE * 2, screenY + BOX_SIZE,
    //         GetColor(200, 200, 200), FALSE);
}

void Block::Hit(ColorId color)
{
    m_color = color;
    m_brightness = 120;
}

unsigned int Block::ToDrawColor(ColorId colorId)
{
    switch (colorId)
    {
    case ColorId::Magenta:
        return GetColor(255, 50, 150);
    case ColorId::Cyan:
        return GetColor(100, 255, 255);
    case ColorId::Purple:
        return GetColor(160, 80, 255);
    default:
        return GetColor(5, 0, 40); // 無色
    }
}

ColorId Block::GetBlockColor()
{
    return m_color;
}