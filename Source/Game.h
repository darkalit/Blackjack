#pragma once
#include <cstdint>
#include <queue>
#include <random>
#include <vector>

#include "Button.h"
#include "Card.h"
#include "EventSystem.h"
#include "GameOverUI.h"
#include "GameUI.h"
#include "MenuUI.h"
#include "Music.h"
#include "PauseUI.h"
#include "ResultsUI.h"
#include "Sound.h"
#include "Timer.h"
#include "Window.h"

class Game
{
public:
    Game(int32_t width, int32_t height, bool fullscreen = false);
    ~Game();
    void Launch();

private:
    enum class State : uint8_t
    {
        MENU,
        PAUSE,
        BET,
        IDLE,
        RESULTS,
        RESET_DECKS,
        GAME_OVER,

        DEALER_REFILL,
        DEALER_HIT,
        PLAYER_REFILL,
        PLAYER_HIT,
        PLAYER_STAND,
    };

    void Init();
    void Tick();
    void ProcessInput();
    void Update();
    void Draw();

    void SetState(State state);
    void ResetDecks();
    void AddCardToPlayerDeck(Card& card);
    void AddCardToDealerDeck(Card& card);
    bool AllOfCardsState(const std::vector<Card>& cards, Card::State state);
    bool AllOfCardsBasePosEqPos(const std::vector<Card>& cards);
    ResultsUI::Outcome GetOutcome();
    int32_t CalculatePoints(const std::vector<Card>& cards) const;

    bool m_ShouldClose = false;
    double m_Dt = 1.0 / 60.0;
    double m_FrameTime = 0.0;
    Vec2i m_RendererSize = { 512, 288 };

    Window m_Window;

    Timer m_Timer;
    EventSystem m_EventSystem;
    std::random_device m_Rd;
    std::mt19937 m_Generator;

    GameUI m_GameUI;
    ResultsUI m_ResultsUI;
    MenuUI m_MenuUI;
    GameOverUI m_GameOverUI;
    PauseUI m_PauseUI;
    ResultsUI::Outcome m_Outcome;

    State m_OldState = State::MENU;
    State m_NewState = State::MENU;

    int32_t m_Cash = 1500;
    int32_t m_Bet = 0;

    int32_t m_MaxPoints = 21;
    int32_t m_PlayerPoints = 0;
    int32_t m_DealerPoints = 0;
    std::vector<Card> m_Deck = {};
    std::vector<Card> m_PlayerDeck = {};
    std::vector<Card> m_DealerDeck = {};

    Texture* m_Background;
    Texture* m_Skin;

    Sound* m_ButtonPress;
    Sound* m_BetPress;
    Sound* m_BetConfirmPress;
    Sound* m_Bust;
    Sound* m_Win;
    Sound* m_Push;
    Sound* m_CardSweep;
    Sound* m_HitPress;
    Sound* m_StayPress;

    Music* m_BackgroundMusic;
};

