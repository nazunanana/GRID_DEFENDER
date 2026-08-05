#pragma once
#include "IScene.h"

class GameoverScene : public IScene
{
public:
    GameoverScene(SceneManager *mgr, Input *input, int score, float remainingTime);
    ~GameoverScene();
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw() override;

private:
    void DrawCenteredString(int y, int fontHandle, const char* text);
    int m_score;
    float m_remainingTime;
    int m_resultFontHandle;
    int m_resultScoreFontHandle;
    int m_commandFontHandle;
    int m_resultTextWidth;
    int m_resultScoreTextWidth;
    int m_resultTimeTextWidth;
    int m_commandTextWidth;
    static constexpr const char* GAMEOVER_TEXT = "GAME OVER";
    static constexpr const char* COMMAND_TEXT = "PRESS RETRY";
};
