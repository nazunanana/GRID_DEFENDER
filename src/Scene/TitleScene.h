#pragma once
#include "IScene.h"
#include "../Audio/AudioManager.h"

class TitleScene : public IScene
{
public:
    TitleScene(SceneManager* mgr, Input* input);
    ~TitleScene();
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw() override;

private:
    int m_titleFontHandle;
    int m_commandFontHandle;
    int m_titleTextWidth;
    int m_commandTextWidth;
    static constexpr const char* TITLE_TEXT = "GRID DEFENDER";
    static constexpr const char* COMMAND_TEXT = "[X] NORMAL MODE   [C] HARD MODE   [V] RULE";
};
