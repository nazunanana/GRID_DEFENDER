#include "RuleScene.h"
#include "SceneManager.h"
#include "../Input/input.h"
#include "../Core/Config.h"
#include "../GameSystem/Common.h"
#include "DxLib.h"

/*
遊び方表示
*/

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
                           lines[i], GetColor(235, 235, 255), m_descriptionFontHandle);
    }
}

void RuleScene::DrawVirus(int x, int y, ColorId color) const
{
    int graph = TextureManager::Instance().GetVirusGraph(color);
    if (graph == -1) return;
    DrawExtendGraph(x, y, x + RULE_VIRUS_SIZE, y + RULE_VIRUS_SIZE, graph, TRUE);
}

void RuleScene::DrawBlock(int x, int y, ColorId color) const
{
    DrawBox(x, y, x + RULE_BOX_SIZE, y + RULE_BOX_SIZE, BlockColor(color), TRUE);
}

void RuleScene::DrawRipple(int gx, int gy, int radius, ColorId color) const
{
    const float size = (radius + 0.5f) * (RULE_BOX_SIZE);
    const int x = gx + RULE_BOX_SIZE/2;
    const int y = gy + RULE_BOX_SIZE/2;
 
    DrawBoxAA(x - size, y - size, x + size, y + size,
              RippleColor(color), FALSE, 2.0f);
}

void RuleScene::DrawCursor(int x, int y) const
{
    DrawLine(x - CURSOR_LINE_LENGTH, y, x + CURSOR_LINE_LENGTH, y, GetColor(255, 255, 255), CURSOR_THICKNESS);
    DrawLine(x, y - CURSOR_LINE_LENGTH, x, y + CURSOR_LINE_LENGTH, GetColor(255, 255, 255), CURSOR_THICKNESS);
    DrawCircle(x, y, CURSOR_RADIUS, GetColor(255, 255, 255), FALSE, CURSOR_THICKNESS);
}

void RuleScene::Draw()
{
    // 背景
    DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(5, 0, 40), TRUE);

    // タイトル
    DrawStringToHandle(60, 55, "ウィルスからシステムを守れ", GetColor(255, 255, 255), m_titleFontHandle);
    // 上段文
    DrawTextBlock(60, 145, TEXT_A, TEXT_A_LINES);
    // 下段文
    DrawTextBlock(260, 325, TEXT_B, TEXT_B_LINES);
    DrawTextBlock(260, 465, TEXT_C, TEXT_C_LINES);
    // コマンド
    DrawStringToHandle((SCREEN_W - m_commandTextWidth) / 2, 628,
                       COMMAND_TEXT, GetColor(255, 255, 255), m_commandFontHandle);

    // ウィルス
    DrawVirus(540, 80, ColorId::Magenta);
    DrawVirus(690, 140, ColorId::Cyan);
    DrawVirus(630, 180, ColorId::Purple);
    // 照準
    DrawCursor(640, 130);
    // ブロック
    DrawBlock(50, 360, ColorId::Cyan);
    DrawBlock(200, 440, ColorId::Purple);
    DrawBlock(110, 490, ColorId::Magenta);
    // 衝撃波
    DrawRipple(110, 490, 2, ColorId::Magenta);
}