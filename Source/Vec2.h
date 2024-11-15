#pragma once
#include <cstdint>

template <typename T>
struct Vec2
{
    Vec2();

    template <typename S>
    Vec2(S _x, S _y);
    Vec2(const Vec2& other);

    template <typename S>
    operator Vec2<S> const();

    Vec2& operator=(const Vec2& rhs);

    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2& operator+=(const Vec2& rhs);
    Vec2& operator-=(const Vec2& rhs);

    template <typename S>
    Vec2 operator+(S scalar) const;

    template <typename S>
    Vec2 operator-(S scalar) const;

    template <typename S>
    Vec2 operator*(S scalar) const;

    template <typename S>
    Vec2 operator/(S scalar) const;

    template <typename S>
    Vec2& operator+=(S scalar);

    template <typename S>
    Vec2& operator-=(S scalar);

    template <typename S>
    Vec2& operator*=(S scalar);

    template <typename S>
    Vec2& operator/=(S scalar);

    bool operator==(const Vec2& rhs) const;
    bool operator!=(const Vec2& rhs) const;

    Vec2 normalize() const;
    T magnitude() const;

    T x;
    T y;
};

typedef Vec2<double> Vec2d;
typedef Vec2<float> Vec2f;
typedef Vec2<uint32_t> Vec2u;
typedef Vec2<int32_t> Vec2i;

template <typename T>
Vec2<T>::Vec2() : x(T{}), y(T{}) {}

template <typename T>
template <typename S>
Vec2<T>::Vec2(S _x, S _y) : x(static_cast<T>(_x)), y(static_cast<T>(_y)) {}

template <typename T>
Vec2<T>::Vec2(const Vec2& other) : x(other.x), y(other.y) {}

template <typename T>
template <typename S>
Vec2<T>::operator Vec2<S> const()
{
    return { static_cast<S>(x), static_cast<S>(y) };
}

template <typename T>
Vec2<T>& Vec2<T>::operator=(const Vec2& rhs)
{
    x = rhs.x;
    y = rhs.y;

    return *this;
}

template <typename T>
Vec2<T> Vec2<T>::operator+(const Vec2& rhs) const
{
    return Vec2{ x + rhs.x, y + rhs.y };
}

template <typename T>
Vec2<T> Vec2<T>::operator-(const Vec2& rhs) const
{
    return Vec2{ x - rhs.x, y - rhs.y };
}

template <typename T>
Vec2<T>& Vec2<T>::operator+=(const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

template <typename T>
Vec2<T>& Vec2<T>::operator-=(const Vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

template <typename T>
template <typename S>
Vec2<T> Vec2<T>::operator+(S scalar) const
{
    return Vec2(x + static_cast<T>(scalar), y + static_cast<T>(scalar));
}

template <typename T>
template <typename S>
Vec2<T> Vec2<T>::operator-(S scalar) const
{
    return Vec2{ x - static_cast<T>(scalar), y - static_cast<T>(scalar) };
}

template <typename T>
template <typename S>
Vec2<T> Vec2<T>::operator*(S scalar) const
{
    return Vec2{ x * static_cast<T>(scalar), y * static_cast<T>(scalar) };
}

template <typename T>
template <typename S>
Vec2<T> Vec2<T>::operator/(S scalar) const
{
    return Vec2{ x / static_cast<T>(scalar), y / static_cast<T>(scalar) };
}

template <typename T>
template <typename S>
Vec2<T>& Vec2<T>::operator+=(S scalar)
{
    x += static_cast<T>(scalar);
    y += static_cast<T>(scalar);

    return *this;
}

template <typename T>
template <typename S>
Vec2<T>& Vec2<T>::operator-=(S scalar)
{
    x -= static_cast<T>(scalar);
    y -= static_cast<T>(scalar);

    return *this;
}

template <typename T>
template <typename S>
Vec2<T>& Vec2<T>::operator*=(S scalar)
{
    x *= static_cast<T>(scalar);
    y *= static_cast<T>(scalar);

    return *this;
}

template <typename T>
template <typename S>
Vec2<T>& Vec2<T>::operator/=(S scalar)
{
    x /= static_cast<T>(scalar);
    y /= static_cast<T>(scalar);

    return *this;
}

template <typename T>
bool Vec2<T>::operator==(const Vec2& rhs) const
{
    return x == rhs.x && y == rhs.y;
}

template <typename T>
bool Vec2<T>::operator!=(const Vec2& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
Vec2<T> Vec2<T>::normalize() const
{
    return *this / this->magnitude();
}

template <typename T>
T Vec2<T>::magnitude() const
{
    return sqrt(x * x + y * y);
}
