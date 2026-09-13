#include "DxLib.h"
#include "Core/App.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // リリース用
    // char exePath[MAX_PATH];
    // GetModuleFileNameA(NULL, exePath, MAX_PATH);
    // if (char *p = strrchr(exePath, '\\'))
    //     *p = '\0';
    // SetCurrentDirectoryA(exePath);
    // SetOutApplicationLogValidFlag(FALSE); // Log.txt を出力しない

    SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
    SetWindowIconID(101);

    // APPクラスを生成
    App app;
    // Run()を呼ぶ
    return app.Run();
}