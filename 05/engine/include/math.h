#pragma once
#include <cstdint>
#include <iostream>
#include <istream>
#include <ostream>

class Math
{
public:
    static int    abs(int x);
    static double sqrt(double x);
    static double exp(double x);
    static double log(double x);
    static double sin(double x);
    static double cos(double x);
    static double tan(double x);
    static double ctan(double x);
};

class Vector3
{
public:
    float x;
    float y;
    float z;
    Vector3(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    {
    }
    Vector3() {}

    Vector3 operator+(const Vector3& v) const;

    Vector3 operator-(const Vector3& v) const;

    Vector3 operator*(const Vector3& v) const;

    Vector3 operator/(const Vector3& v) const;

    Vector3 operator+(float f) const;

    Vector3 operator-(float f) const;

    Vector3 operator*(float f) const;

    Vector3 operator/(float f) const;

    Vector3& operator=(const Vector3& v);

    friend std::ostream& operator<<(std::ostream& os, const Vector3& vector)
    {
        os << vector.x << " " << vector.y << " " << vector.z;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector3& vector)
    {
        is >> vector.x >> vector.y >> vector.z;
        return is;
    }

    bool operator==(const Vector3& v);

    bool operator!=(const Vector3& v);

    static Vector3 normalize(Vector3 vector);
    Vector3        normalize();

    static Vector3 cross(const Vector3& a, const Vector3& b);
};

class Color
{
public:
    float r;
    float g;
    float b;
    float a;

    Color(float r, float b, float g, float a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {
    }
    Color(float r, float b, float g)
        : r(r)
        , g(g)
        , b(b)
        , a(1.0f)
    {
    }
    Color() {}

    static Color red();
    static Color green();
    static Color blue();
    static Color white();
    static Color black();
    static Color pink();
    static Color yellow();
    static Color cyan();

    friend std::ostream& operator<<(std::ostream& os, const Color& color)
    {
        os << color.r << " " << color.g << " " << color.b << " " << color.a;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Color& color)
    {
        is >> color.r >> color.g >> color.b >> color.a;
        return is;
    }

    friend bool operator==(const Color& lhs, const Color& rhs)
    {
        return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b &&
               lhs.a == rhs.a;
    }

    friend bool operator!=(const Color& lhs, const Color& rhs)
    {
        return lhs.r != rhs.r || lhs.g != rhs.g || lhs.b != rhs.b ||
               lhs.a != rhs.a;
    }
};