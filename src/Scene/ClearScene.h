#pragma once
#include "IScene.h"

class ClearScene : public IScene
{
public:
    ClearScene(SceneManager* mgr, Input* input);
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw() override;

};
