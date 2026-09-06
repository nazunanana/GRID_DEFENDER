#include "GameScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Core/Config.h"
#include "../Graphics/TextureManager.h"
#include "DxLib.h"

using namespace DxLib;

/*
ゲームシーン
*/

GameScene::GameScene(SceneManager *manager, Input *input, Difficulty difficulty)
    : IScene(manager, input), m_difficulty(difficulty) {}

// ゲーム画面に入ったときの処理
void GameScene::Enter()
{
     m_cutInUI.SetText("GAME START", false);
    AudioManager::Instance().PlayBgm("gameBgm");
}

// ゲーム画面を出たときの処理
void GameScene::Exit()
{
    AudioManager::Instance().StopBgm();
}

// ゲーム画面の更新処理
void GameScene::Update(float dt)
{
    if (m_phase != GamePhase::Playing) // カットイン表示中はゲームプレイ更新を止める
    {
        m_cutInUI.Update(dt);
        if (m_cutInUI.IsDisplaying() == false) // カットイン表示が終わったら
        {
            switch (m_phase)
            {
            case GamePhase::Start:
                m_phase = GamePhase::Playing; // ゲーム再開
                break;
            case GamePhase::Clear:
                m_sceneMgr->RequestChange(SceneType::Clear, m_difficulty, m_scoreMgr.GetScore());
                break;
            case GamePhase::GameOver:
                m_sceneMgr->RequestChange(SceneType::GameOver, m_difficulty, m_scoreMgr.GetScore(), TIME_LIMIT - m_elapsedTime);
                break;
            default:
                break;
            }
        }
        return;
    }
    // 各クラスのUpdateを呼び出す
    m_player.Update(m_input->Pressed(Action::Shoot), m_input->GetMousePosition());
    m_blockGrid.Update();
    m_virusMgr.Update(dt, m_scoreMgr.GetLevel(), m_difficulty);
    //m_scoreMgr.Update(dt);
    m_cutInUI.Update(dt);

    if (m_damageTimer > 0.0f) m_damageTimer -= dt;
    int damage = m_virusMgr.PopLeakCount(); // コアに到達したウィルス数
    if(damage != 0) // ダメージを受ける
    {
        m_hpNum -= damage;
        m_damageTimer = DAMAGE_TIME;
        AudioManager::Instance().PlaySe("damageSe");
    }

    // 発射検知＆ブロック上であればヒット処理
    if (m_player.isShoot)
        ResolveTapHit(m_player.GetPos().x, m_player.GetPos().y);

    // 衝撃波の処理（成長・消滅のみ）
    m_rippleMgr.Update();

    m_rippleHits.clear();
    for (auto &r : m_rippleMgr.GetRipples())
    {
        if (!r.IsActive())
            continue;

        int col, row;
        std::optional<ColorId> virusColor = m_virusMgr.CollisionRipple(r.GetScreenX(), r.GetScreenY(), r.GetSize(), col, row);
        if (virusColor) // 衝撃波とウイルスが衝突したらメモする
            m_rippleHits.push_back({col, row, *virusColor, r.GetRippleColor(), r.GetRippleLevel()});
    }
    for (const RippleHit &hit : m_rippleHits) // ウイルスとの衝突処理
        ResolveRippleHit(hit.col, hit.row, hit.virusColor, hit.rippleColor, hit.rippleLevel);

    // 終了判定
    m_elapsedTime += dt;
    float remainingTime = TIME_LIMIT - m_elapsedTime;
    if (remainingTime <= 15.0f && !m_isClimax)
    {
        m_isClimax = true;
        m_scoreMgr.IsIncreaseLevel(m_isClimax);
        m_cutInUI.SetText("CLIMAX", false);
    }
    else if (remainingTime <= 0.0f)
    {
        m_phase = GamePhase::Clear;
        m_cutInUI.SetText("SYSTEM SECURED", false);
        AudioManager::Instance().StopBgm();
        AudioManager::Instance().PlaySe("clearSe");
        return;
    }
    if (m_hpNum <= 0)
    {
        m_phase = GamePhase::GameOver;
        m_cutInUI.SetText("SYSTEM ERROR", false);
        AudioManager::Instance().StopBgm();
        AudioManager::Instance().PlaySe("errorSe");
        return;
    }
}

// ゲーム画面の描画処理
void GameScene::Draw()
{
    // 背景
    // DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), true);

    // HP表示
    for (int i = 1; i <= m_hpNum; i++)
    {
        DrawExtendGraph(SCREEN_W - ORIGIN_X - ORIGIN_Y * i + m_hpUiOffset, m_hpUiOffset + SCREEN_H - ORIGIN_Y, SCREEN_W - ORIGIN_X - ORIGIN_Y * (i - 1) - m_hpUiOffset, SCREEN_H - m_hpUiOffset,
                        TextureManager::Instance().GetHpGraph(), TRUE);
    }

    // 抗体ブロック
    m_blockGrid.Draw();

    // グリッド線
    DrawExtendGraph(ORIGIN_X, ORIGIN_Y, SCREEN_W - ORIGIN_X, ORIGIN_Y + COL_MAX * BOX_SIZE,
                    TextureManager::Instance().GetFieldGraph(), TRUE);

    m_virusMgr.Draw();
    m_rippleMgr.Draw();
    m_player.Draw();
    m_scoreMgr.Draw(m_elapsedTime);
    m_cutInUI.Draw();

    // メインコア
    DrawExtendGraph(ORIGIN_X, COL_MAX * BOX_SIZE + ORIGIN_Y, SCREEN_W - ORIGIN_X, SCREEN_H - ORIGIN_Y,
                    TextureManager::Instance().GetCoreGraph(), TRUE);
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
    std::optional<ColorId> virusColor = m_virusMgr.GetVirusColorAtPoint(x, y);

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

    // 衝撃波生成
    m_rippleMgr.GenerateRipple(blockCol, blockRow, colorToSet, 1);
}

// 衝撃波でのヒット処理
void GameScene::ResolveRippleHit(int col, int row, ColorId virusColor, ColorId rippleColor, int rippleLevel)
{
    if (virusColor == rippleColor)
        m_scoreMgr.IncreaseScore(3000 * rippleLevel); // 同色の衝撃波で退治（連鎖継続）
    else
    {
        m_scoreMgr.IncreaseScore(1000 * rippleLevel); // 別色の衝撃波で退治（ここで連鎖は途切れる）
        AudioManager::Instance().PlaySe("hitSe");
        return;
    }

    // SEを鳴らす
    if (rippleLevel == 1)
        AudioManager::Instance().PlaySe("rippleSe");
    else
        AudioManager::Instance().PlaySe("rippleSe2");

    // ブロックの色変更
    m_blockGrid.ChangeColor(col, row, virusColor);

    // 衝撃波生成
    m_rippleMgr.GenerateRipple(col, row, virusColor, rippleLevel + 1);
}