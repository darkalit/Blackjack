#pragma once

#include <functional>

#include "Texture.h"
#include "GameObject.h"

#define BUTTON_MEMBER(Name) \
public: \
inline void SetOn##Name(const std::function<void()>& func) { \
    m_##Name.OnPress = func; \
}\
private: \
Button m_##Name; \
public: \

class Button : public GameObject
{
public:
    void Init(Texture& texture, const Vec2d& pos);
    void Update(double dt) override;
    void Draw() override;

    Vec2d GetSize() const override;

    std::function<void()> OnPress;

private:
    Texture* m_Texture = nullptr;
    bool m_Held = false;
};
