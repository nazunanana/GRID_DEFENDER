#include "TitleScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Core/Config.h"
#include "DxLib.h"

/*
タイトルシーン
*/

TitleScene::TitleScene(SceneManager *manager, Input *input)
    : IScene(manager, input)
{
    // タイトル
    m_titleFontHandle = CreateFontToHandle(
        FONT_NAME,                     // フォント名
        TITLE_FONT_SIZE,              // フォントサイズ
        -1,                            // 太さ（-1で規定値）
        DX_FONTTYPE_ANTIALIASING_EDGE, // フォントタイプ（縁取り付きアンチエイリアス）
        -1,                            // 文字セット（-1でデフォルト）
        3                              // 縁のサイズ（EDGE系タイプ使用時）
    );
    m_titleTextWidth = GetDrawStringWidthToHandle(TITLE_TEXT, -1, m_titleFontHandle);
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

TitleScene::~TitleScene()
{
    DeleteFontToHandle(m_titleFontHandle);
    DeleteFontToHandle(m_commandFontHandle);
}

// タイトル画面に入ったときの処理
void TitleScene::Enter()
{
    AudioManager::Instance().PlayBgm("menuBgm");
}

// タイトル画面を出たときの処理
void TitleScene::Exit()
{

}

// タイトル画面の更新処理
void TitleScene::Update(float dt)
{
    // ゲームシーンに移行
    // Decideでノーマルモード
    if (m_input->Pressed(Action::Decide))
    {
        m_sceneMgr->RequestChange(SceneType::Game, Difficulty::Normal);
        AudioManager::Instance().StopBgm();
        return;
    }

    // Decide2でハードモード
    if (m_input->Pressed(Action::Decide2))
    {
        m_sceneMgr->RequestChange(SceneType::Game, Difficulty::Hard);
        AudioManager::Instance().StopBgm();
        return;
    }

    // Decide3で遊び方画面
    if (m_input->Pressed(Action::Decide3))
    {
        m_sceneMgr->RequestChange(SceneType::Rule);
        return;
    }
}

// タイトル画面の描画処理
void TitleScene::Draw()
{
    DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(5, 0, 40), true);
    DrawStringToHandle((SCREEN_W - m_titleTextWidth) / 2, SCREEN_H / 5, TITLE_TEXT, GetColor(255, 255, 255), m_titleFontHandle);
    DrawStringToHandle((SCREEN_W - m_commandTextWidth) / 2, SCREEN_H * 3 / 4, COMMAND_TEXT, GetColor(255, 255, 255), m_commandFontHandle);
    //DrawStringToHandle((SCREEN_W - m_commandTextWidth) / 2, SCREEN_H * 4 / 5, "[V] RULE", GetColor(255, 255, 255), m_commandFontHandle);
}