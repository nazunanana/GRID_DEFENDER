#include "ClearScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Core/Config.h"
#include "DxLib.h"
#include <cstdio>
#include <cstring>

/*
クリアシーン
*/

ClearScene::ClearScene(SceneManager *manager, Input *input, int score, Difficulty difficulty)
    : IScene(manager, input), m_score(score), m_difficulty(difficulty) 
{
    m_rank = GetRank();
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
    // ランク
    m_resultRankFontHandle = CreateFontToHandle(
        FONT_NAME,                     // フォント名
        RESULT_RANK_FONT_SIZE,              // フォントサイズ
        -1,                            // 太さ（-1で規定値）
        DX_FONTTYPE_ANTIALIASING_EDGE, // フォントタイプ（縁取り付きアンチエイリアス）
        -1,                            // 文字セット（-1でデフォルト）
        3                              // 縁のサイズ（EDGE系タイプ使用時）
    );
    m_resultRankTextWidth = GetDrawStringWidthToHandle(m_rank, -1, m_resultRankFontHandle);
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
    DeleteFontToHandle(m_resultRankFontHandle);
    DeleteFontToHandle(m_commandFontHandle);
}

// クリア画面に入ったときの処理
void ClearScene::Enter()
{
    AudioManager::Instance().PlayBgm("menuBgm");
}

// クリア画面を出たときの処理
void ClearScene::Exit()
{
}

// クリア画面の更新処理
void ClearScene::Update(float dt)
{
    // Decideでリトライ
    if (m_input->Pressed(Action::Decide))
    {
        AudioManager::Instance().StopBgm();
        m_sceneMgr->RequestChange(SceneType::Game, m_difficulty);
        return;
    }
    // Decide2でタイトルシーンに移行
    if (m_input->Pressed(Action::Decide2))
    {
        AudioManager::Instance().StopBgm();
        m_sceneMgr->RequestChange(SceneType::Title);
        return;
    }
}

// クリア画面の描画処理
void ClearScene::Draw()
{
    DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(5, 0, 40), true);
    DrawStringToHandle((SCREEN_W - m_resultTextWidth) / 2, SCREEN_H / 5, GAMECLEAR_TEXT, GetColor(255, 255, 255), m_resultFontHandle);
    DrawFormatStringToHandle((SCREEN_W - m_resultScoreTextWidth) / 2, SCREEN_H / 3, GetColor(255, 255, 255), m_resultScoreFontHandle, "SCORE : %d", m_score);
    DrawStringToHandle((SCREEN_W - m_resultRankTextWidth) / 2, SCREEN_H * 4 / 7, m_rank, GetColor(255, 255, 255), m_resultRankFontHandle);
    DrawStringToHandle((SCREEN_W - m_commandTextWidth) / 2, SCREEN_H * 3 / 4, COMMAND_TEXT, GetColor(255, 255, 255), m_commandFontHandle);
}

const char* ClearScene::GetRank()
{
    if(m_difficulty == Difficulty::Normal)
    {
        if(m_score >= 200000)
            return "S";
        else if(m_score >= 160000)
            return "A";
        else if(m_score >= 120000)
            return "B";
        else if(m_score >= 80000)
            return "C";
        else
            return "D";
    }
    else
    {
        if(m_score >= 320000)
            return "S";
        else if(m_score >= 260000)
            return "A";
        else if(m_score >= 200000)
            return "B";
        else if(m_score >= 160000)
            return "C";
        else
            return "D";
    }
}