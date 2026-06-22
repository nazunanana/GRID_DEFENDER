#pragma once

/*
アプリ、DxLibの実行・終了制御
*/

class App
{
public:
	int Run();

private:
	bool InitDxLib_();
	void ShutdownDxLib_();
	void LimitFps_();

private:

};