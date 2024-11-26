#include "Game.h"

#include <iostream>

#include "Input.h"
#include "Mixer.h"
#include "Renderer.h"
#include "ResourceManager.h"

Game::Game(int32_t width, int32_t height, bool fullscreen)
    : m_Window("Blackjack", { width, height }, fullscreen ? Window::FULLSCREEN : Window::RESIZABLE)
    , m_Generator(m_Rd())
{
    Renderer::Init(m_Window, m_RendererSize);
    Mixer::Init();
    m_GameUI.Init(m_RendererSize);
    m_ResultsUI.Init(m_RendererSize);
    m_MenuUI.Init(m_RendererSize);
    m_GameOverUI.Init(m_RendererSize);
    m_PauseUI.Init(m_RendererSize);

    m_Skin = &ResourceManager::AddTexture("Assets/Skins/default.png");
    m_Background = &ResourceManager::AddTexture("Assets/background.png");

    m_ButtonPress = &ResourceManager::AddSound("Assets/Sounds/button.wav");
    m_BetPress = &ResourceManager::AddSound("Assets/Sounds/bet.wav");
    m_BetConfirmPress = &ResourceManager::AddSound("Assets/Sounds/bet_confirm.wav");
    m_Bust = &ResourceManager::AddSound("Assets/Sounds/hand_lost.wav");
    m_Win = &ResourceManager::AddSound("Assets/Sounds/hand_won.wav");
    m_Push = &ResourceManager::AddSound("Assets/Sounds/bust1.wav");
    m_CardSweep = &ResourceManager::AddSound("Assets/Sounds/sweep.wav");
    m_HitPress = &ResourceManager::AddSound("Assets/Sounds/hit.wav");
    m_StayPress = &ResourceManager::AddSound("Assets/Sounds/stay.wav");
    
    m_BackgroundMusic = &ResourceManager::AddMusic("Assets/Sounds/music.wav");

    Mixer::Play(*m_BackgroundMusic);
}

Game::~Game()
{
    Renderer::Destroy();
}

void Game::Launch()
{
    Init();

    while(!m_ShouldClose)
    {
        Tick();
    }
}

void Game::Init()
{
    m_EventSystem.OnQuit = [this]
        {
            this->m_ShouldClose = true;
        };

    m_GameUI.SetOnHit([this]
        {
            if (m_NewState == State::IDLE) {
                Mixer::Play(*m_HitPress);
                SetState(State::PLAYER_HIT);
            }
        });
    m_GameUI.SetOnStay([this]
        {
            if (m_NewState == State::IDLE) {
                Mixer::Play(*m_StayPress);
                SetState(State::PLAYER_STAND);
            }
        });
    m_GameUI.SetOnStart([this]
        {
            if (m_NewState == State::BET && m_Bet > 0)
            {
                Mixer::Play(*m_BetConfirmPress);
                SetState(State::PLAYER_REFILL);
            }
        });
    m_GameUI.SetOn5Bet([this]
        {
            if (m_NewState == State::BET && m_Cash >= 5) {
                Mixer::Play(*m_BetPress);
                m_Bet += 5;
                m_Cash -= 5;
            }
        });
    m_GameUI.SetOn25Bet([this]
        {
            if (m_NewState == State::BET && m_Cash >= 25) {
                Mixer::Play(*m_BetPress);
                m_Bet += 25;
                m_Cash -= 25;
            }
        });
    m_GameUI.SetOn100Bet([this]
        {
            if (m_NewState == State::BET && m_Cash >= 100) {
                Mixer::Play(*m_BetPress);
                m_Bet += 100;
                m_Cash -= 100;
            }
        });
    m_GameUI.SetOn500Bet([this]
        {
            if (m_NewState == State::BET && m_Cash >= 500) {
                Mixer::Play(*m_BetPress);
                m_Bet += 500;
                m_Cash -= 500;
            }
        });
    m_GameUI.SetOnPause([this]
        {
            Mixer::Play(*m_ButtonPress);
            if (m_NewState == State::BET || m_NewState == State::IDLE)
            {
                SetState(State::PAUSE);
            }
        });

    m_GameOverUI.SetOnRestart([this]
        {
            Mixer::Play(*m_ButtonPress);
            SetState(State::RESET_DECKS);
            m_Bet = 0;
            m_Cash = 1500;
        });
    m_GameOverUI.SetOnMenu([this]
        {
            Mixer::Play(*m_ButtonPress);
            SetState(State::MENU);
        });

    m_MenuUI.SetOnStart([this]
        {
            Mixer::Play(*m_ButtonPress);
            ResetDecks();
            SetState(State::BET);
            m_Bet = 0;
            m_Cash = 1500;
        });
    m_MenuUI.SetOnExit([this]
        {
            Mixer::Play(*m_ButtonPress);
            m_ShouldClose = true;
        });

    m_PauseUI.SetOnContinue([this]
        {
            Mixer::Play(*m_ButtonPress);
            SetState(m_OldState);
        });
    m_PauseUI.SetOnMenu([this]
        {
            Mixer::Play(*m_ButtonPress);
            SetState(State::MENU);
        });
    m_PauseUI.SetButtonFunc([this](const std::string& filename)
        {
            return [this, filename]
                {
                    Mixer::Play(*m_ButtonPress);
                    ResourceManager::RemoveTexture(m_Skin->GetFilename());
                    m_Skin = &ResourceManager::AddTexture(filename);
                };
        });

    ResetDecks();
}

