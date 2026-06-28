#include "Input.h"
#include "DxLib.h"

// 入力の更新
void Input::Update()
{
    SetMouseDispFlag(GetWindowActiveFlag() ? FALSE : TRUE);
    for (int i = 0; i < (int)Action::COUNT; ++i)
    {
        m_curr[i] = GetActionDown_((Action)i);
    }
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    m_mousePos = {(float)mouseX, (float)mouseY};
}

// キーが押されていた場合trueを返す
bool Input::Pressed(Action a) const
{
    return m_curr[(int)a] != 0;
}

// マウスの位置を取得
Vec2 Input::GetMousePosition() const
{
    return m_mousePos;
}

// Actionとキーの結び付け　入力されていれば1を返す
int Input::GetActionDown_(Action a)
{
    switch (a)
    {
    case Action::Shoot:
        return IsMouseDown_(MOUSE_INPUT_LEFT);
    case Action::Decide:
        return IsKeyDown_(KEY_INPUT_X);
    case Action::Back:
        return IsKeyDown_(KEY_INPUT_C);
    case Action::Quit:
        return IsKeyDown_(KEY_INPUT_ESCAPE);
    default:
        return 0;
    }
}

// キーが押されているかどうかを返す
int Input::IsKeyDown_(int key)
{
    return CheckHitKey(key);
}

// マウスが押されているかどうかを返す
int Input::IsMouseDown_(int button)
{
    int currentMouseState = (GetMouseInput() & button) ? 1 : 0;
    int trigger = (m_lastMouseState == 0 && currentMouseState == 1) ? 1 : 0;
    m_lastMouseState = currentMouseState; // 状態を更新
    return trigger;
}