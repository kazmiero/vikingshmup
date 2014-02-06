#ifndef VECTOR2F_H
#define VECTOR2F_H
#include <SDL2/SDL.h>


class Vector2f
{
    public:
        Vector2f();
        Vector2f(float x, float y);
        Vector2f(int x, int y);
        virtual ~Vector2f();

        float dotProduct(const Vector2f& other);
        float norm();
        float sqNorm();
        void normalize();

        float x_, y_;

        // operators
        Vector2f& operator+=(const Vector2f& other);
        Vector2f& operator-=(const Vector2f& other);
        Vector2f& operator*=(float lambda);
        Vector2f& operator/=(float lambda);

        // conversion
        SDL_Point toSDL_Point() const;
};

// operators
Vector2f operator+(const Vector2f& first, const Vector2f& second);
Vector2f operator-(const Vector2f& first, const Vector2f& second);
Vector2f operator*(const Vector2f& vec, float lambda);
Vector2f operator/(const Vector2f& vec, float lambda);
#endif // VECTOR2F_H
