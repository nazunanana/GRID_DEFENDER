#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameoverScene.h"
#include "ClearScene.h"

/*
シーンの切り替え、更新処理
*/

// コンストラクタ
SceneManager::SceneManager(Input* input)
    : m_input(input)
{
    m_currScene = std::make_unique<TitleScene>(this, m_input);
    // m_currScene->Enter();
}

void SceneManager::Update()
{
    // シーン変更が予約されている場合は、シーンを切り替える
    if (m_nextScene != nullptr)
    {
        ChangeScene();
    }
    m_nextScene = nullptr;

    // 現在のシーンの更新処理を呼び出す
    m_currScene->Update();
}

void SceneManager::Draw()
{
    // 現在のシーンの描画処理を呼び出す
    if (m_currScene != nullptr)
    {
        m_currScene->Draw();
    }
}

void SceneManager::RequestChange(SceneType type)
{
    // 次のシーンを予約する
    switch (type)
    {
    case SceneType::Title:
        m_nextScene = std::make_unique<TitleScene>(this, m_input);
        break;
    // 他のシーンタイプの処理
    }
}

void SceneManager::ChangeScene()
{
    // 古いシーンの後処理を呼び出す
    if (m_currScene != nullptr)
    {
        m_currScene->Exit();
    }

    m_currScene = std::move(m_nextScene);

    // 新しいシーンに入る処理を呼び出す
    if (m_currScene != nullptr)
    {
        m_currScene->Enter();
    }
}