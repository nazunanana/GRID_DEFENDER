#pragma once
#include "../Input/input.h"
#include "../Scene/SceneManager.h"
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