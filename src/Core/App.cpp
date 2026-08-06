#include "App.h"
#include "DxLib.h"
#include "Config.h"
// #include "../Scene/SceneManager.h"
#include <memory>

/*
アプリ、DxLibの実行・終了制御
*/

App::App()
{
	m_input = std::make_unique<Input>();
	m_scene = std::make_unique<SceneManager>(m_input.get());
}

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
	if (!InitDxLib_())
		return -1;

	m_time.Reset();
	m_scene->RequestChange(SceneType::Title);

	// BGMとSEの読み込み
	AudioManager::Instance().LoadBgm("menuBgm", "audio/Introduction.mp3");
	AudioManager::Instance().LoadBgm("gameBgm", "audio/ZONE_-X13-.mp3");
	AudioManager::Instance().LoadSe("shootSe", "audio/beam-gun03.mp3");
	AudioManager::Instance().LoadSe("hitSe", "audio/beam-gun01.mp3");
	AudioManager::Instance().LoadSe("chainSe", "audio/Cyber21-1.mp3");
	AudioManager::Instance().LoadSe("chainSe2", "audio/Cyber21-2.mp3");
	AudioManager::Instance().LoadSe("levelUp", "audio/8bitkaihuku3.mp3");

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		m_time.Update(); // タイマーカウント

		ClearDrawScreen();

		m_input->Update();
		m_scene->Update(m_time.DeltaTime());
		m_scene->Draw();

		ScreenFlip();
		LimitFps_();
	}

	ShutdownDxLib_();
	return 0;
}
