#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class Player : public cocos2d::Node
{
public:
    static Player* create();
    virtual bool init();

    void setHealth(int value);
    void startCharging();
    void releaseCharge();

private:
    cocos2d::Sprite* sprite;
    cocos2d::Label* healthLabel;
    int health;
    int maxHealth;

    float power;
    float maxPower;
};

#endif
