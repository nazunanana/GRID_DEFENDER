#pragma once
#include "IScene.h"

class GameScene : public IScene
{
public:
    // GameScene(SceneManager* mgr, Input* input);
    // void Enter() override;
    // void Exit() override;
    void Update() override;
    void Draw() override;

};