void Game::Tick()
{
    ProcessInput();
    m_Timer.Reset();

    m_FrameTime = m_Timer.Dt();
    while (m_FrameTime > 0.0) {
        Update();
    }

    Draw();
}

void Game::ProcessInput()
{
    m_EventSystem.Poll();
}

void Game::Update()
{
    double deltaTime = std::min(m_FrameTime, m_Dt);
    m_DealerPoints = CalculatePoints(m_DealerDeck);
    m_PlayerPoints = CalculatePoints(m_PlayerDeck);

    switch (m_NewState)
    {
    case State::MENU:
        m_MenuUI.Update(deltaTime);
        break;
    case State::PAUSE:
        m_PauseUI.Update(deltaTime);

        break;
    case State::BET:
        break;
    case State::IDLE:
        break;
    case State::RESULTS:
        if (m_ResultsUI.IsStarted())
        {
            switch (GetOutcome())
            {
            case ResultsUI::Outcome::WIN:
                Mixer::Play(*m_Win);
                m_Cash += m_Bet * 2;
                break;
            case ResultsUI::Outcome::BUST:
                Mixer::Play(*m_Bust);
                break;
            case ResultsUI::Outcome::PUSH:
                Mixer::Play(*m_Push);
                m_Cash += m_Bet;
                break;
            case ResultsUI::Outcome::BLACKJACK:
                Mixer::Play(*m_Win);
                m_Cash += m_Bet * 2.5;
            }

            m_Bet = 0;
        }

        if (m_ResultsUI.IsEnded())
        {
            SetState(State::RESET_DECKS);
            if (GetOutcome() == ResultsUI::Outcome::BUST && m_Cash < 5)
            {
                SetState(State::GAME_OVER);
            }            
        }

        m_Outcome = GetOutcome();
        m_ResultsUI.Update(deltaTime, m_Outcome);
        
        break;

    case State::RESET_DECKS:
        if (!AllOfCardsState(m_PlayerDeck, Card::State::MOVE)) {
            for (auto& card : m_PlayerDeck)
            {
                card.BasePos = m_Deck.back().BasePos;
                card.SetState(Card::State::FRONT);
                card.SetState(Card::State::MOVE);
            }
        }

        if (!AllOfCardsState(m_DealerDeck, Card::State::MOVE)) {
            for (auto& card : m_DealerDeck)
            {
                card.BasePos = m_Deck.back().BasePos;
                card.SetState(Card::State::FRONT);
                card.SetState(Card::State::MOVE);
            }
        }

        if (AllOfCardsBasePosEqPos(m_PlayerDeck) && AllOfCardsBasePosEqPos(m_DealerDeck)) {
            ResetDecks();
            SetState(State::BET);
        }
        break;
    case State::GAME_OVER:
        m_GameOverUI.Update(deltaTime);

        break;
    case State::DEALER_REFILL:
        if (m_DealerDeck.size() < 2) {
            if (m_DealerDeck.empty() || m_DealerDeck.back().GetState() != Card::State::MOVE) {
                Mixer::Play(*m_CardSweep);
                AddCardToDealerDeck(m_Deck.back());
                m_Deck.pop_back();
            }
            break;
        }

        if (m_PlayerDeck.empty() || m_PlayerDeck.back().GetState() != Card::State::MOVE) {
            SetState(State::IDLE);
        }

        break;
    case State::DEALER_HIT:
        if (m_DealerPoints < 17) {
            Mixer::Play(*m_CardSweep);
            AddCardToDealerDeck(m_Deck.back());
            m_Deck.pop_back();
        }

        if (m_DealerDeck.back().GetState() != Card::State::MOVE) {
            SetState(State::RESULTS);
        }

        break;
    case State::PLAYER_REFILL:
        if (m_PlayerDeck.size() < 2) {
            if (m_PlayerDeck.empty() || m_PlayerDeck.back().GetState() != Card::State::MOVE) {
                Mixer::Play(*m_CardSweep);
                AddCardToPlayerDeck(m_Deck.back());
                m_Deck.pop_back();
            }
            break;
        }

        if (m_PlayerDeck.empty() || m_PlayerDeck.back().GetState() != Card::State::MOVE) {
            SetState(State::DEALER_REFILL);
        }

        break;
    case State::PLAYER_HIT:
        if (m_PlayerDeck.size() < 3) {
            Mixer::Play(*m_CardSweep);
            AddCardToPlayerDeck(m_Deck.back());
            m_Deck.pop_back();
        }

        if (m_PlayerDeck.back().GetState() != Card::State::MOVE) {
            m_DealerDeck.front().SetState(Card::State::FLIP);

            SetState(State::DEALER_HIT);
        }        

        break;
    case State::PLAYER_STAND:
        m_DealerDeck.front().SetState(Card::State::FLIP);

        if (m_PlayerPoints >= m_DealerPoints && m_DealerPoints < m_MaxPoints)
        {
            SetState(State::DEALER_HIT);
            break;
        }

        SetState(State::RESULTS);
        break;
    }

    for (auto& card : m_PlayerDeck)
    {
        card.Update(deltaTime);
    }

    for (auto& card : m_DealerDeck)
    {
        card.Update(deltaTime);
    }
    m_Deck.back().Update(deltaTime);
    m_GameUI.Update(deltaTime);

    m_FrameTime -= deltaTime;
}

