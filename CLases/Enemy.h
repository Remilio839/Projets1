#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class Enemy : public cocos2d::Node
{
public:
    static Enemy* create();
    virtual bool init();

    cocos2d::Sprite* getSprite() { return sprite; }

    void setHealth(int value);

    void shootAtPlayer(const cocos2d::Vec2& targetPosition);

private:
    cocos2d::Sprite* sprite;
    cocos2d::Label* healthLabel;
    int health;
    int maxHealth;
};

#endif
