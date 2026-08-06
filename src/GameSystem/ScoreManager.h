#pragma once
#include "../Audio/AudioManager.h"

class ScoreManager
{
public:
    ScoreManager();
    ~ScoreManager();
    void IncreaseScore(int amount);
    int GetScore();
    int GetLevel();
    void Update(float dt);
    void Draw(float time);
private:
    const int SCORE_PER_LEVEL = 50000;
    const float DISPLAY_LEVELUP_TIME = 1.5f;
    int m_score = 0;
    int m_level = 1;
    float m_levelUpTimer = 0.0f;
    int m_scoreFontHandle = -1;
    int m_displayFontHandle = -1;
    int m_displayTextWidth;
    bool IsIncreaseLevel();
};