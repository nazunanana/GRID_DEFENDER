#include "RuleScene.h"
#include "SceneManager.h"
#include "../Input/input.h"
#include "../Core/Config.h"
#include "DxLib.h"

/*
遊び方表示
*/

namespace
{
    // ---------- レイアウト ----------
    // パネル
    constexpr int PANEL_X1 = 30;
    constexpr int PANEL_Y1 = 25;
    constexpr int PANEL_X2 = SCREEN_W - 30;
    constexpr int PANEL_Y2 = 540;

    // 上段（テキスト左・図右）
    constexpr int FIG_A_X = 565;
    constexpr int FIG_A_Y = 110;

    // 下段（図左・テキスト右）
    constexpr int FIG_B_X = 60;
    constexpr int FIG_B_Y = 320;

    // コマンド
    constexpr int COMMAND_Y = 560;

    // 説明図のマス
    constexpr int MINI_CELL = 32;

    // ---------- 色 ----------
    const unsigned int COL_BG        = GetColor(5, 0, 40);
    const unsigned int COL_PANEL     = GetColor(38, 30, 78);
    const unsigned int COL_TEXT      = GetColor(235, 235, 255);
    const unsigned int COL_GRID_BG   = GetColor(12, 6, 46);
    const unsigned int COL_GRID_LINE = GetColor(70, 60, 130);
    const unsigned int COL_VIRUS_P   = GetColor(168, 85, 247);  // 紫ウィルス
    const unsigned int COL_VIRUS_C   = GetColor(52, 211, 235);  // 水色ウィルス
    const unsigned int COL_WAVE      = GetColor(190, 120, 255);
    const unsigned int COL_CURSOR    = GetColor(255, 255, 255);

}

RuleScene::RuleScene(SceneManager* manager, Input* input)
    : IScene(manager, input)
{
    m_titleFontHandle = CreateFontToHandle(
        FONT_NAME, 
        RULE_TITLE_FONT_SIZE, 
        -1, 
        DX_FONTTYPE_ANTIALIASING_EDGE, 
        -1, 
        3
    );

    m_descriptionFontHandle = CreateFontToHandle(
        FONT_NAME, 
        DESCRIPTION_FONT_SIZE, 
        -1, 
        DX_FONTTYPE_ANTIALIASING_EDGE,
        -1,
        3
    );

    m_commandFontHandle = CreateFontToHandle(
        FONT_NAME, 
        COMMAND_FONT_SIZE, 
        -1, 
        DX_FONTTYPE_ANTIALIASING_EDGE, 
        -1, 
        3
    );

    m_commandTextWidth = GetDrawStringWidthToHandle(COMMAND_TEXT, -1, m_commandFontHandle);
}

RuleScene::~RuleScene()
{
    DeleteFontToHandle(m_titleFontHandle);
    DeleteFontToHandle(m_descriptionFontHandle);
    DeleteFontToHandle(m_commandFontHandle);
}

void RuleScene::Enter()
{
    AudioManager::Instance().PlayBgm("menuBgm");
}

void RuleScene::Exit()
{

}

void RuleScene::Update(float dt)
{
    // タイトルへ戻る
    if (m_input->Pressed(Action::Decide))
    {
        m_sceneMgr->RequestChange(SceneType::Title);
        return;
    }
}

// テキストブロック
void RuleScene::DrawTextBlock(int x, int y, const char* const* lines, int lineCount) const
{
    for (int i = 0; i < lineCount; ++i)
    {
        DrawStringToHandle(x, y + i * DESCRIPTION_LINE_H,
                           lines[i], COL_TEXT, m_descriptionFontHandle);
    }
}

// void RuleScene::DrawVirus(int gx, int gy, int col, int row, ColorId color) const
// {
//     const int graph = m_virusGraph[static_cast<int>(color)];
//     if (graph == -1) return;
 
//     const int x = gx + col * BOX_SIZE;
//     const int y = gy + row * BOX_SIZE;
//     DrawExtendGraph(x, y, x + BOX_SIZE, y + BOX_SIZE, graph, TRUE);
// }

// void RuleScene::DrawBlock(int gx, int gy, int col, int row, ColorId color) const
// {
//     const int x = gx + col * BOX_SIZE;
//     const int y = gy + row * BOX_SIZE;
 
//     DrawBox(x, y, x + BOX_SIZE, y + BOX_SIZE, ToDrawColor(color), TRUE);
 
//     if (color != ColorId::None)
//     {
//         SetDrawBlendMode(DX_BLENDMODE_ADD, ANTIBODY_BRIGHTNESS);
//         DrawBox(x, y, x + BOX_SIZE, y + BOX_SIZE, GetColor(255, 255, 255), TRUE);
//         SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//     }
// }

// void RuleScene::DrawRipple(int gx, int gy, int col, int row, int radius, ColorId color) const
// {
//     const float cx   = static_cast<float>(gx + col * BOX_SIZE + BOX_SIZE / 2);
//     const float cy   = static_cast<float>(gy + row * BOX_SIZE + BOX_SIZE / 2);
//     const float size = (radius + 0.5f) * BOX_SIZE;
 
//     DrawBoxAA(cx - size, cy - size, cx + size, cy + size,
//               ToDrawColor(color), FALSE, RIPPLE_THICKNESS);
// }

// void RuleScene::DrawCursor(int gx, int gy, float col, float row) const
// {
//     const int x = gx + static_cast<int>(col * BOX_SIZE);
//     const int y = gy + static_cast<int>(row * BOX_SIZE);
 
//     DrawLine(x - CURSOR_LINE_LENGTH, y, x + CURSOR_LINE_LENGTH, y, COL_CURSOR, CURSOR_THICKNESS);
//     DrawLine(x, y - CURSOR_LINE_LENGTH, x, y + CURSOR_LINE_LENGTH, COL_CURSOR, CURSOR_THICKNESS);
//     DrawCircle(x, y, CURSOR_RADIUS, COL_CURSOR, FALSE, CURSOR_THICKNESS);
// }

void RuleScene::Draw()
{
    DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(5, 0, 40), TRUE);

    //DrawBox(PANEL_X1, PANEL_Y1, PANEL_X2, PANEL_Y2, COL_PANEL, TRUE);

    DrawStringToHandle(60, 55, "ウィルスからシステムを守れ", GetColor(255, 255, 255), m_titleFontHandle);

    DrawTextBlock(60, 145, TEXT_A, TEXT_A_LINES);
    // DrawShootFigure();

    // DrawChainFigure();
    DrawTextBlock(260, 325, TEXT_B, TEXT_B_LINES);
    DrawTextBlock(260, 465, TEXT_C, TEXT_C_LINES);

    DrawStringToHandle((SCREEN_W - m_commandTextWidth) / 2, COMMAND_Y,
                       COMMAND_TEXT, GetColor(255, 255, 255), m_commandFontHandle);
}