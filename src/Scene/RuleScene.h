#pragma once
#include "IScene.h"
#include "../Audio/AudioManager.h"
#include "../Entity/Block.h"
#include "../Graphics/TextureManager.h"

class RuleScene : public IScene
{
public:
    RuleScene(SceneManager *mgr, Input *input);
    ~RuleScene();
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw() override;

private:
    void DrawTextBlock(int x, int y, const char *const *lines, int lineCount) const;
    void DrawVirus(int x, int y, ColorId color) const;
    void DrawBlock(int x, int y, ColorId color) const;
    void DrawCursor(int x, int y) const;
    void DrawRipple(int x, int y, int radius, ColorId color) const;
    int m_titleFontHandle;
    int m_descriptionFontHandle;
    int m_commandFontHandle;
    int m_commandTextWidth;
    static constexpr const char *TITLE_TEXT = "ウィルスからシステムを守れ";
    static constexpr const char *COMMAND_TEXT = "[X] BACK";
    static constexpr const char *TEXT_A[] = {
        "ウィルスは防衛壁を越え、",
        "システムに侵入しようとしている。",
        "あなたは防衛プログラムとして、",
        "防衛壁に電撃弾を撃ち込み、ウィルスを退治しよう。",
    };
    static constexpr int TEXT_A_LINES = sizeof(TEXT_A) / sizeof(TEXT_A[0]);

    static constexpr const char *TEXT_B[] = {
        "ウィルスを退治すると、壁に抗体が生成される。",
        "抗体からは衝撃波が発生し、",
        "同じ種類のウィルスを巻き込んで連鎖する。",
    };
    static constexpr int TEXT_B_LINES = sizeof(TEXT_B) / sizeof(TEXT_B[0]);

    static constexpr const char *TEXT_C[] = {
        "反射神経と判断力で、ウィルスを一掃しよう。",
    };
    static constexpr int TEXT_C_LINES = sizeof(TEXT_C) / sizeof(TEXT_C[0]);
    static constexpr int RULE_VIRUS_SIZE = 60;
    static constexpr int RULE_BOX_SIZE = 40;
};
