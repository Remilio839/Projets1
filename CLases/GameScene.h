#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(GameScene);

    void update(float dt);

private:
    Player* player;
    Enemy* enemy;

    std::vector<cocos2d::Sprite*> fireballs;

    void setupBackground();
    void setupPlayer();
    void setupEnemy();
    void setupInputListeners();
    void scheduleEnemyShooting();

    bool checkCollisionAt(cocos2d::Vec2 targetPosition, cocos2d::Sprite* fireball);

    void changeEnemySprite();

    int enemyState = 0;

    int score;
    cocos2d::Label* scoreLabel;
    void updateScore();

    cocos2d::Sprite* background;

    float elapsedTime;
    cocos2d::Label* timerLabel;
    void updateTimer(float dt);
};

#endif
