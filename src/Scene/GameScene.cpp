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
    fieldTex = LoadGraph("img/field_tex2.png");
    hpTex = LoadGraph("img/hp_tex.png");
    // frameImg = LoadGraph("img/frame.png");
    // 仮
    isStart = true;
}

// ゲーム画面を出たときの処理
void GameScene::Exit()
{
    DeleteGraph(coreTex);
    DeleteGraph(fieldTex);
    DeleteGraph(hpTex);
}

// ゲーム画面の更新処理
void GameScene::Update(float dt)
{
    // 各クラスのUpdateを呼び出す
    m_input.Update();
    m_player.Update(m_input.Pressed(Action::Shoot), m_input.GetMousePosition());
    m_virusMgr.Update(dt);
    hpNum -= m_virusMgr.PopLeakCount(); // コアに到達されたらHPを減らす

    // 発射検知＆ブロック上であればヒット処理
    if (m_player.isShoot)
    {
        int col, row;
        if (m_blockGrid.HitBlock(m_player.GetPos(), col, row))
            ResolveHit(col, row);
    }

    // 波紋の処理
    m_chainMgr.Update();
    // 波紋による衝突処理が残っていたらResolveHitを呼ぶ
    while (m_chainMgr.HasExpandedRipple())
    {
        ChainManager::ExpandedRipple r = m_chainMgr.PopExpandedRipple();
        ResolveHit(r.col, r.row, r.color, r.chainLevel);
    }

    // 終了判定
    m_elapsedTime += dt;
    float remainingTime = TIME_LIMIT - m_elapsedTime;
    if (remainingTime <= 0.0f)
    {
        m_sceneMgr->RequestChange(SceneType::Clear, m_scoreMgr.GetScore());
        return;
    }
    if (hpNum <= 0)
    {
        m_sceneMgr->RequestChange(SceneType::GameOver, m_scoreMgr.GetScore(), remainingTime);
        return;
    }
}

// ゲーム画面の描画処理
void GameScene::Draw()
{
    DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), true);

    // HP表示
    for (int i = 1; i <= hpNum; i++)
    {
        DrawExtendGraph(SCREEN_W - ORIGIN_X - BOX_SIZE * i + hpUiOffset, hpUiOffset, SCREEN_W - ORIGIN_X - BOX_SIZE * (i - 1) - hpUiOffset, ORIGIN_Y - hpUiOffset,
                        hpTex, TRUE);
    }
    m_scoreMgr.Draw();
    m_blockGrid.Draw();

    // 背景
    DrawExtendGraph(ORIGIN_X, ORIGIN_Y, SCREEN_W - ORIGIN_X, ORIGIN_Y + COL_MAX * BOX_SIZE,
                    fieldTex, TRUE);

    m_virusMgr.Draw();
    m_chainMgr.Draw();
    m_player.Draw();

    // メインコア
    DrawExtendGraph(ORIGIN_X, COL_MAX * BOX_SIZE + ORIGIN_Y, SCREEN_W - ORIGIN_X, SCREEN_H - ORIGIN_Y,
                    coreTex, TRUE);

}

// ブロックにヒットしたときの処理
void GameScene::ResolveHit(int col, int row, std::optional<ColorId> rippleColor, int chainLevel)
{
    // ウィルスがいたら色を返す
    std::optional<ColorId> virusColor = m_virusMgr.GetVirusColor(col, row);

    // ウィルスがなく、かつ無色ブロックの場合はreturn
    if ((rippleColor && !virusColor) || (!virusColor && (m_blockGrid.GetBlockColorAt(col, row) == ColorId::None)))
        return;
    else if (virusColor) // ウィルスがいた場合は退治
    {
        m_virusMgr.KillVirus(col, row);

        if (!rippleColor)
            m_scoreMgr.IncreaseScore(1000); // 直接タップで退治
        else if (virusColor == rippleColor)
            m_scoreMgr.IncreaseScore(2000 * chainLevel); // 同色の波紋で退治（連鎖継続）
        else
        {
            m_scoreMgr.IncreaseScore(1000 * chainLevel); // 別色の波紋で退治（ここで連鎖は途切れる）
            return;
        }
    }

    // ブロックの色変更
    ColorId colorToSet = virusColor ? *virusColor : m_blockGrid.GetBlockColorAt(col, row).value();
    m_blockGrid.ChangeColor(col, row, colorToSet);

    // 波紋生成（直接タップ由来なら1連鎖目、既存の波紋由来ならその次の連鎖として生成）
    int nextChainLevel = rippleColor ? chainLevel + 1 : 1;
    m_chainMgr.GenerateRipple(col, row, colorToSet, nextChainLevel);
}