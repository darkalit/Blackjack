#include "PauseUI.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "Utils.h"

void PauseUI::Init(const Vec2d& renderSize)
{
    m_RenderSize = renderSize;

    m_Background = &ResourceManager::AddTexture("Assets/pause_background.png");

    m_Continue.Init(ResourceManager::AddTexture("Assets/continue.png"), { 30, 100 });
    m_Menu.Init(ResourceManager::AddTexture("Assets/menu.png"), { 30, 140 });
}

void PauseUI::Update(double dt)
{
    m_Continue.Update(dt);
    m_Menu.Update(dt);

    std::vector<std::string> files = Utils::ListFilesWithExtension("Assets/Skins", ".png");

    if (files.size() != m_SkinButtons.size())
    {
        m_SkinButtons.clear();
        for (int32_t i = 0; i < files.size(); ++i)
        {
            auto& button = m_SkinButtons.emplace_back();
            button.Init(ResourceManager::AddTexture("Assets/empty_button.png"), { 24.0 * i + 46.0, 264.0 });
            button.OnPress = m_ButtonFunc(files[i]);
        }
    }

    for (auto& button : m_SkinButtons)
    {
        button.Update(dt);
    }
}

void PauseUI::Draw()
{
    Renderer::Draw(*m_Background);

    for (auto& button : m_SkinButtons)
    {
        button.Draw();
    }

    m_Continue.Draw();
    m_Menu.Draw();
}

void PauseUI::SetButtonFunc(const std::function<std::function<void()>(const std::string&)>& func)
{
    m_ButtonFunc = func;
}
