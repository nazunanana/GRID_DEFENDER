#pragma once
#include "IScene.h"
#include "../Input/Input.h"
#include "../GameSystem/Player.h"
#include "../GameSystem/BlockGrid.h"
#include "../GameSystem/VirusManager.h"
#include "../GameSystem/ChainManager.h"
#include "../GameSystem/ScoreManager.h"
#include "../GameSystem/CutInUIManager.h"
#include "../Audio/AudioManager.h"
#include <Vector>

class GameScene : public IScene
{
public:
    GameScene(SceneManager* mgr, Input* input, Difficulty difficulty);
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw() override;

private:
    enum class GamePhase { Start, Playing, Clear, GameOver }; // ゲームの進行状態
    void ResolveTapHit(int x, int y); // 直接タップでのヒット処理
    void ResolveRippleHit(int col, int row, ColorId virusColor, ColorId rippleColor, int chainLevel); // 衝撃波がVirusを見つけた時のヒット処理
    const float DAMAGE_TIME = 0.1f;
    int coreTex = -1;
    int fieldTex = -1;
    int hpTex = -1;
    int frameImg = -1;
    int hpNum = 3;
    int hpUiOffset = 5;
    float m_elapsedTime = 0.0f;
    float m_damageTimer = 0.0f;
    float m_virusClearTimer = 0.0f;
    bool m_isClimax = false;
    struct RippleHit { int col; int row; ColorId virusColor; ColorId rippleColor; int chainLevel; };
    std::vector<RippleHit> m_rippleHits;// ウイルスに衝突した衝撃波を記録
    GamePhase m_phase = GamePhase::Start;
    Difficulty m_difficulty;
    Player m_player;
    BlockGrid m_blockGrid;
    VirusManager m_virusMgr;
    ChainManager m_chainMgr;
    ScoreManager m_scoreMgr;
    CutInUIManager m_cutInUI;
};
