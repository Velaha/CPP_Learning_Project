#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <numeric>

template <size_t Dimension, typename Type> class Point
{
private:
    /* data */
    std::array<Type, Dimension> values {};

public:
    Point(/* args */) = default;
    ~Point()          = default;

    Point<Dimension, Type>& operator+=(const Point<Dimension, Type>& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(), std::plus<Type>());

        return *this;
    }

    Point& operator-=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       std::minus<Type>());
        return *this;
    }

    Point& operator*=(const float scalar)
    {
        std::transform(values.begin(), values.end(), values.begin(),
                       [scalar](float v) { return v * scalar; });
        return *this;
    }

    Point operator+(const Point& other) const
    {
        Point result = *this;
        result += other;
        return result;
    }

    Point operator-(const Point& other) const
    {
        Point result = *this;
        result -= other;
        return result;
    }

    Point operator*(const float scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    Point operator-() const
    {
        std::transform(values.begin(), values.end(), values.begin(), [](Type value) { return -value; });
        return *this;
    }

    float length() const
    {
        return std::sqrt(std::reduce(values.begin(), values.end(), 0.f,
                                     [](float acc, float cur) { return acc + (cur * cur); }));
    }

    float distance_to(const Point& other) const { return (*this - other).length(); }

    Point& normalize(const float target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point& cap_length(const float max_len)
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
