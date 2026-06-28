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
    // 各クラスのUpdateを呼び出す
    m_input.Update();
    m_player.Update(m_input.Pressed(Action::Shoot), m_input.GetMousePosition());

    // 発射検知＆ブロック上であればヒット処理
    if (m_player.isShoot)
    {
        int col, row;
        if(m_blockGrid.HitBlock(m_player.GetPos(), col, row))
            ResolveHit(col, row);
    }
}

// ゲーム画面の描画処理
void GameScene::Draw()
{
    DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), true);

    m_blockGrid.Draw();
    m_player.Draw();

    // メインコア
    DrawExtendGraph(0, COL_MAX * BOX_SIZE + ORIGIN_Y, SCREEN_W, SCREEN_H - ORIGIN_Y,
                    coreTex, TRUE);

    // フレーム
    DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H,
                    frameImg, TRUE);
}

void GameScene::ResolveHit(int col, int row, int rippleColor)
{
    // ウィルスがいたら色を返す

    // 無色ブロック& !colorの場合はreturn

    // if(virusColor) // ウィルスがいた場合
    // ウィルス退治
    // 波紋による他色ウィルス退治の場合はここでreturn
    m_blockGrid.ChangeColor(col, row, 0);
}