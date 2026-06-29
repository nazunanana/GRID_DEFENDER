#pragma once

class Time
{
public:
    void Reset();
    void Update();
    float DeltaTime() const { return m_delta; }

private:
    int m_prev = 0;
    float m_delta = 0.0f;
};