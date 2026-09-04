#include "GameoverScene.h"
#include "SceneManager.h"
#include "../Input/input.h"
#include "../Core/Config.h"
#include "DxLib.h"
#include <cstdio>
#include <cstring>

/*
ゲームオーバーシーン
*/

GameoverScene::GameoverScene(SceneManager *manager, Input *input, int score, float remainingTime, Difficulty difficulty)
    : IScene(manager, input), m_score(score), m_remainingTime(remainingTime), m_difficulty(difficulty)
{
    m_rank = GetRank();
    // ゲームオーバー
    m_resultFontHandle = CreateFontToHandle(
        FONT_NAME,                     // フォント名
        TITLE_FONT_SIZE,               // フォントサイズ
        -1,                            // 太さ（-1で規定値）
        DX_FONTTYPE_ANTIALIASING_EDGE, // フォントタイプ（縁取り付きアンチエイリアス）
        -1,                            // 文字セット（-1でデフォルト）
        3                              // 縁のサイズ（EDGE系タイプ使用時）
    );
    m_resultTextWidth = GetDrawStringWidthToHandle(GAMEOVER_TEXT, -1, m_resultFontHandle);
    // スコア・残り時間
    m_resultScoreFontHandle = CreateFontToHandle(
        FONT_NAME,                     // フォント名
        RESULT_SCORE_FONT_SIZE,        // フォントサイズ
        -1,                            // 太さ（-1で規定値）
        DX_FONTTYPE_ANTIALIASING_EDGE, // フォントタイプ（縁取り付きアンチエイリアス）
        -1,                            // 文字セット（-1でデフォルト）
        3                              // 縁のサイズ（EDGE系タイプ使用時）
    );
    m_resultScoreTextWidth = GetDrawFormatStringWidthToHandle(m_resultScoreFontHandle, "SCORE : %d", m_score);
    m_resultTimeTextWidth = GetDrawFormatStringWidthToHandle(m_resultScoreFontHandle, "TIME LEFT : %.1f", m_remainingTime);
    // ランク
    m_resultRankFontHandle = CreateFontToHandle(
        FONT_NAME,                     // フォント名
        RESULT_RANK_FONT_SIZE,         // フォントサイズ
        -1,                            // 太さ（-1で規定値）
        DX_FONTTYPE_ANTIALIASING_EDGE, // フォントタイプ（縁取り付きアンチエイリアス）
        -1,                            // 文字セット（-1でデフォルト）
        3                              // 縁のサイズ（EDGE系タイプ使用時）
    );
    m_resultRankTextWidth = GetDrawStringWidthToHandle(m_rank, -1, m_resultRankFontHandle);
    // コマンド
    m_commandFontHandle = CreateFontToHandle(
        FONT_NAME,                     // フォント名
        COMMAND_FONT_SIZE,             // フォントサイズ
        -1,                            // 太さ（-1で規定値）
        DX_FONTTYPE_ANTIALIASING_EDGE, // フォントタイプ（縁取り付きアンチエイリアス）
        -1,                            // 文字セット（-1でデフォルト）
        3                              // 縁のサイズ（EDGE系タイプ使用時）
    );
    m_commandTextWidth = GetDrawStringWidthToHandle(COMMAND_TEXT, -1, m_commandFontHandle);
}

GameoverScene::~GameoverScene()
{
    DeleteFontToHandle(m_resultFontHandle);
    DeleteFontToHandle(m_resultScoreFontHandle);
    DeleteFontToHandle(m_resultRankFontHandle);
    DeleteFontToHandle(m_commandFontHandle);
}

// ゲームオーバー画面に入ったときの処理
void GameoverScene::Enter()
{
    AudioManager::Instance().PlayBgm("menuBgm");
}

// ゲームオーバー画面を出たときの処理
void GameoverScene::Exit()
{
}

// ゲームオーバー画面の更新処理
void GameoverScene::Update(float dt)
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

// ゲームオーバー画面の描画処理
void GameoverScene::Draw()
{
    DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(5, 0, 40), true);
    DrawStringToHandle((SCREEN_W - m_resultTextWidth) / 2, SCREEN_H / 5, GAMEOVER_TEXT, GetColor(255, 255, 255), m_resultFontHandle);
    DrawFormatStringToHandle((SCREEN_W - m_resultScoreTextWidth) / 2, SCREEN_H / 3, GetColor(255, 255, 255), m_resultScoreFontHandle, "SCORE : %d", m_score);
    DrawFormatStringToHandle((SCREEN_W - m_resultTimeTextWidth) / 2, SCREEN_H / 3 + 40, GetColor(255, 255, 255), m_resultScoreFontHandle, "TIME LEFT : %.1f", m_remainingTime);
    //DrawStringToHandle((SCREEN_W - m_resultRankTextWidth) / 2, SCREEN_H * 4 / 7, m_rank, GetColor(255, 255, 255), m_resultRankFontHandle);
    DrawStringToHandle((SCREEN_W - m_commandTextWidth) / 2, SCREEN_H * 3 / 4, COMMAND_TEXT, GetColor(255, 255, 255), m_commandFontHandle);
}

const char *GameoverScene::GetRank()
{
    if(m_difficulty == Difficulty::Normal)
    {
        if(m_score >= 300000)
            return "S";
        else if(m_score >= 240000)
            return "A";
        else if(m_score >= 180000)
            return "B";
        else if(m_score >= 120000)
            return "C";
        else
            return "D";
    }
    else
    {
        if(m_score >= 340000)
            return "S";
        else if(m_score >= 280000)
            return "A";
        else if(m_score >= 220000)
            return "B";
        else if(m_score >= 160000)
            return "C";
        else
            return "D";
    }
}