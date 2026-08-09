#pragma once

class CutInUIManager
{
public:
    CutInUIManager();
    ~CutInUIManager();
    void Update(float dt);
    void Draw();
    void SetText(const char* text, bool isChangeText);
    bool IsDisplaying() { return m_displayTimer > 0.0f; }
private:
    const float DISPLAY_LEVELUP_TEXT_TIME = 1.5f;
    const float DISPLAY_TEXT_TIME = 2.0f;
    const char* m_displayText;
    float m_displayTimer = 0.0f;
    int m_displayFontHandle = -1;
    int m_displayTextWidth;
    bool m_isChangeText = true;
};