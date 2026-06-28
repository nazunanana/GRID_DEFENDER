#include "GameScene.h"
#include "SceneManager.h"
#include "../Input/input.h"
#include "../Core/Config.h"
#include "DxLib.h"

using namespace DxLib;

/*
ゲームシーン
*/

GameScene::GameScene(SceneManager *manager, Input *input)
    : IScene(manager, input) {}

// ゲーム画面に入ったときの処理
void GameScene::Enter()
{
    coreTex = LoadGraph("img/core_tex.png");
    frameImg = LoadGraph("img/frame.png");
    // 仮
    isStart = true;
}

// ゲーム画面を出たときの処理
void GameScene::Exit()
{
    DeleteGraph(coreTex);
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
    DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), true);

    m_blockGrid.Draw();

    // メインコア
    DrawExtendGraph(0, COL_MAX * BOX_SIZE + ORIGIN_Y, SCREEN_W, SCREEN_H - ORIGIN_Y,
                    coreTex, TRUE);

    // フレーム
    DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H,
                    frameImg, TRUE);
}