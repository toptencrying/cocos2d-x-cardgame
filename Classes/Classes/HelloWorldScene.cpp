#include "HelloWorldScene.h"
#include "controllers/GameController.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if (!Scene::init()) return false;

    // 绿色背景
    auto bg = LayerColor::create(Color4B(30, 80, 30, 255));
    this->addChild(bg);

    // 启动控制器
    auto controller = new GameController();
    controller->init(this); // 传入 Scene 节点

    return true;
}