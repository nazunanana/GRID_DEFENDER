#include "GameoverScene.h"
#include "SceneManager.h"
#include "Input.h"

#include "DxLib.h"

/*
ゲームオーバーシーン
*/

// // ゲームオーバー画面に入ったときの処理
// void GameoverScene::Enter()
// {
// }

// ゲームオーバー画面の更新処理
void GameoverScene::Update()
{
    // Decideでタイトルシーンに移行
    if (m_input->Pressed(Action::Decide))
    {
        m_sceneMgr->RequestChange(SceneType::Title);
        return;
    }
}

// ゲームオーバー画面の描画処理
void GameoverScene::Draw()
{
    DrawBox(0, 0, 1280, 720, GetColor(10, 10, 20), true);
    DrawString(200, 200, "GAME OVER", GetColor(255, 255, 255));
    DrawString(200, 260, "PRESS START", GetColor(200, 200, 200));
}