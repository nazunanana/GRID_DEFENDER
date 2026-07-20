#include "ScoreManager.h"
#include "../Core/Config.h"
#include "DxLib.h"

ScoreManager::ScoreManager()
{
    // フォント
    m_fontHandle = CreateFontToHandle(
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
    DeleteFontToHandle(m_fontHandle);
}

void ScoreManager::IncreaseScore(int amount)
{
    m_score += amount;
}

int ScoreManager::GetScore()
{
    return m_score;
}

void ScoreManager::Draw()
{
    // スコア表示
    DrawFormatStringToHandle(ORIGIN_X, (BOX_SIZE - SCORE_FONT_SIZE) / 2, GetColor(255, 255, 255), m_fontHandle,
                             "SCORE: %d", m_score);
}
