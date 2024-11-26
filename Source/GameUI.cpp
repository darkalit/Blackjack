#include "GameUI.h"

#include "Renderer.h"
#include "ResourceManager.h"

void GameUI::Init(const Vec2d& renderSize)
{
    m_Navbar = &ResourceManager::AddTexture("Assets/navbar.png");

    m_Stay.Init(ResourceManager::AddTexture("Assets/stop.png"), { renderSize.x - 70.0, renderSize.y - 100.0 });
    m_Hit.Init(ResourceManager::AddTexture("Assets/hit.png"), { renderSize.x - 70.0, renderSize.y - 200.0 });
    m_Pause.Init(ResourceManager::AddTexture("Assets/pause.png"), { 4, 2 });

    m_Start.Init(ResourceManager::AddTexture("Assets/bet.png"), { 70.0, renderSize.y - 70.0 });
    m_5Bet.Init(ResourceManager::AddTexture("Assets/chip.png"), { 10.0, renderSize.y - 70.0 });
    m_25Bet.Init(ResourceManager::AddTexture("Assets/chip_red.png"), { 10.0, renderSize.y - 130.0 });
    m_100Bet.Init(ResourceManager::AddTexture("Assets/chip_blue.png"), { 10.0, renderSize.y - 190.0 });
    m_500Bet.Init(ResourceManager::AddTexture("Assets/chip_black.png"), { 10.0, renderSize.y - 250.0 });
}

void GameUI::Update(double dt)
{
    m_5Bet.Update(dt);
    m_25Bet.Update(dt);
    m_100Bet.Update(dt);
    m_500Bet.Update(dt);

    m_Start.Update(dt);
    m_Stay.Update(dt);
    m_Hit.Update(dt);
    m_Pause.Update(dt);
}

void GameUI::Draw(int32_t bet, int32_t cash)
{
    Renderer::Draw(*m_Navbar, { 0, 0 });
    Renderer::Draw(bet, { 94, 5 });
    Renderer::Draw(cash, { 397 , 5 });

    m_Hit.Draw();
    m_Stay.Draw();
    m_Start.Draw();
    m_Pause.Draw();

    m_5Bet.Draw();
    m_25Bet.Draw();
    m_100Bet.Draw();
    m_500Bet.Draw();
}
