#include "TitleScene.h"
#include "SceneManager.h"
#include "../Input/input.h"

#include "DxLib.h"

/*
タイトルシーン
*/

TitleScene::TitleScene(SceneManager* manager, Input* input)
    : IScene(manager, input) {}

// タイトル画面に入ったときの処理
void TitleScene::Enter()
{
}

// タイトル画面を出たときの処理
void TitleScene::Exit()
{
    
}

// タイトル画面の更新処理
void TitleScene::Update(float dt)
{
    // Decideでゲームシーンに移行
    if (m_input->Pressed(Action::Decide))
    {
        m_sceneMgr->RequestChange(SceneType::Game);
        return;
    }
}

// タイトル画面の描画処理
void TitleScene::Draw()
{
    DrawBox(0, 0, 1280, 720, GetColor(10, 10, 20), true);
    DrawString(200, 200, "GRID DEFENDER", GetColor(255, 255, 255));
    DrawString(200, 260, "PRESS START", GetColor(200, 200, 200));
}