#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, -200));
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Scene::init())
        return false;

    setupBackground();
    setupPlayer();
    setupEnemy();
    setupInputListeners();
    scheduleEnemyShooting();

    score = 10000;

    scoreLabel = Label::createWithSystemFont("Score: 10000", "Arial", 24);
    scoreLabel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 100, Director::getInstance()->getVisibleSize().height - 50));
    scoreLabel->setColor(Color3B::WHITE);
    this->addChild(scoreLabel, 1);

    timerLabel = Label::createWithSystemFont("Time: 0", "Arial", 24);
    timerLabel->setPosition(Vec2(100, Director::getInstance()->getVisibleSize().height - 50));
    timerLabel->setColor(Color3B::WHITE);
    this->addChild(timerLabel, 1);

    schedule([this](float dt) {
        changeEnemySprite();
        }, 30.0f, "enemySpriteChangeKey");

    schedule([this](float dt) {
        updateScore();
        }, 1.0f, "scoreUpdateKey");

    elapsedTime = 0.0f;

    schedule([this](float dt) {
        updateTimer(dt);
        }, 1.0f, "timerUpdateKey");

    return true;
}

void GameScene::setupBackground()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    background = Sprite::create("level1_background.jpeg");
    if (background) {
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        float scaleX = visibleSize.width / background->getContentSize().width;
        float scaleY = visibleSize.height / background->getContentSize().height;
        background->setScale(std::max(scaleX, scaleY));
        this->addChild(background, 0);
    }
}

void GameScene::setupPlayer()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    player = Player::create();
    player->setPosition(Vec2(100, visibleSize.height / 2 - 100));
    this->addChild(player, 1);
}

void GameScene::setupEnemy()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    enemy = Enemy::create();
    enemy->setPosition(Vec2(visibleSize.width - 100, visibleSize.height / 2 - 100));
    this->addChild(enemy, 1);
}

void GameScene::setupInputListeners()
{
    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        player->startCharging();
        return true;
        };

    listener->onTouchEnded = [this](Touch* touch, Event* event) {
        player->releaseCharge();
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::scheduleEnemyShooting()
{
    this->schedule([this](float delta) {
        if (player) {
            enemy->shootAtPlayer(player->getPosition());
        }
        }, 2.0f, "enemyShootKey");
}

void GameScene::changeEnemySprite()
{
    static int enemyState = 0;

    switch (enemyState) {
    case 0:
        enemy->getSprite()->setTexture("enemy2.png");
        background->setTexture("level2_background.jpg");
        break;
    case 1:
        enemy->getSprite()->setTexture("enemy3.png");
        background->setTexture("level3_background.jpg");
        break;
    default:
        enemy->getSprite()->setTexture("enemy.png");
        background->setTexture("level1_background.jpeg");
        enemyState = -1;
        break;
    }

    enemyState++;
}

bool GameScene::checkCollisionAt(Vec2 targetPosition, Sprite* fireball)
{
    Vec2 fireballPosition = fireball->getPosition();

    if (fireballPosition.distance(targetPosition) < 10) {
        return true;
    }

    return false;
}

void GameScene::updateScore()
{
    if (score > 0) {
        score -= rand() % 50 + 1;
    }

    scoreLabel->setString("Score: " + std::to_string(score));
}

void GameScene::updateTimer(float dt)
{
    elapsedTime += dt;
    int seconds = static_cast<int>(elapsedTime);

    timerLabel->setString("Time: " + std::to_string(seconds));
}

void GameScene::update(float dt)
{
    for (auto fireball : fireballs) {
        if (checkCollisionAt(enemy->getPosition(), fireball)) {
            CCLOG("¡Colisión detectada en la posición del enemigo!");
            fireball->removeFromParent();
        }
    }
}
