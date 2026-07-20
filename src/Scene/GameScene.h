#pragma once
#include "IScene.h"
#include "../Input/Input.h"
#include "../GameSystem/Player.h"
#include "../GameSystem/BlockGrid.h"
#include "../GameSystem/VirusManager.h"
#include "../GameSystem/ChainManager.h"
#include "../GameSystem/ScoreManager.h"

class GameScene : public IScene
{
public:
    GameScene(SceneManager* mgr, Input* input);
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw() override;
    bool isStart = false;

private:
    void ResolveHit(int col, int row, std::optional<ColorId> rippleColor = std::nullopt, int chainLevel = 0);
    int coreTex = -1;
    int fieldTex = -1;
    int hpTex = -1;
    int frameImg = -1;
    int hpNum = 3;
    int hpUiOffset = 5;
    Input m_input;
    Player m_player;
    BlockGrid m_blockGrid;
    VirusManager m_virusMgr;
    ChainManager m_chainMgr;
    ScoreManager m_scoreMgr;
};
