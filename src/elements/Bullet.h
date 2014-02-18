#ifndef BULLET_H
#define BULLET_H

#include "Element.h"
#include "Trajectory.h"
#include "models/BulletModel.h"

class Bullet : public Element
{
    public:
        Bullet(const AABB& aabb, const std::string& spriteName, float lifetime, Vector2f ori, float velocity);
        Bullet(const BulletModel& model, Vector2f pos, Vector2f ori, float velocity);
        Bullet(const BulletModel& model, Vector2f pos, const Trajectory& trajectory);
        virtual ~Bullet();

        virtual void initTrajectory();
        virtual void move();
        bool lives();

        void bounce(const Vector2f& normal, const Vector2f& tangent);
        void setTrajectory(const Trajectory& trajectory);
        //void setSpeed(Vector2f dp);
        //void setSpeed(float dx, float dy);
        //float getMaxVelocity() const;
    protected:
        Vector2f dp_;
//        float velocity_;        // pixels per second
//        float maxVelocity_;     // pixels per second

        Uint32 lifetime_;       // in frame number
        Trajectory* trajectory_;
    private:
        /// circular collision model
        void initCollisionModel();
};

#endif // BULLET_H
