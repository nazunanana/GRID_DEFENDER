#include "DxLib.h"
#include "Core/App.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // APPクラスを生成
    App app;
    // Run()を呼ぶ
    return app.Run();
}