#pragma once
#include "IScene.h"
#include "../Core/Config.h"
#include "../Input/Input.h"
#include "../GameSystem/Common.h"
#include "../GameSystem/Player.h"
#include "../GameSystem/BlockGrid.h"
#include "../GameSystem/VirusManager.h"
#include "../GameSystem/RippleManager.h"
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
    enum class GamePhase // ゲームの進行状態
    {
        Start,
        Playing,
        Clear,
        GameOver
    };
    struct RippleHit // 衝撃波データ
    {
        int col;
        int row;
        ColorId color;
        int rippleLevel;
    };
    void ResolveTapHit(int x, int y); // 直接タップでのヒット処理
    void ResolveVirusHit(int blockCol, int blockRow, ColorId virusColor, bool isCreateBlock, int chainLevel); // ウイルス退治後の処理
    void ResolveBlockHit(int blockCol, int blockRow, ColorId blockColor); // 抗体タップ時の処理
    void ResolveRippleVirus(std::vector<int> chainCount); // 衝撃波がVirusに当たった時のヒット処理
    void ResolveRippleBlock(); // 衝撃波が抗体に当たった時のヒット処理
    const float DAMAGE_TIME = 0.1f;
    int m_coreTex = -1;
    int m_fieldTex = -1;
    int m_hpTex = -1;
    int m_frameImg = -1;
    int m_hpNum = 3;
    int m_hpUiOffset = 5;
    float m_elapsedTime = 0.0f;
    float m_damageTimer = 0.0f;
    float m_virusClearTimer = 0.0f;
    bool m_isClimax = false;
    std::vector<RippleHit> m_rippleHits; // ブロックに衝突した衝撃波を記録
    GamePhase m_phase = GamePhase::Start;
    Difficulty m_difficulty;
    Player m_player;
    BlockGrid m_blockGrid;
    VirusManager m_virusMgr;
    RippleManager m_rippleMgr;
    ScoreManager m_scoreMgr;
    CutInUIManager m_cutInUI;
};
