#include "HelloWorldScene.h"
#include "GameScene.h" 

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("menu_background.jpeg");
    if (background) {
        background->setPosition(Vec2(
            origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));

        float scaleX = visibleSize.width / background->getContentSize().width;
        float scaleY = visibleSize.height / background->getContentSize().height;
        background->setScale(std::max(scaleX, scaleY));
        this->addChild(background, 0);
    }

    auto playLabel = Label::createWithTTF("Play Now", "fonts/Marker Felt.ttf", 48);
    playLabel->setColor(Color3B::WHITE);

    auto playButton = MenuItemLabel::create(
        playLabel,
        CC_CALLBACK_1(HelloWorld::menuPlayCallback, this)
    );

    playButton->setPosition(Vec2(
        visibleSize.width / 2,
        visibleSize.height / 2 - 50));

    auto menu = Menu::create(playButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void HelloWorld::menuPlayCallback(Ref* pSender)
{
    auto gameScene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, gameScene));
}
