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
    m_cutInUI.Update(dt);

    if (m_damageTimer > 0.0f)
        m_damageTimer -= dt;                // ダメージ演出時間
    int damage = m_virusMgr.PopLeakCount(); // 今フレームでコアに到達したウィルス数
    if (damage != 0)                        // ダメージを受ける
    {
        m_hpNum -= damage;
        m_damageTimer = DAMAGE_TIME;
        AudioManager::Instance().PlaySe("damageSe");
    }

    // 発射検知＆ブロック上であればヒット処理
    if (m_player.isShoot)
        ResolveTapHit(m_player.GetPos().x, m_player.GetPos().y);

    // 衝撃波の処理（成長・消滅のみ）
    RippleManager::ChainEventType chainEvent;
    std::vector<int> chainCount = {};
    bool isSameColor;
    m_rippleMgr.Update(m_blockGrid, m_virusMgr, chainEvent, chainCount, isSameColor);

    switch (chainEvent)
    {
    case RippleManager::ChainEventType::CollisionVirus:
        ResolveRippleVirus(chainCount, isSameColor);
        break;
    case RippleManager::ChainEventType::CollisionBlock:
        ResolveRippleBlock();
        break;
    }

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
    ColorId virusColor = m_virusMgr.GetVirusColorAtPoint(x, y);

    int blockCol = -1, blockRow = -1;
    // スクリーン座標からブロック座標に変換
    m_blockGrid.ScreenToIndex(x, y, blockCol, blockRow);

    if (virusColor != ColorId::None) // タップでウイルスが退治された場合
    {
        ResolveVirusHit(blockCol, blockRow, virusColor, true);
        return;
    }

    // ブロックの色を取得
    ColorId blockColor = m_blockGrid.GetBlockColorAt(blockCol, blockRow);

    if (blockColor != ColorId::None) // 抗体をタップした場合
    {
        ResolveBlockHit(blockCol, blockRow, blockColor);
        return;
    }

    // 何もない場合は撃つSEのみ
    AudioManager::Instance().PlaySe("shootSe");
}

// ウイルス退治後の処理
void GameScene::ResolveVirusHit(int blockCol, int blockRow, ColorId virusColor, bool isCreateBlock)
{
    // SEを鳴らす
    AudioManager::Instance().PlaySe("hitSe");
    // スコア換算
    m_scoreMgr.IncreaseScore(2000);
    // 直接撃った場合は抗体生成
    if (isCreateBlock)
    {
        // ブロックの色変更
        m_blockGrid.ChangeColor(blockCol, blockRow, virusColor, 1);
    }
}

// 抗体ヒット処理
void GameScene::ResolveBlockHit(int blockCol, int blockRow, ColorId blockColor)
{
    // 衝撃波生成
    m_rippleMgr.StartChain(blockCol, blockRow, blockColor);
    // 撃った抗体は無色に戻す
    m_blockGrid.ChangeColor(blockCol, blockRow, ColorId::None,1);
}

// 衝撃波とウイルスのヒット処理
void GameScene::ResolveRippleVirus(std::vector<int> chainCount, bool isSameColor)
{
    int maxCount = 1;
    // スコア換算
    for(const auto &c : chainCount)
    {
        if(isSameColor) m_scoreMgr.IncreaseScore(3000 * c);
        else m_scoreMgr.IncreaseScore(1000 * c);
        if(c > maxCount) maxCount = c;
    }

    // SEを鳴らす
    if(maxCount >= 5)
        AudioManager::Instance().PlaySe("rippleSe3");
    else if(maxCount >= 3)
        AudioManager::Instance().PlaySe("rippleSe2");
    else if (maxCount >= 1)
        AudioManager::Instance().PlaySe("rippleSe");

    // 盤面を光らせる
    // if(maxCount == 5)
    //     m_blockGrid.AllBright(20);
    // else if(maxCount == 3)
    //     m_blockGrid.AllBright(10);
}

// 衝撃波とブロックのヒット処理
void GameScene::ResolveRippleBlock()
{
    //AudioManager::Instance().PlaySe("hitBlockSe");
}