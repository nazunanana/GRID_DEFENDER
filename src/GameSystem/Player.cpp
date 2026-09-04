#include "Player.h"
#include "DxLib.h"
#include "../Core/Config.h"

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
    DrawLine(m_pos.x - CURSOR_LINE_LENGTH, m_pos.y,
             m_pos.x + CURSOR_LINE_LENGTH, m_pos.y,
             GetColor(255, 255, 255), CURSOR_THICKNESS);
    DrawLine(m_pos.x, m_pos.y - CURSOR_LINE_LENGTH,
             m_pos.x, m_pos.y + CURSOR_LINE_LENGTH,
             GetColor(255, 255, 255), CURSOR_THICKNESS);
    DrawCircle(m_pos.x, m_pos.y, CURSOR_RADIUS, GetColor(255, 255, 255), FALSE, CURSOR_THICKNESS);
}

Vec2 Player::GetPos()
{
    return m_pos;
}