void Game::Draw()
{
    Renderer::Clear();
    Renderer::Draw(*m_Background);

    if (!m_Deck.empty()) {
        m_Deck.back().Draw();
    }

    for (auto& card : m_PlayerDeck)
    {
        card.Draw();
    }

    for (auto& card : m_DealerDeck)
    {
        card.Draw();
    }

    switch (m_NewState)
    {
    case State::MENU:
        m_MenuUI.Draw();
        break;
    case State::PAUSE:
        m_PauseUI.Draw();
        break;
    case State::GAME_OVER:
        m_GameOverUI.Draw();
        break;
    case State::BET:
    case State::IDLE:
    case State::RESET_DECKS:
    case State::DEALER_HIT:
    case State::DEALER_REFILL:
    case State::PLAYER_HIT:
    case State::PLAYER_REFILL:
        m_GameUI.Draw(m_Bet, m_Cash);
        break;
    case State::RESULTS:
        m_ResultsUI.Draw();
        break;

    default:
        break;
    }

    Renderer::Flush();
}

void Game::SetState(State state)
{
    m_OldState = m_NewState;
    m_NewState = state;
}

void Game::ResetDecks()
{
    m_Deck.clear();
    m_PlayerDeck.clear();
    m_DealerDeck.clear();
    for (int32_t i = 0; i <= static_cast<int32_t>(Card::Suit::LAST); ++i)
    {
        Card::Suit suit = static_cast<Card::Suit>(i);

        for (int32_t j = 0; j <= static_cast<int32_t>(Card::Rank::LAST); ++j)
        {
            Card::Rank rank = static_cast<Card::Rank>(j);
            m_Deck.emplace_back(Card(m_Skin, { 88, 50 }, { 48, 64 }, suit, rank));
        }
    }

    std::shuffle(m_Deck.begin(), m_Deck.end(), m_Generator);
}

