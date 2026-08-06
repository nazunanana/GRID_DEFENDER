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
    fieldTex = LoadGraph("img/field_tex3.png");
    hpTex = LoadGraph("img/hp_tex.png");
    // frameImg = LoadGraph("img/frame.png");
    // 仮
    isStart = true;

    AudioManager::Instance().PlayBgm("gameBgm");
}

// ゲーム画面を出たときの処理
void GameScene::Exit()
{
    AudioManager::Instance().StopBgm();
    DeleteGraph(coreTex);
    DeleteGraph(fieldTex);
    DeleteGraph(hpTex);
}

// ゲーム画面の更新処理
void GameScene::Update(float dt)
{
    // 各クラスのUpdateを呼び出す
    m_player.Update(m_input->Pressed(Action::Shoot), m_input->GetMousePosition());
    m_blockGrid.Update();
    m_virusMgr.Update(dt, m_scoreMgr.GetLevel());
    m_scoreMgr.Update(dt);

    if (m_damageTimer > 0.0f) m_damageTimer -= dt;
    int damage = m_virusMgr.PopLeakCount(); // コアに到達したウィルス数
    if(damage != 0) // ダメージを受ける
    {
        hpNum -= damage;
        m_damageTimer = DAMAGE_TIME;
        AudioManager::Instance().PlaySe("damageSe");
    }

    // 発射検知＆ブロック上であればヒット処理
    if (m_player.isShoot)
        ResolveTapHit(m_player.GetPos().x, m_player.GetPos().y);

    // 波紋の処理（成長・消滅のみ）
    m_chainMgr.Update();
    for (auto &r : m_chainMgr.GetRipples())
    {
        if (!r.IsActive())
            continue;

        int col, row;
        std::optional<ColorId> virusColor = m_virusMgr.CollisionRipple(r.GetScreenX(), r.GetScreenY(), r.GetSize(), col, row);
        if (virusColor)
            ResolveRippleHit(col, row, *virusColor, r.GetRippleColor(), r.GetChainLevel());
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
        DrawExtendGraph(SCREEN_W - ORIGIN_X - ORIGIN_Y * i + hpUiOffset, hpUiOffset + SCREEN_H - ORIGIN_Y, SCREEN_W - ORIGIN_X - ORIGIN_Y * (i - 1) - hpUiOffset, SCREEN_H - hpUiOffset,
                        hpTex, TRUE);
    }
    m_blockGrid.Draw();

    // 背景
    DrawExtendGraph(ORIGIN_X, ORIGIN_Y, SCREEN_W - ORIGIN_X, ORIGIN_Y + COL_MAX * BOX_SIZE,
                    fieldTex, TRUE);

    m_virusMgr.Draw();
    m_chainMgr.Draw();
    m_player.Draw();
    m_scoreMgr.Draw(m_elapsedTime);

    // メインコア
    DrawExtendGraph(ORIGIN_X, COL_MAX * BOX_SIZE + ORIGIN_Y, SCREEN_W - ORIGIN_X, SCREEN_H - ORIGIN_Y,
                    coreTex, TRUE);
    if (m_damageTimer > 0.0f)
    {
        SetDrawBlendMode(DX_BLENDMODE_MULA, 255);
        DrawBox(ORIGIN_X, COL_MAX * BOX_SIZE + ORIGIN_Y, SCREEN_W - ORIGIN_X, SCREEN_H - ORIGIN_Y,
                    GetColor(255, 100, 100), TRUE);
        // 乗算やめる
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

// 直接タップでのヒット処理
void GameScene::ResolveTapHit(int x, int y)
{
    // ウィルスがいたら色を返し、退治
    std::optional<ColorId> virusColor = m_virusMgr.GetVirusColorAtPoint(y, x);

    int blockCol = -1, blockRow = -1;
    // スクリーン座標からブロック座標に変換
    m_blockGrid.ScreenToIndex(x, y, blockCol, blockRow);
    // ブロックの色を取得
    std::optional<ColorId> blockColor = m_blockGrid.GetBlockColorAt(blockCol, blockRow);

    // グリッド範囲外なら効果音だけ鳴らして終了
    if (!blockColor)
    {
        AudioManager::Instance().PlaySe("shootSe");
        return;
    }

    // SEを鳴らす
    if (!virusColor)
        AudioManager::Instance().PlaySe("shootSe");
    else
        AudioManager::Instance().PlaySe("hitSe");

    // ウィルスが存在しない&無色ブロックであればreturn
    if (!virusColor && *blockColor == ColorId::None)
        return;
    // ウィルスが存在したらスコア+1000
    if (virusColor)
        m_scoreMgr.IncreaseScore(1000);

    // ブロックの色変更
    ColorId colorToSet = virusColor ? *virusColor : m_blockGrid.GetBlockColorAt(blockCol, blockRow).value();
    m_blockGrid.ChangeColor(blockCol, blockRow, colorToSet);

    // 波紋生成
    m_chainMgr.GenerateRipple(blockCol, blockRow, colorToSet, 1);
}

// 波紋でのヒット処理
void GameScene::ResolveRippleHit(int col, int row, ColorId virusColor, ColorId rippleColor, int chainLevel)
{
    if (virusColor == rippleColor)
        m_scoreMgr.IncreaseScore(3000 * chainLevel); // 同色の波紋で退治（連鎖継続）
    else
    {
        m_scoreMgr.IncreaseScore(1000 * chainLevel); // 別色の波紋で退治（ここで連鎖は途切れる）
        AudioManager::Instance().PlaySe("hitSe");
        return;
    }

    // SEを鳴らす
    if (chainLevel == 1)
        AudioManager::Instance().PlaySe("chainSe");
    else
        AudioManager::Instance().PlaySe("chainSe2");

    // ブロックの色変更
    m_blockGrid.ChangeColor(col, row, virusColor);

    // 波紋生成
    m_chainMgr.GenerateRipple(col, row, virusColor, chainLevel + 1);
}