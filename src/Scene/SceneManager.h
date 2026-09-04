#pragma once
#include "IScene.h"
#include "../GameSystem/Common.h"
#include <memory>

class Input;

enum class SceneType
{
    Title,
    Rule,
    Game,
    Clear,
    GameOver,
};

class SceneManager
{
public:
    SceneManager(Input* input);
    // シーンの更新
    void Update(float df);
    // シーンの描画
    void Draw();
    // シーン変更を予約する
    void RequestChange(SceneType type, Difficulty difficulty = Difficulty::Normal, int score = 0, float remainingTime = 0.0f);
private:
    Input* m_input;
    // 現在のシーンを保持
    std::unique_ptr<IScene> m_currScene;
    // 次のシーンを保持
    std::unique_ptr<IScene> m_nextScene;
    // シーン変更処理
    void ChangeScene();
};