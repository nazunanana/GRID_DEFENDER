#include "App.h"
#include "DxLib.h"
#include "Config.h"


/*
アプリ、DxLibの実行・終了制御
*/

// TODO: タイトルシーンのセット・ドロー、BGMロード

// DxLib初期化
bool App::InitDxLib_()
{
	ChangeWindowMode(TRUE);
	SetGraphMode(SCREEN_W, SCREEN_H, 32);

	if (DxLib_Init() == -1)
		return false;
	
	SetDrawScreen(DX_SCREEN_BACK);
	return true;
}

// DxLibを終わらせる
void App::ShutdownDxLib_()
{
	DxLib_End();
}

// フレームレート制限
void App::LimitFps_()
{
	const int frameMs = 1000 / TARGET_FPS;
	static int prev = GetNowCount();

	int now = GetNowCount();
	int diff = now - prev;

	if (diff < frameMs) // FPSが制限を超えている場合、待機
		WaitTimer(frameMs - diff);

	prev = GetNowCount();
}

int App::Run()
{
    if (!InitDxLib_()) return -1;

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        ClearDrawScreen();
        DrawString(100, 100, "TEST", GetColor(0, 255, 255));
        ScreenFlip();
    }

    ShutdownDxLib_();

    return 0;
}

