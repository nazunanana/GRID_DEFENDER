#include "Player.h"
#include "DxLib.h"

using namespace DxLib;

/*
プレイヤー
*/

void Player::Update(bool isInput, Vec2 pos)
{
    isShoot = false;
    m_pos = pos;
    if (isInput) // クールタイム条件も足す
        isShoot = true;
}

void Player::Draw()
{
    DrawLine(m_pos.x - LINE_LENGTH, m_pos.y,
             m_pos.x + LINE_LENGTH, m_pos.y,
             GetColor(255, 255, 255), LINE_THICKNESS);
    DrawLine(m_pos.x, m_pos.y - LINE_LENGTH,
             m_pos.x, m_pos.y + LINE_LENGTH,
             GetColor(255, 255, 255), LINE_THICKNESS);
    DrawCircle(m_pos.x, m_pos.y, CIRCLE_RADIUS, GetColor(255, 255, 255), FALSE, LINE_THICKNESS);
}

Vec2 Player::GetPos()
{
    return m_pos;
}