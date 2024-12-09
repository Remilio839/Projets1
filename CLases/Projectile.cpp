#include "Projectile.h"

USING_NS_CC;

Projectile* Projectile::create(const Vec2& velocity) {
    Projectile* ret = new (std::nothrow) Projectile();
    if (ret && ret->init(velocity)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Projectile::init(const Vec2& initialVelocity) {
    if (!Node::init()) {
        return false;
    }

    velocity = initialVelocity;
    gravity = -200.0f;

    projectileSprite = Sprite::create("fireball.png");
    if (projectileSprite) {
        projectileSprite->setScale(0.03);
        this->addChild(projectileSprite);
    }

    scheduleUpdate();

    return true;
}

void Projectile::update(float dt) {
    velocity.y += gravity * dt;

    this->setPosition(this->getPosition() + velocity * dt);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    if (this->getPositionX() < 0 || this->getPositionX() > visibleSize.width ||
        this->getPositionY() < 0 || this->getPositionY() > visibleSize.height) {
        this->removeFromParent();
    }
}
