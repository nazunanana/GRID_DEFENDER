#pragma once
#include "IScene.h"

class TitleScene : public IScene
{
public:
    TitleScene(SceneManager* mgr, Input* input);
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw() override;
};
