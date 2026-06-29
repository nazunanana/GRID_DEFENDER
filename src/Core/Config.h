#pragma once

/*
設定値
*/

constexpr int SCREEN_W = 800;  // 横の解像度
constexpr int SCREEN_H = 640;  // 縦の解像度
constexpr int TARGET_FPS = 60; // FPS
constexpr int BOX_SIZE = 40; // ブロックの大きさ
constexpr int ORIGIN_X = 0; // BOX_SIZE; // ブロックのX座標基準値
constexpr int ORIGIN_Y = BOX_SIZE; // ブロックのY座標基準値
constexpr int COL_MAX = 10; // ブロックの縦の最大個数
constexpr int ROW_MAX = SCREEN_W / BOX_SIZE; // ブロックの横の最大個数