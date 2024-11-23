#pragma once

#include <SDL_rect.h>

#include "GameObject.h"

class Texture;

class Card : public GameObject
{
public:
    enum class State : uint8_t
    {
        FRONT,
        FLIPPED,
        MOVE,
        FLIP,
        FLIP_OUT,
    };

    enum class Suit : uint8_t
    {
        DIAMONDS = 0,
        CLUBS,
        HEARTS,
        SPADES,

        LAST = SPADES,
    };

    enum class Rank : uint8_t
    {
        TWO = 0,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        ACE,

        LAST = ACE,
    };

    Card(const Vec2d& pos, const Vec2d& size, Suit suit, Rank rank);

    Card(const Card& other) = default;
    Card& operator=(const Card& other);

    void Update(double dt) override;
    void Draw() override;
    Vec2d GetSize() const override;

    Suit GetSuit() const;
    Rank GetRank() const;
    int32_t GetPoints(bool aceFlag) const;

    void SetState(State state);
    State GetState() const;

    Vec2d BasePos = Pos;

private:
    SDL_Rect GetClip(bool back) const;

    Suit m_Suit;
    Rank m_Rank;

    State m_OldState = State::FLIPPED;
    State m_NewState = State::FLIPPED;
    double m_T = 0.0;

    Texture* m_Texture = nullptr;

    static double s_MoveAnimTime;
    static double s_FlipAnimTime;
};

