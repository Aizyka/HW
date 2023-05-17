#include "tmath.h"

int Math::abs(int x)
{
    if (x < 0)
    {
        return -x;
    }
    else
    {
        return x;
    }
}
double Math::sqrt(double x)
{
    double result      = x / 2;
    double prev_result = 0;
    while (result != prev_result)
    {
        prev_result = result;
        result      = (x / result + result) / 2;
    }
    return result;
}

double Math::exp(double x)
{
    double result = 1;
    double term   = 1;
    for (int i = 1; i <= 50; i++)
    {
        term *= x / i;
        result += term;
    }
    return result;
}

double Math::log(double x)
{
    double result = 0;
    double term   = (x - 1) / x;
    for (int i = 1; i <= 100; i += 2)
    {
        result += term;
        term *= (x - 1) * (x - 1) / (x * x);
    }
    return 2 * result;
}

double Math::sin(double x)
{
    double result = x;
    double term   = x;
    for (int i = 1; i <= 100; i++)
    {
        term *= -x * x / (2 * i) / (2 * i + 1);
        result += term;
    }
    return result;
}

double Math::cos(double x)
{
    double result = 1;
    double term   = 1;
    for (int i = 1; i <= 100; i++)
    {
        term *= -x * x / (2 * i - 1) / (2 * i);
        result += term;
    }
    return result;
}

double Math::tan(double x)
{
    return sin(x) / cos(x);
}
double Math::ctan(double x)
{
    return cos(x) / sin(x);
}

Vector3 Vector3::operator+(const Vector3& v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator*(const Vector3& v) const
{
    return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3 Vector3::operator/(const Vector3& v) const
{
    return Vector3(x / v.x, y / v.y, z / v.z);
}

// Operator overloads for float arithmetic
Vector3 Vector3::operator+(float f) const
{
    return Vector3(x + f, y + f, z + f);
}

Vector3 Vector3::operator-(float f) const
{
    return Vector3(x - f, y - f, z - f);
}

Vector3 Vector3::operator*(float f) const
{
    return Vector3(x * f, y * f, z * f);
}

Vector3 Vector3::operator/(float f) const
{
    return Vector3(x / f, y / f, z / f);
}

Vector3& Vector3::operator=(const Vector3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

bool Vector3::operator==(const Vector3& v)
{
    return (x == v.x && v.y == y && v.z == z);
}

bool Vector3::operator!=(const Vector3& v)
{
    return (x != v.x || v.y != y || v.z != z);
}

Vector3 Vector3::normalize(Vector3 vector)
{
    float length = Math::sqrt(vector.x * vector.x + vector.y * vector.y +
                              vector.z * vector.z);
    return Vector3(vector.x / length, vector.y / length, vector.z / length);
}

Vector3 Vector3::normalize()
{
    float length = Math::sqrt(x * x + y * y + z * z);
    x /= length;
    y /= length;
    z /= length;
    *this;
}

Vector3 Vector3::cross(const Vector3& a, const Vector3& b)
{
    float x = a.y * b.z - a.z * b.y;
    float y = a.z * b.x - a.x * b.z;
    float z = a.x * b.y - a.y * b.x;
    return { x, y, z };
}

Color Color::red()
{
    return Color(1.0f, 0.0f, 0.0f);
}
Color Color::green()
{
    return Color(0.0f, 1.0f, 0.0f);
}
Color Color::blue()
{
    return Color(0.0f, 0.0f, 1.0f);
}
Color Color::white()
{
    return Color(1.0f, 1.0f, 1.0f);
}
Color Color::black()
{
    return Color(0.0f, 0.0f, 0.0f);
}
Color Color::pink()
{
    return Color(1.0f, 0.0f, 1.0f);
}
Color Color::yellow()
{
    return Color(1.0f, 1.0f, 0.0f);
}
Color Color::cyan()
{
    return Color(0.0f, 1.0f, 1.0f);
}