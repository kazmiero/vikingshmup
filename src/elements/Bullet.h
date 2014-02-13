#ifndef BULLET_H
#define BULLET_H

#include "Element.h"
#include "models/BulletModel.h"

class Bullet : public Element
{
    public:
        Bullet(const AABB& aabb, const std::string& spriteName, float lifetime, Vector2f ori, float velocity);
        Bullet(const BulletModel& model, Vector2f pos, Vector2f ori, float velocity);
        virtual ~Bullet();

        virtual void move();
        bool lives();

        void bounce(const Vector2f& normal, const Vector2f& tangent);
        //void setSpeed(Vector2f dp);
        //void setSpeed(float dx, float dy);
        //float getMaxVelocity() const;
    protected:
        Vector2f dp_;
//        float velocity_;        // pixels per second
//        float maxVelocity_;     // pixels per second

        Uint32 lifetime_;       // in frame number
    private:
        /// circular collision model
        void initCollisionModel();
};

#endif // BULLET_H
