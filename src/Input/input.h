#pragma once
#include <array>

struct Vector2 {
    float x;
    float y;
};

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
    void Update(); // 入力の更新
    bool Pressed(Action a) const; // キーが押されていた場合trueを返す
    Vector2 GetMousePosition() const; // マウスの位置を取得

private:
    std::array<int, (int)Action::COUNT> m_curr{}; // アクションごとの入力状況
    Vector2 m_mousePos{}; // マウスの位置  

    int GetActionDown_(Action a) const;// Actionとキーの結び付け　入力されていれば1を返す
    static int IsKeyDown_(int key); // キーが押されているかどうかを返す
    static int IsMouseDown_(int button); // マウスが押されているかどうかを返す
};