#pragma once
#include "IScene.h"
#include "../Audio/AudioManager.h"
#include "../Entity/Block.h"

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
    static constexpr int FIG_COLS = 5;
    static constexpr int FIG_ROWS = 4;
    Block m_figA[FIG_ROWS][FIG_COLS];
    Block m_figB[FIG_ROWS][FIG_COLS];
    int m_virusGraph[3];
    void DrawVirus(int gx, int gy, int col, int row, ColorId color) const;
    void DrawBlock(int gx, int gy, int col, int row, ColorId color) const;
    void DrawCursor(int gx, int gy, float col, float row) const;
    void DrawRipple(int gx, int gy, int col, int row, int radius, ColorId color) const;
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
};
