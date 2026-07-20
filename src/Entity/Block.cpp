#include "Block.h"
#include "../Core/Config.h"
#include "DxLib.h"

using namespace DxLib;

/*
ブロック
*/

void Block::Update()
{
}

void Block::Draw(int screenX, int screenY)
{
    // 塗りつぶしブロック
    DrawBox(screenX, screenY, screenX + BOX_SIZE, screenY + BOX_SIZE,
            ToDrawColor(m_color), TRUE);
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

    // TODO: ヒットしたときは一瞬光らせる
}

void Block::Hit(ColorId color)
{
    m_color = color;
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