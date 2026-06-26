#pragma once
#include "IScene.h"
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
    void Update() override;
    void Draw() override;
    bool isStart = false;

private:
    void ResolveHit(int col, int row, int color);
    Player m_player;
    BlockGrid m_blockGrid;
    VirusManager m_virusMgr;
    ChainManager m_chainMgr;
    //ScoreManager m_scoreMgr;
};
