#pragma once

#include <algorithm>
#include <numeric>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>

template <typename Type, const unsigned int Dim>
class Point{
    private:
        std::array<Type, Dim> values;
    public:
            Point() = default;
            /*template <typename... Ts>
            Point(Ts&&... params) : values { std::forward<Ts>(params)... } {
                    assert(Dim == sizeof...(Ts) && "Invalide size");
            }*/
            Point(const Type value1, const Type value2) : values {value1, value2}{
                static_assert(Dim == 2 && "Invalide size");
            }
            Point(const Type value1, const Type value2, const Type value3) : values {value1, value2, value3}{
                static_assert(Dim == 3 && "Invalide size");
            }

            Type& x(){ return values[0]; }
            Type x() const{ return values[0]; }
            Type& y(){ return values[1]; }
            Type y() const{ return values[1]; }
            Type& z()
            {
                static_assert(Dim > 2 && "Invalide size");
                return values[2];
            }
            Type z() const
            {
                static_assert(Dim > 2 && "Invalide size");
                return values[2];
            }

            Point<Type, Dim>& operator += (const Point<Type, Dim>& other){
                std::transform(values.begin(), values.end(), other.values.begin(), values.begin(), std::plus<Type> {});
                return *this;
            }

            Point<Type, Dim>& operator -= (const Point<Type, Dim>& other){
                std::transform(values.begin(), values.end(), other.values.begin(), values.begin(), std::minus<Type> {});
                return *this;
            }

            Point<Type, Dim>& operator*=(const Type scalar)
            {
                std::transform(values.begin(), values.end(), values.begin(), [scalar](Type v) { return v * scalar; });
                return *this;
            }

            Point<Type, Dim>& operator*=(const Point<Type, Dim>& other)
            {
                for (auto i = 0u; i < Dim; i++)
                {
                    values[i] *= other.values[i];
                }
                return *this;
            }

            Point<Type, Dim> operator+(const Point<Type, Dim>& other) const
            {
                Point<Type, Dim> result = *this;
                result += other;
                return result;
            }

            Point<Type, Dim> operator*(const Point<Type, Dim>& other) const
            {
                Point<Type, Dim> result = *this;
                result *= other;
                return result;
            }

            Point<Type, Dim> operator*(const Type scalar) const
            {
                Point<Type, Dim> result = *this;
                result *= scalar;
                return result;
            }

            Point<Type, Dim> operator-(const Point<Type, Dim>& other) const
            {
                Point<Type, Dim> result = *this;
                result -= other;
                return result;
            }

            Point<Type, Dim> operator-() const { return Point<Type, Dim> { -x(), -y(), -z() }; }


            float length() const {
                return std::sqrt(std::inner_product(values.begin(), values.end(), values.begin(), float { 0 }));
                // return std::sqrt(x() * x() + y() * y() + z() * z());
            }

            float distance_to(const Point<Type, Dim>& other) const { return (*this - other).length(); }

            Point<Type, Dim>& normalize(const float target_len = 1.0f)
            {
                const float current_len = length();
                if (current_len == 0)
                {
                    throw std::logic_error("cannot normalize vector of length 0");
                }

                *this *= (target_len / current_len);
                return *this;
            }

            Point<Type, Dim>& cap_length(const float max_len)
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

/*struct Point2D
{
    float values[2] {};

    Point2D() {}
    Point2D(float x, float y) : values { x, y } {}

    float& x() { return values[0]; }
    float x() const { return values[0]; }

    float& y() { return values[1]; }
    float y() const { return values[1]; }

    Point2D& operator+=(const Point2D& other)
    {
        x() += other.x();
        y() += other.y();
        return *this;
    }

    Point2D& operator*=(const Point2D& other)
    {
        x() *= other.x();
        y() *= other.y();
        return *this;
    }

    Point2D& operator*=(const float scalar)
    {
        x() *= scalar;
        y() *= scalar;
        return *this;
    }

    Point2D operator+(const Point2D& other) const
    {
        Point2D result = *this;
        result += other;
        return result;
    }

    Point2D operator*(const Point2D& other) const
    {
        Point2D result = *this;
        result *= other;
        return result;
    }

    Point2D operator*(const float scalar) const
    {
        Point2D result = *this;
        result *= scalar;
        return result;
    }
};*/

/*struct Point3D
{
    std::array<float, 3> values;

    Point3D() {}
    Point3D(float x, float y, float z) : values { x, y, z } {}

    float& x() { return values[0]; }
    float x() const { return values[0]; }

    float& y() { return values[1]; }
    float y() const { return values[1]; }

    float& z() { return values[2]; }
    float z() const { return values[2]; }

    Point3D& operator+=(const Point3D& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       std::plus<float> {});
        x() += other.x();
        y() += other.y();
        z() += other.z();
        return *this;
    }

    Point3D& operator-=(const Point3D& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       std::minus<float> {});
        return *this;
    }

    Point3D& operator*=(const float scalar)
    {
        std::transform(values.begin(), values.end(), values.begin(), [scalar](float v) { return v * scalar; });
        return *this;
    }

    Point3D operator+(const Point3D& other) const
    {
        Point3D result = *this;
        result += other;
        return result;
    }

    Point3D operator-(const Point3D& other) const
    {
        Point3D result = *this;
        result -= other;
        return result;
    }

    Point3D operator*(const float scalar) const
    {
        Point3D result = *this;
        result *= scalar;
        return result;
    }

    Point3D operator-() const { return Point3D { -x(), -y(), -z() }; }

    float length() const {
        return std::sqrt(std::inner_product(values.begin(), values.end(), values.begin(), float { 0 }));
       // return std::sqrt(x() * x() + y() * y() + z() * z());
    }

    float distance_to(const Point3D& other) const { return (*this - other).length(); }

    Point3D& normalize(const float target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point3D& cap_length(const float max_len)
    {
        assert(max_len > 0);

        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }
};*/
using Point2D = Point<float, 2>;
using Point3D = Point<float, 3>;


// our 3D-coordinate system will be tied to the airport: the runway is parallel to the x-axis, the z-axis
// points towards the sky, and y is perpendicular to both thus,
// {1,0,0} --> {.5,.5}   {0,1,0} --> {-.5,.5}   {0,0,1} --> {0,1}
inline Point2D project_2D(const Point3D& p)
{
    return { .5f * p.x() - .5f * p.y(), .5f * p.x() + .5f * p.y() + p.z() };
}
