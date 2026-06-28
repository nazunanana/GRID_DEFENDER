#pragma once
#include "../GameSystem/Common.h"
#include <array>

enum class Action
{
    Shoot,
    Decide,
    Back,
    Quit,

    COUNT
};

class Input
{
public:
    void Update();                 // 入力の更新
    bool Pressed(Action a) const;  // キーが押されていた場合trueを返す
    Vec2 GetMousePosition() const; // マウスの位置を取得

private:
    std::array<int, (int)Action::COUNT> m_curr{}; // アクションごとの入力状況
    Vec2 m_mousePos{};                            // マウスの位置
    int m_lastMouseState = 0;
    int GetActionDown_(Action a);  // Actionとキーの結び付け　入力されていれば1を返す
    static int IsKeyDown_(int key);      // キーが押されているかどうかを返す
    int IsMouseDown_(int button); // マウスが押されているかどうかを返す
};