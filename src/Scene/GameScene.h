#pragma once
#include "IScene.h"
#include "Player.h"
#include "BlockGrid.h"
#include "VirusManager.h"
#include "ChainManager.h"
#include "ScoreManager.h"

class GameScene : public IScene
{
public:
    // GameScene(SceneManager* mgr, Input* input);
    // void Enter() override;
    // void Exit() override;
    void Update() override;
    void Draw() override;
    static constexpr int COL_MAX = 8;
    static constexpr int ROW_MAX = 16;
    static constexpr int BOX_SIZE = 40;
    bool isStart;

private:
    void ResolveHit(int col, int row, int color);
    Player m_player;
    BlockGrid m_blockGrid;
    VirusManager m_virusMgr;
    ChainManager m_chainMgr;
    //ScoreManager m_scoreMgr;
};
