#include "GameScene.h"
#include "SceneManager.h"
#include "../Input/input.h"
#include "../Core/Config.h"

#include "DxLib.h"

/*
ゲームシーン
*/

GameScene::GameScene(SceneManager* manager, Input* input)
    : IScene(manager, input) {}

// ゲーム画面に入ったときの処理
void GameScene::Enter()
{
    // 仮
    isStart = true;
}

// ゲーム画面を出たときの処理
void GameScene::Exit()
{
    
}

// ゲーム画面の更新処理
void GameScene::Update()
{
    // if (m_input->Pressed(Action::Decide))// Decideでゲームシーンに移行
    // {
    //     m_sceneMgr->RequestChange(SceneType::Clear);
    //     return;
    // }
}

// ゲーム画面の描画処理
void GameScene::Draw()
{
    DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(10, 10, 20), true);
}