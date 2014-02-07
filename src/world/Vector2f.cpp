#include "Vector2f.h"
#include <cmath>

#define PI 3.14159265

Vector2f::Vector2f() :
    x_(0.0f),
    y_(0.0f)
{
}

Vector2f::Vector2f(float x, float y) :
    x_(x),
    y_(y)
{
}

Vector2f::Vector2f(int x,int y)
{
    x_ = float(x);
    y_ = float(y);
}

Vector2f::Vector2f(double x,double y)
{
    x_ = float(x);
    y_ = float(y);
}

Vector2f::~Vector2f()
{
    //dtor
}

float Vector2f::dotProduct(const Vector2f& other)
{
    return x_*other.x_ + y_*other.y_;
}

float Vector2f::sqNorm()
{
    return dotProduct(*this);
}

float Vector2f::norm()
{
    return sqrt(sqNorm());
}

void Vector2f::normalize()
{
    if (sqNorm() > 0)
    {
        *this /= norm();
    }
}

SDL_Point Vector2f::toSDL_Point() const
{
    SDL_Point point;
    point.x = (int) x_;
    point.y = (int) y_;
    return point;
}

Vector2f& Vector2f::operator+=(const Vector2f& other)
{
    x_ += other.x_;
    y_ += other.y_;
    return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& other)
{
    x_ -= other.x_;
    y_ -= other.y_;
    return *this;
}

Vector2f& Vector2f::operator*=(float lambda)
{
    x_ *= lambda;
    y_ *= lambda;
    return *this;
}

Vector2f& Vector2f::operator/=(float lambda)
{
    x_ /= lambda;
    y_ /= lambda;
    return *this;
}

Vector2f operator+(const Vector2f& first, const Vector2f& second)
{
    Vector2f sum(first);
    sum.x_ += second.x_;
    sum.y_ += second.y_;
    return sum;
}

Vector2f operator-(const Vector2f& first, const Vector2f& second)
{
    Vector2f diff(first);
    diff.x_ -= second.x_;
    diff.y_ -= second.y_;
    return diff;
}

Vector2f operator*(const Vector2f& vec, float lambda)
{
    Vector2f prod(vec);
    prod.x_ *= lambda;
    prod.y_ *= lambda;
    return prod;
}

Vector2f operator/(const Vector2f& vec, float lambda)
{
    Vector2f quo(vec);
    quo.x_ /= lambda;
    quo.y_ /= lambda;
    return quo;
}

Vector2f Vector2f::getOrientationByAngle(double angle)
{
    return Vector2f(sin(angle*PI/180.0), -cos(angle*PI/180.0));
}
