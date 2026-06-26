#include "ClearScene.h"
#include "SceneManager.h"
#include "../Input/input.h"

#include "DxLib.h"

/*
クリアシーン
*/

ClearScene::ClearScene(SceneManager* manager, Input* input)
    : IScene(manager, input) {}

// クリア画面に入ったときの処理
void ClearScene::Enter()
{
}

// クリア画面を出たときの処理
void ClearScene::Exit()
{
    
}

// クリア画面の更新処理
void ClearScene::Update()
{
    // Decideでタイトルシーンに移行
    if (m_input->Pressed(Action::Decide))
    {
        m_sceneMgr->RequestChange(SceneType::Title);
        return;
    }
}

// クリア画面の描画処理
void ClearScene::Draw()
{
    DrawBox(0, 0, 1280, 720, GetColor(10, 10, 20), true);
    DrawString(200, 200, "CLEAR", GetColor(255, 255, 255));
    DrawString(200, 260, "PRESS START", GetColor(200, 200, 200));
}