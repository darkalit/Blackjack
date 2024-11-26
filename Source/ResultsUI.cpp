#include "ResultsUI.h"

#include <SDL_rect.h>

#include "Renderer.h"
#include "ResourceManager.h"

void ResultsUI::Init(const Vec2d& renderSize)
{
    m_RenderSize = renderSize;

    m_Banner = &ResourceManager::AddTexture("Assets/result_banner.png");
    m_ResultsText = &ResourceManager::AddTexture("Assets/results_text.png");

    Pos = { (m_RenderSize.x - m_Banner->GetSize().x) / 2 , 0.0 };
}

void ResultsUI::Update(double dt, Outcome outcome)
{
    m_Outcome = outcome;

    if (m_T <= 1.0) {
        m_T += dt * 0.75;
        Pos.y = m_RenderSize.y * (m_T < 0.5 ? 0.5 - std::pow(0.84 - m_T, 4) : 0.5 + std::pow(0.16 - m_T, 4));
    } else
    {
        m_T = 0.0;
    }
}

void ResultsUI::Draw()
{
    Renderer::Draw(*m_Banner, Pos);

    SDL_Rect clip = {
        0,
        static_cast<int32_t>(m_Outcome) * m_ResultsText->GetSize().y / (static_cast<int32_t>(Outcome::LAST) + 1),
        m_ResultsText->GetSize().x,
        m_ResultsText->GetSize().y / (static_cast<int32_t>(Outcome::LAST) + 1)
    };
    Renderer::Draw(*m_ResultsText, {
        (m_RenderSize.x - clip.w) / 2, Pos.y + m_Banner->GetSize().y / 2
    }, 0, &clip);
}

bool ResultsUI::IsStarted()
{
    return m_T == 0.0;
}

bool ResultsUI::IsEnded()
{
    return m_T > 1.0;
}
