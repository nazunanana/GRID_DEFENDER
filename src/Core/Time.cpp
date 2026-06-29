#include "Time.h"
#include "DxLib.h"

/*
タイマー制御
*/

// タイマーリセット
void Time::Reset()
{
	m_prev = GetNowCount();
	m_delta = 0.0f;
}

// タイマーカウント
void Time::Update()
{
	int now = GetNowCount();
	m_delta = (now - m_prev) / 1000.0f;
	m_prev = now;
}