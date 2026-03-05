#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "cocos2d.h"
#include "../controllers/GameController.h"

/**
 * 游戏场景
 * 主游戏场景，包含游戏控制器和视图
 */
class GameScene : public cocos2d::Scene
{
public:
    static GameScene* create();
    virtual bool init() override;

private:
    void createUI();
    void onUndoButtonClicked();

    GameController* _gameController; // 游戏控制器
};

#endif // GAME_SCENE_H