#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <numeric>

template <size_t Dimension, typename Type> class Point
{
private:
    /* data */

public:
    std::array<Type, Dimension> values {};

    Point(/* args */) = default;
    ~Point()          = default;

    Point(Type e1, Type e2) : values { e1, e2 } {}
    Point(Type e1, Type e2, Type e3) : values { e1, e2, e3 } {}

    Type& x() { return values[0]; }
    Type x() const { return values[0]; }

    Type& y() { return values[1]; }
    Type y() const { return values[1]; }

    Type& z() { return values[2]; }
    Type z() const { return values[2]; }

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

    Point& operator*=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       std::multiplies<Type>());
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

    Point operator*(const Point& other) const
    {
        Point result = *this;
        result *= other;
        return result;
    }

    Point operator*(const float scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    Point operator-() const { return Point<Dimension, Type>(-x(), -y(), -z()); }

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