void Game::AddCardToPlayerDeck(Card& card)
{
    m_PlayerDeck.push_back(std::move(card));
    size_t deckSize = m_PlayerDeck.size();
    int32_t deckWidth = 0;

    for (const auto& cardD : m_PlayerDeck)
    {
        deckWidth += cardD.GetSize().x;
    }

    for (size_t i = 0; i < deckSize; ++i)
    {
        m_PlayerDeck[i].BasePos = { (m_RendererSize.x - deckWidth) / 2.0 + m_PlayerDeck[i].GetSize().x * i + 2.0 * i, m_RendererSize.y - 80.0 };
        m_PlayerDeck[i].SetState(Card::State::FRONT);
        m_PlayerDeck[i].SetState(Card::State::MOVE);
    }
}

void Game::AddCardToDealerDeck(Card& card)
{
    card.BasePos = { card.BasePos.x + 80.0, card.BasePos.y };
    if (m_DealerDeck.empty())
    {
        card.SetState(Card::State::FLIPPED);
    } else
    {
        card.SetState(Card::State::FRONT);
    }
    card.SetState(Card::State::MOVE);
    m_DealerDeck.push_back(card);
    size_t deckSize = m_DealerDeck.size();

    for (size_t i = 0; i < deckSize; ++i)
    {
        m_DealerDeck[i].BasePos.x = card.BasePos.x + m_DealerDeck[i].GetSize().x * i + 2.0 * i;
    }
}

bool Game::AllOfCardsState(const std::vector<Card>& cards, Card::State state)
{
    return std::all_of(cards.begin(), cards.end(), [state](const Card& c)
        {
            return c.GetState() == state;
        });
}

bool Game::AllOfCardsBasePosEqPos(const std::vector<Card>& cards)
{
    return std::all_of(cards.begin(), cards.end(), [](const Card& c)
        {
            return c.Pos == c.BasePos;
        });
}

ResultsUI::Outcome Game::GetOutcome()
{
    if (m_PlayerPoints > m_DealerPoints && m_PlayerPoints == m_MaxPoints && m_PlayerDeck.size() == 2)
    {
        return ResultsUI::Outcome::BLACKJACK;
    }

    if ((m_PlayerPoints > m_DealerPoints || m_DealerPoints > m_MaxPoints) && m_PlayerPoints <= m_MaxPoints)
    {
        return ResultsUI::Outcome::WIN;
    }

    if (m_PlayerPoints == m_DealerPoints && m_DealerPoints < m_MaxPoints)
    {
        return ResultsUI::Outcome::PUSH;
    }

    return ResultsUI::Outcome::BUST;
}

int32_t Game::CalculatePoints(const std::vector<Card>& cards) const
{
    int32_t points = 0;

    std::vector<Card> sortedCards = cards;
    std::sort(sortedCards.begin(), sortedCards.end(), [](const Card& a, const Card& b)
        {
            return a.GetRank() < b.GetRank();
        });


    for (const auto& card : sortedCards)
    {
        if (card.GetRank() == Card::Rank::ACE && points + card.GetPoints(true) <= m_MaxPoints)
        {
            points += card.GetPoints(true);
        } else
        {
            points += card.GetPoints(false);
        }
    }

    return points;
}
