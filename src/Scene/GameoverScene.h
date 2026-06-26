#pragma once
#include "IScene.h"

class GameoverScene : public IScene
{
public:
    GameoverScene(SceneManager* mgr, Input* input);
    void Enter() override;
    void Exit() override;
    void Update() override;
    void Draw() override;

};
