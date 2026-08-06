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
    // レベルアップ表示
    m_displayFontHandle = CreateFontToHandle(
        FONT_NAME,                     // フォント名
        TITLE_FONT_SIZE,               // フォントサイズ
        -1,                            // 太さ（-1で規定値）
        DX_FONTTYPE_ANTIALIASING_EDGE, // フォントタイプ（縁取り付きアンチエイリアス）
        -1,                            // 文字セット（-1でデフォルト）
        3                              // 縁のサイズ（EDGE系タイプ使用時）
    );
    m_displayTextWidth = GetDrawStringWidthToHandle("LEVEL UP", -1, m_displayFontHandle);
}

ScoreManager::~ScoreManager()
{
    DeleteFontToHandle(m_scoreFontHandle);
    DeleteFontToHandle(m_displayFontHandle);
}

void ScoreManager::IncreaseScore(int amount)
{
    m_score += amount;
    if(IsIncreaseLevel())
        m_levelUpTimer = DISPLAY_LEVELUP_TIME;
}

int ScoreManager::GetScore()
{
    return m_score;
}

int ScoreManager::GetLevel()
{
    return m_level;
}

bool ScoreManager::IsIncreaseLevel()
{
    if(m_score > m_level * SCORE_PER_LEVEL && m_level < 4)
    {
        m_level++;
        AudioManager::Instance().PlaySe("levelUp");
        return true;
    }
    return false;
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
    // レベルアップ表記
    if(m_levelUpTimer > 0.0f)
        DrawStringToHandle((SCREEN_W - m_displayTextWidth) / 2, SCREEN_H / 3, "LEVEL UP", GetColor(255, 255, 255), m_displayFontHandle);
}

void ScoreManager::Update(float dt)
{
    if (m_levelUpTimer > 0.0f) m_levelUpTimer -= dt;
}
