#include "ClearScene.h"
#include "SceneManager.h"
#include "../Input/input.h"
#include "../Core/Config.h"
#include "DxLib.h"
#include <cstdio>
#include <cstring>

/*
クリアシーン
*/

ClearScene::ClearScene(SceneManager *manager, Input *input, int score)
    : IScene(manager, input), m_score(score)
{
    // ゲームクリア
    m_resultFontHandle = CreateFontToHandle(
        FONT_NAME,                     // フォント名
        TITLE_FONT_SIZE,              // フォントサイズ
        -1,                            // 太さ（-1で規定値）
        DX_FONTTYPE_ANTIALIASING_EDGE, // フォントタイプ（縁取り付きアンチエイリアス）
        -1,                            // 文字セット（-1でデフォルト）
        3                              // 縁のサイズ（EDGE系タイプ使用時）
    );
    m_resultTextWidth = GetDrawStringWidthToHandle(GAMECLEAR_TEXT, -1, m_resultFontHandle);
    // スコア
    m_resultScoreFontHandle = CreateFontToHandle(
        FONT_NAME,                     // フォント名
        RESULT_SCORE_FONT_SIZE,              // フォントサイズ
        -1,                            // 太さ（-1で規定値）
        DX_FONTTYPE_ANTIALIASING_EDGE, // フォントタイプ（縁取り付きアンチエイリアス）
        -1,                            // 文字セット（-1でデフォルト）
        3                              // 縁のサイズ（EDGE系タイプ使用時）
    );
    m_resultScoreTextWidth = GetDrawFormatStringWidthToHandle(m_resultScoreFontHandle, "SCORE : %d", m_score);
    // コマンド
    m_commandFontHandle = CreateFontToHandle(
        FONT_NAME,                     // フォント名
        COMMAND_FONT_SIZE,              // フォントサイズ
        -1,                            // 太さ（-1で規定値）
        DX_FONTTYPE_ANTIALIASING_EDGE, // フォントタイプ（縁取り付きアンチエイリアス）
        -1,                            // 文字セット（-1でデフォルト）
        3                              // 縁のサイズ（EDGE系タイプ使用時）
    );
    m_commandTextWidth = GetDrawStringWidthToHandle(COMMAND_TEXT, -1, m_commandFontHandle);
}

ClearScene::~ClearScene()
{
    DeleteFontToHandle(m_resultFontHandle);
    DeleteFontToHandle(m_resultScoreFontHandle);
    DeleteFontToHandle(m_commandFontHandle);
}

// クリア画面に入ったときの処理
void ClearScene::Enter()
{
}

// クリア画面を出たときの処理
void ClearScene::Exit()
{
}

// クリア画面の更新処理
void ClearScene::Update(float dt)
{
    // Decideでタイトルシーンに移行
    if (m_input->Pressed(Action::Decide))
    {
        m_sceneMgr->RequestChange(SceneType::Game);
        return;
    }
}

// クリア画面の描画処理
void ClearScene::Draw()
{
    DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(5, 0, 40), true);
    DrawStringToHandle((SCREEN_W - m_resultTextWidth) / 2, SCREEN_H / 5, GAMECLEAR_TEXT, GetColor(255, 255, 255), m_resultFontHandle);
    DrawFormatStringToHandle((SCREEN_W - m_resultScoreTextWidth) / 2, SCREEN_H / 3, GetColor(255, 255, 255), m_resultScoreFontHandle, "SCORE : %d", m_score);
    DrawStringToHandle((SCREEN_W - m_commandTextWidth) / 2, SCREEN_H * 3 / 4, COMMAND_TEXT, GetColor(255, 255, 255), m_commandFontHandle);
}