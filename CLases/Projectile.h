#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "cocos2d.h"

class Projectile : public cocos2d::Node
{
public:
    static Projectile* create(const cocos2d::Vec2& velocity);
    virtual bool init(const cocos2d::Vec2& velocity);

    void update(float dt) override;

private:
    cocos2d::Sprite* projectileSprite;
    cocos2d::Vec2 velocity;
    float gravity;
};

#endif
