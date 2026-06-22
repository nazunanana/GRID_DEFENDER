#pragma once

class SceneManager;
class Input;

/*
シーンインターフェース
*/

class IScene
{
public:
    // コンストラクタ
    IScene(SceneManager* mgr, Input* input)
        : m_sceneMgr(mgr), m_input(input) {}
    virtual ~IScene() = default;

    // シーンに入ったときの処理
    virtual void Enter() {}
    // シーンから出たときの処理
    virtual void Exit() {}
    // シーンの更新
    virtual void Update() = 0;
    // シーンの描画
    virtual void Draw() = 0;

protected:
    SceneManager* m_sceneMgr;
    Input* m_input;
};