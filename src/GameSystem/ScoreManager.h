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
    void Draw(float time);
    void IsIncreaseLevel(bool isClimax = false);
private:
    static constexpr int LEVELUP_SCORE[5] = { 50000, 100000, 150000, 200000, 250000};
    int m_score = 0;
    int m_level = 1;
    int m_levelupScoreIndex = 0;
    int m_scoreFontHandle = -1;
    bool IsLevelUp();
};