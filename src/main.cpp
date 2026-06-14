#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // ウインドウモードに変更
    ChangeWindowMode(TRUE);
    // 画面サイズをサイバーゲームっぽく 640x480 (または 800x600) に設定
    SetGraphMode(640, 480, 32);

    // DXライブラリ初期化処理
    if (DxLib_Init() == -1) return -1;

    // 描画先を裏画面に設定（これを行うことで画面のチラつきを防ぎます）
    SetDrawScreen(DX_SCREEN_BACK);

    // ゲームループ
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        // 画面をクリア（真っ黒にする、電脳世界のスタート！）
        ClearDrawScreen();

        // 💡 ここにゲームの処理を書いていきます
        DrawString(100, 100, "TEST", GetColor(0, 255, 255));

        // 裏画面の内容を表画面に反映
        ScreenFlip();
    }

    // DXライブラリ使用の終了処理
    DxLib_End();

    return 0;
}