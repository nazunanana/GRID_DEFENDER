#pragma once

class ScoreManager
{
public:
    ScoreManager();
    ~ScoreManager();
    void IncreaseScore(int amount);
    int GetScore();
    void Draw(float time);
private:
    int m_score = 0;
    int m_fontHandle = -1;
};