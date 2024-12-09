#include "Player.h"

USING_NS_CC;

Player* Player::create()
{
    Player* ret = new (std::nothrow) Player();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Player::init()
{
    if (!Node::init())
        return false;

    health = 1000;
    maxHealth = 1000;
    power = 0;
    maxPower = 100;

    sprite = Sprite::create("player.png");
    sprite->setScale(0.2f);
    this->addChild(sprite, 0);

    healthLabel = Label::createWithSystemFont("Health: 1000", "Arial", 24);
    healthLabel->setPosition(Vec2(0, sprite->getContentSize().height + 20));
    healthLabel->setColor(Color3B::WHITE);
    this->addChild(healthLabel, 1);

    return true;
}

void Player::setHealth(int value)
{
    health = value;
    if (health < 0)
        health = 0;

    healthLabel->setString("Health: " + std::to_string(health));

    if (health <= 0) {
        CCLOG("Player defeated!");
    }
}

void Player::startCharging()
{
    this->schedule([this](float delta) {
        power += delta * 50;
        if (power > maxPower) {
            power = maxPower;
        }
        CCLOG("Cargando poder: %f", power);
        }, 0.1f, "chargeKey");
}

void Player::releaseCharge()
{
    this->unschedule("chargeKey");
    CCLOG("Disparando con poder: %f", power);

    auto fireball = Sprite::create("fireball.png");
    if (!fireball) {
        CCLOG("Error: No se pudo cargar fireball.png");
        return;
    }
    fireball->setScale(0.05f);
    fireball->setPosition(this->getPosition());
    this->getParent()->addChild(fireball, 2);

    auto physicsBody = PhysicsBody::createCircle(fireball->getContentSize().width * 0.05f);
    float velocity = power * 10;
    physicsBody->setVelocity(Vec2(velocity, velocity * 0.5));
    physicsBody->setGravityEnable(true);
    physicsBody->setContactTestBitmask(true);
    fireball->setPhysicsBody(physicsBody);

    power = 0;
}

