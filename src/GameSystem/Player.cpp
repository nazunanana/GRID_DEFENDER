#include "Player.h"
#include "DxLib.h"

using namespace DxLib;

/*
プレイヤー
*/

void Player::Update(bool isInput)
{
    if (isInput) // クールタイム条件も足す
        isShoot = true;
}

void Player::Draw(Vec2 mousePos)
{
    DrawLine(mousePos.x - LINE_LENGTH, mousePos.y,
             mousePos.x + LINE_LENGTH, mousePos.y,
             GetColor(255, 255, 255), LINE_THICKNESS);
    DrawLine(mousePos.x, mousePos.y - LINE_LENGTH,
             mousePos.x, mousePos.y + LINE_LENGTH,
             GetColor(255, 255, 255), LINE_THICKNESS);
    DrawCircle(mousePos.x, mousePos.y, CIRCLE_RADIUS, GetColor(255, 255, 255), FALSE, LINE_THICKNESS);
}