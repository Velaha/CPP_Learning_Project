#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <numeric>

template <size_t Dimension, typename Type> class Pointv2
{
private:
    /* data */
    template <typename... Values> std::array<Type, Dimension> make(Values&&... elements)
    {
        return std::array<Type, Dimension> { std::forward<Values>(elements)... };
    }

public:
    std::array<Type, Dimension> values {};

    Pointv2(/* args */) = default;
    ~Pointv2()          = default;

    template <typename... Values> Pointv2(Values&&... elements) : values { std::forward<Values>(elements)... }
    {
        static_assert(Dimension == sizeof...(elements));
    }

    /*
    template <typename... Values> Pointv2(Values&&... elements) : values { make(elements...) }
    {
        static_assert(Dimension == sizeof...(elements));
    }
    */

    Type& x() { return values[0]; }
    Type x() const { return values[0]; }

    Type& y()
    {
        static_assert(Dimension >= 2);
        return values[1];
    }
    Type y() const
    {
        static_assert(Dimension >= 2);
        return values[1];
    }

    Type& z()
    {
        static_assert(Dimension >= 3);
        return values[2];
    }
    Type z() const
    {
        static_assert(Dimension >= 3);
        return values[2];
    }

    Pointv2<Dimension, Type>& operator+=(const Pointv2<Dimension, Type>& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(), std::plus<Type>());

        return *this;
    }

    Pointv2& operator-=(const Pointv2& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       std::minus<Type>());
        return *this;
    }

    Pointv2& operator*=(const Pointv2& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       std::multiplies<Type>());
        return *this;
    }

    Pointv2& operator*=(const float scalar)
    {
        std::transform(values.begin(), values.end(), values.begin(),
                       [scalar](float v) { return v * scalar; });
        return *this;
    }

    Pointv2 operator+(const Pointv2& other) const
    {
        Pointv2 result = *this;
        result += other;
        return result;
    }

    Pointv2 operator-(const Pointv2& other) const
    {
        Pointv2 result = *this;
        result -= other;
        return result;
    }

    Pointv2 operator*(const Pointv2& other) const
    {
        Pointv2 result = *this;
        result *= other;
        return result;
    }

    Pointv2 operator*(const float scalar) const
    {
        Pointv2 result = *this;
        result *= scalar;
        return result;
    }

    Pointv2 operator-() const { return Pointv2<Dimension, Type>(-x(), -y(), -z()); }

    float length() const
    {
        return std::sqrt(std::reduce(values.begin(), values.end(), 0.f,
                                     [](float acc, float cur) { return acc + (cur * cur); }));
    }

    float distance_to(const Pointv2& other) const { return (*this - other).length(); }

    Pointv2& normalize(const float target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Pointv2& cap_length(const float max_len)
    {
        assert(max_len > 0);

        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }
};
