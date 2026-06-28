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
    DrawBox(screenX, screenY, screenX + BOX_SIZE, screenY + BOX_SIZE,
            GetColor(200, 200, 200), FALSE);
    // ブロック枠線を足す
    if(screenX == ORIGIN_X)
        DrawBox(0, screenY, BOX_SIZE, screenY + BOX_SIZE,
            GetColor(200, 200, 200), FALSE);
    else if(screenX == ORIGIN_X + BOX_SIZE * (ROW_MAX - 1))
        DrawBox(screenX + BOX_SIZE, screenY, screenX + BOX_SIZE * 2, screenY + BOX_SIZE,
            GetColor(200, 200, 200), FALSE);

    // TODO: ヒットしたときは一瞬光らせる
}

void Block::Hit(int color)
{
    m_color = color;
}

unsigned int Block::ToDrawColor(int colorId)
{
    switch (colorId)
    {
    case 0:
        return GetColor(255, 60, 200); // Magenta
    case 1:
        return GetColor(60, 255, 255); // Cyan
    case 2:
        return GetColor(255, 255, 60); // Yellow
    default:
        return GetColor(10, 10, 10); // 無色
    }
}