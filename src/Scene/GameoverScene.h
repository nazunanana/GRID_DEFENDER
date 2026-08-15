#pragma once
#include "IScene.h"
#include "../Audio/AudioManager.h"
#include "../GameSystem/Common.h"

class GameoverScene : public IScene
{
public:
    GameoverScene(SceneManager *mgr, Input *input, int score, float remainingTime, Difficulty difficulty);
    ~GameoverScene();
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw() override;

private:
    void DrawCenteredString(int y, int fontHandle, const char* text);
    const char* GetRank();
    int m_score;
    const char* m_rank;
    float m_remainingTime;
    int m_resultFontHandle;
    int m_resultScoreFontHandle;
    int m_resultRankFontHandle;
    int m_commandFontHandle;
    int m_resultTextWidth;
    int m_resultScoreTextWidth;
    int m_resultTimeTextWidth;
    int m_resultRankTextWidth;
    int m_commandTextWidth;
    static constexpr const char* GAMEOVER_TEXT = "GAME OVER";
    static constexpr const char* COMMAND_TEXT = "[X] RETRY    [C] TITLE";
    Difficulty m_difficulty;
};
