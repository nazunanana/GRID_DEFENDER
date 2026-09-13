#include "ScoreManager.h"
#include "../Core/Config.h"
#include "DxLib.h"

ScoreManager::ScoreManager()
{
    // スコア・タイマー表示
    m_scoreFontHandle = CreateFontToHandle(
        FONT_NAME,                     // フォント名
        SCORE_FONT_SIZE,               // フォントサイズ
        -1,                            // 太さ（-1で規定値）
        DX_FONTTYPE_ANTIALIASING_EDGE, // フォントタイプ（縁取り付きアンチエイリアス）
        -1,                            // 文字セット（-1でデフォルト）
        3                              // 縁のサイズ（EDGE系タイプ使用時）
    );
}

ScoreManager::~ScoreManager()
{
    DeleteFontToHandle(m_scoreFontHandle);
}

void ScoreManager::IncreaseScore(int amount)
{
    m_score += amount;
    IsIncreaseLevel();
}

int ScoreManager::GetScore()
{
    return m_score;
}

int ScoreManager::GetLevel()
{
    return m_level;
}

void ScoreManager::IsIncreaseLevel(bool isClimax)
{
    if((IsLevelUp() || isClimax) && m_level < 5)
    {
        m_level++;
        AudioManager::Instance().PlaySe("levelUp");
    }
}

void ScoreManager::Draw(float time)
{
    // スコア表示
    DrawFormatStringToHandle(ORIGIN_X+20, (ORIGIN_Y - SCORE_FONT_SIZE) / 2, GetColor(255, 255, 255), m_scoreFontHandle,
                             "SCORE: %d", m_score);
    // 残り時間表示
    int remainingTime = static_cast<int>(TIME_LIMIT - time);
    if (remainingTime < 0) remainingTime = 0;
    DrawFormatStringToHandle(SCREEN_W - ORIGIN_X - 150, (ORIGIN_Y - SCORE_FONT_SIZE) / 2, GetColor(255, 255, 255), m_scoreFontHandle,
                             "TIME: %d", remainingTime);
}

// レベルアップできるかどうか
bool ScoreManager::IsLevelUp()
{
    switch(m_level)
    {
    case 1:
        return m_score > 25000;
    case 2:
        return m_score > 50000;
    case 3:
        return m_score > 100000;
    case 4:
        return m_score > 150000;
    default:
        return m_score > 200000;
    }
}