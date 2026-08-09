#include "../Core/Config.h"
#include "CutInUIManager.h"
#include "DxLib.h"

/* インゲームでのカットイン表示 */

CutInUIManager::CutInUIManager()
{
    // カットインテキストのフォント設定
    m_displayFontHandle = CreateFontToHandle(
        FONT_NAME,                     // フォント名
        TITLE_FONT_SIZE,               // フォントサイズ
        -1,                            // 太さ（-1で規定値）
        DX_FONTTYPE_ANTIALIASING_EDGE, // フォントタイプ（縁取り付きアンチエイリアス）
        -1,                            // 文字セット（-1でデフォルト）
        3                              // 縁のサイズ（EDGE系タイプ使用時）
    );
}

CutInUIManager::~CutInUIManager()
{
    DeleteFontToHandle(m_displayFontHandle);
}

void CutInUIManager::SetText(const char *text, bool isLevelUp)
{
    if (!m_isChangeText)
        return; // レベルアップ以外のテキストが表示されていたら何もセットしない

    if (isLevelUp)
    {
        m_displayTimer = DISPLAY_LEVELUP_TEXT_TIME;
        m_isChangeText = true;
    }
    else
    {
        m_displayTimer = DISPLAY_TEXT_TIME;
        m_isChangeText = false;
    }
    m_displayText = text;
    m_displayTextWidth = GetDrawStringWidthToHandle(m_displayText, -1, m_displayFontHandle);
}

void CutInUIManager::Update(float dt)
{
    if (m_displayTimer > 0.0f)
        m_displayTimer -= dt;
    else
        m_isChangeText = true;
}

void CutInUIManager::Draw()
{
    // レベルアップ表記
    if (m_displayTimer > 0.0f)
    {
        DrawStringToHandle((SCREEN_W - m_displayTextWidth) / 2, SCREEN_H / 3, m_displayText, GetColor(255, 255, 255), m_displayFontHandle);
    }
}