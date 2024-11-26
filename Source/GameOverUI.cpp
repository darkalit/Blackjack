#include "GameOverUI.h"

#include "Renderer.h"
#include "ResourceManager.h"

void GameOverUI::Init(const Vec2d& renderSize)
{
    m_RenderSize = renderSize;

    m_Background = &ResourceManager::AddTexture("Assets/game_over.png");

    m_Restart.Init(ResourceManager::AddTexture("Assets/restart.png"), {});
    m_Restart.Pos = {
        (m_RenderSize.x - m_Restart.GetSize().x) / 2,
        (m_RenderSize.y - m_Background->GetSize().y) / 2 + m_Background->GetSize().y / 3,
    };

    m_Menu.Init(ResourceManager::AddTexture("Assets/menu.png"), {});
    m_Menu.Pos = {
        (m_RenderSize.x - m_Menu.GetSize().x) / 2,
        (m_RenderSize.y - m_Background->GetSize().y) / 2 + 2 * m_Background->GetSize().y / 3,
    };
}

void GameOverUI::Update(double dt)
{
    m_Restart.Update(dt);
    m_Menu.Update(dt);
}

void GameOverUI::Draw()
{
    Renderer::Draw(*m_Background, {
        (m_RenderSize.x - m_Background->GetSize().x) / 2,
        (m_RenderSize.y - m_Background->GetSize().y) / 2
    });

    m_Restart.Draw();
    m_Menu.Draw();
}
