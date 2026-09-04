#pragma once

/*
設定値
*/

constexpr int SCREEN_W = 800;  // 横の解像度
constexpr int SCREEN_H = 680;  // 縦の解像度
constexpr float TIME_LIMIT = 90.0f; // タイムリミット
constexpr int TARGET_FPS = 60; // FPS
constexpr int BOX_SIZE = 50; // ブロックの大きさ
constexpr int OFFSET = 40; // ブロックの大きさ
constexpr int ORIGIN_X = 0; // BOX_SIZE; // ブロックのX座標基準値
constexpr int ORIGIN_Y = OFFSET; // ブロックのY座標基準値
constexpr int ROW_MAX = SCREEN_W / BOX_SIZE; // ブロックの横の最大個数
constexpr int COL_MAX = ROW_MAX / 2; // ブロックの縦の最大個数

/* UI */
constexpr const char* FONT_NAME = "x12y16pxMaruMonica";
constexpr int SCORE_FONT_SIZE = 24;
constexpr int TITLE_FONT_SIZE = 52;
constexpr int RULE_TITLE_FONT_SIZE = 32;
constexpr int DESCRIPTION_FONT_SIZE = 20;
constexpr int DESCRIPTION_LINE_H = 32;
constexpr int RESULT_SCORE_FONT_SIZE = 24;
constexpr int RESULT_RANK_FONT_SIZE = 42;
constexpr int COMMAND_FONT_SIZE = 20;