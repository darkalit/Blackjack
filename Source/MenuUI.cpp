#include "MenuUI.h"

#include "Renderer.h"
#include "ResourceManager.h"

void MenuUI::Init(const Vec2d& renderSize)
{
    m_Start.Init(ResourceManager::AddTexture("Assets/start.png"), { 30, 100 });
    m_Exit.Init(ResourceManager::AddTexture("Assets/quit.png"), { 30, 140 });

    m_Background = &ResourceManager::AddTexture("Assets/menu_background.png");
}

void MenuUI::Update(double dt)
{
    m_Start.Update(dt);
    m_Exit.Update(dt);
}

void MenuUI::Draw()
{
    Renderer::Draw(*m_Background);

    m_Start.Draw();
    m_Exit.Draw();
}
