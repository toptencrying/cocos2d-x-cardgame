#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include "cocos2d.h"
#include "../models/GameModel.h"
#include "CardView.h"
#include <map>
#include <functional>

class GameView : public cocos2d::Layer {
public:
    CREATE_FUNC(GameView);
    virtual bool init();

    void setupUI(GameModel* model);
    void moveCard(int cardId, cocos2d::Vec2 targetPos, int zOrder);


    void refreshAll();
    void updateCardState(int cardId, const CardModel* model);

    void setOnCardClicked(std::function<void(int)> callback) { _onCardClicked = callback; }
    void setOnUndoClicked(std::function<void()> callback) { _onUndoClicked = callback; }

private:
    std::map<int, CardView*> _cardNodes;
    std::function<void(int)> _onCardClicked;
    std::function<void()> _onUndoClicked;
};

#endif