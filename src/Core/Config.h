#pragma once

/*
設定値
*/

constexpr int SCREEN_W = 800;  // 横の解像度
constexpr int SCREEN_H = 680;  // 縦の解像度
constexpr float TIME_LIMIT = 60.0f; // タイムリミット
constexpr int TARGET_FPS = 60; // FPS
constexpr int BOX_SIZE = 40; // ブロックの大きさ
constexpr int ORIGIN_X = 0; // BOX_SIZE; // ブロックのX座標基準値
constexpr int ORIGIN_Y = BOX_SIZE; // ブロックのY座標基準値
constexpr int COL_MAX = 10; // ブロックの縦の最大個数
constexpr int ROW_MAX = SCREEN_W / BOX_SIZE; // ブロックの横の最大個数

/* UI */
constexpr const char* FONT_NAME = "x12y16pxMaruMonica";
constexpr int SCORE_FONT_SIZE = 24;
constexpr int RESULT_FONT_SIZE = 52;
constexpr int RESULT_SCORE_FONT_SIZE = 24;
constexpr int COMMAND_FONT_SIZE = 20;