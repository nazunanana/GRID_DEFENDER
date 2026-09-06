#pragma once
#include "../Input/Input.h"
#include "../Scene/SceneManager.h"
#include "../Audio/AudioManager.h"
#include "Time.h"
#include <memory>

/*
アプリ、DxLibの実行・終了制御
*/

class App
{
public:
	App();
	int Run();

private:
	bool InitDxLib_();
	void ShutdownDxLib_();
	void LimitFps_();

private:
    std::unique_ptr<Input> m_input;
    std::unique_ptr<SceneManager> m_scene;
	Time m_time;
};