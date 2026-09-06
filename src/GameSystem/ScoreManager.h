#pragma once
#include "../Audio/AudioManager.h"
#include "CutInUIManager.h"

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
    bool IsIncreaseLevel(bool isClimax = false);
private:
    const int SCORE_PER_LEVEL = 50000;
    int m_score = 0;
    int m_level = 1;
    int m_scoreLevel = 1;
    int m_scoreFontHandle = -1;
    CutInUIManager m_cutInUI;
};