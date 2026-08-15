#pragma once
#include "IScene.h"
#include "../Audio/AudioManager.h"
#include "../GameSystem/Common.h"

class ClearScene : public IScene
{
public:
    ClearScene(SceneManager* mgr, Input* input, int score, Difficulty difficulty);
    ~ClearScene();
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw() override;

private:
    const char* GetRank();
    void DrawCenteredString(int y, int fontHandle, const char* text);
    int m_score;
    const char* m_rank;
    int m_resultFontHandle;
    int m_resultScoreFontHandle;
    int m_resultRankFontHandle;
    int m_commandFontHandle;
    int m_resultTextWidth;
    int m_resultScoreTextWidth;
    int m_resultRankTextWidth;
    int m_commandTextWidth;
    static constexpr const char* GAMECLEAR_TEXT = "GAME CLEAR";
    static constexpr const char* COMMAND_TEXT = "[X] RETRY    [C] TITLE";
    Difficulty m_difficulty;
};
