#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "cocos2d.h"
#include "../models/GameModel.h"
#include "../views/GameView.h"
#include "../managers/UndoManager.h"

class GameController : public cocos2d::Ref {
public:
    void init(cocos2d::Node* parentLayer);
    void onCardClicked(int cardId);
    void onUndoClicked();

private:
    GameModel* _model;
    GameView* _view;
    UndoManager* _undoManager;

    bool isMatch(int face1, int face2);

  
    void refreshBoardState();
    void calculateBlockers();
};

#endif