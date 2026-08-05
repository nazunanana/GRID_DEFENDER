#pragma once
#include "IScene.h"

class ClearScene : public IScene
{
public:
    ClearScene(SceneManager* mgr, Input* input, int score);
    ~ClearScene();
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw() override;

private:
    void DrawCenteredString(int y, int fontHandle, const char* text);
    int m_score;
    int m_resultFontHandle;
    int m_resultScoreFontHandle;
    int m_commandFontHandle;
    int m_resultTextWidth;
    int m_resultScoreTextWidth;
    int m_commandTextWidth;
    static constexpr const char* GAMECLEAR_TEXT = "GAME CLEAR";
    static constexpr const char* COMMAND_TEXT = "PRESS RETRY";
};
