#include "Card.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture.h"

double Card::s_MoveAnimTime = 0.4;
double Card::s_FlipAnimTime = 0.04;

Card::Card(const Vec2d& pos, const Vec2d& size, Suit suit, Rank rank)
    : BasePos(pos)
    , m_Suit(suit)
    , m_Rank(rank)
{
    m_Size = size;
    Pos = pos;

    m_Texture = &ResourceManager::AddTexture("Assets/cards.png");
}

Card& Card::operator=(const Card& other)
{
    if (this == &other)
        return *this;
    GameObject::operator =(other);
    BasePos = other.BasePos;
    m_Suit = other.m_Suit;
    m_Rank = other.m_Rank;
    m_OldState = other.m_OldState;
    m_NewState = other.m_NewState;
    m_T = other.m_T;
    m_Texture = other.m_Texture;
    return *this;
}

void Card::Update(double dt)
{
    double t;
    switch (m_NewState)
    {
    case State::FRONT:
        m_T += dt;
        Pos.y = BasePos.y + sin(16 * atan(1) * m_T + Pos.x / 20.0);
        m_T = m_T > 0.5 ? 0.0 : m_T;
        break;

    case State::MOVE:
        m_T -= dt;
        // quart easeIn
        t = 1.0 - m_T / s_MoveAnimTime;
        Pos = Pos + (BasePos - Pos) * pow(t, 4);
        break;

    case State::FLIP:
        m_T -= dt;
        t = m_T / s_FlipAnimTime;
        Pos.x = BasePos.x + (GetClip(false).w - m_Size.x) / 2.0;
        // cubic easeIn
        m_Size.x = GetClip(false).w * pow(t, 3);

        if (m_T < 0.0)
        {
            SetState(State::FRONT);
            SetState(State::FLIP_OUT);
        }
        break;

    case State::FLIP_OUT:
        m_T -= dt;
        t = m_T / s_FlipAnimTime;
        Pos.x = BasePos.x + (GetClip(false).w - m_Size.x) / 2.0;
        // cubic easeIn
        m_Size.x = GetClip(false).w - GetClip(false).w * pow(t, 3);
        break;

    default:
        break;
    }

    if (m_T < 0.0)
    {
        SetState(m_OldState);
    }
}

void Card::Draw()
{
    SDL_Rect clip;
    switch (m_NewState)
    {
    case State::FRONT:
        clip = GetClip(false);
        break;

    case State::FLIPPED:
        clip = GetClip(true);        
        break;

    case State::MOVE:
    case State::FLIP_OUT:
        clip = GetClip(m_OldState == State::FLIPPED);
        break;

    case State::FLIP:
        clip = GetClip(m_OldState == State::FRONT);
        break;
    }

    Renderer::Draw(*m_Texture, Pos, GetSize(), Angle, &clip);
}

Vec2d Card::GetSize() const
{
    if (m_Size == Vec2i{})
    {
        return m_Texture->GetSize();
    }
    return m_Size;
}

Card::Suit Card::GetSuit() const
{
    return m_Suit;
}

Card::Rank Card::GetRank() const
{
    return m_Rank;
}

int32_t Card::GetPoints(bool aceFlag) const
{
    switch (m_Rank)
    {
    case Rank::TWO:
        return 2;
    case Rank::THREE:
        return 3;
    case Rank::FOUR:
        return 4;
    case Rank::FIVE:
        return 5;
    case Rank::SIX:
        return 6;
    case Rank::SEVEN:
        return 7;
    case Rank::EIGHT:
        return 8;
    case Rank::NINE:
        return 9;
    case Rank::TEN:
    case Rank::JACK:
    case Rank::QUEEN:
    case Rank::KING:
        return 10;
    case Rank::ACE:
        return aceFlag ? 11 : 1;
    }

    return 0;
}

void Card::SetState(State state)
{
    // anti softlock
    if (m_NewState != state) {
        m_OldState = m_NewState;
        m_NewState = state;
    }

    switch (state)
    {
    case State::MOVE:
        m_T = s_MoveAnimTime;
        break;

    case State::FLIP:
        m_Size = { GetClip(false).w, GetClip(false).h };
        m_T = s_FlipAnimTime;
        break;

    case State::FLIP_OUT:
        m_T = s_FlipAnimTime;
        break;

    default:
        break;
    }
}

Card::State Card::GetState() const
{
    return m_NewState;
}

SDL_Rect Card::GetClip(bool back) const
{
    Vec2i cardsCount = { 13, 5 };
    Vec2i cardSize = { m_Texture->GetSize().x / cardsCount.x, m_Texture->GetSize().y / cardsCount.y };

    if (back)
    {
        return { 0, 4 * cardSize.y, cardSize.x, cardSize.y };
    }

    int32_t yPos = static_cast<int32_t>(m_Suit);
    int32_t xPos = static_cast<int32_t>(m_Rank);

    return { xPos * cardSize.x, yPos * cardSize.y, cardSize.x, cardSize.y };
}
