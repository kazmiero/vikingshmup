#ifndef VECTOR2F_H
#define VECTOR2F_H
#include <SDL2/SDL.h>


class Vector2f
{
    public:
        Vector2f();
        Vector2f(float x, float y);
        Vector2f(int x, int y);
        Vector2f(double x, double y);
        virtual ~Vector2f();

        float dotProduct(const Vector2f& other);
        float norm();
        float sqNorm();
        void normalize();

        void bounce(const Vector2f& normal, const Vector2f& tangent);
        void applyRotation(const Vector2f& center, double angleDegrees);

        float x_, y_;

        // copy operators
        Vector2f& operator=(const Vector2f& other);

        // operators
        Vector2f& operator+=(const Vector2f& other);
        Vector2f& operator-=(const Vector2f& other);
        Vector2f& operator*=(float lambda);
        Vector2f& operator/=(float lambda);

        // conversion
        SDL_Point toSDL_Point() const;

        // statics
        static Vector2f getOrientationByAngle(double angle);
        static Vector2f getOrthogonalVector(const Vector2f& vec);
        static Vector2f getOrthogonalProjection(const Vector2f& point, const Vector2f& lineP1, const Vector2f& lineP2);
};

// operators
Vector2f operator+(const Vector2f& first, const Vector2f& second);
Vector2f operator-(const Vector2f& first, const Vector2f& second);
Vector2f operator*(const Vector2f& vec, float lambda);
Vector2f operator/(const Vector2f& vec, float lambda);


#endif // VECTOR2F_H
