#ifndef __CARD_MOVE_COMMAND_H__
#define __CARD_MOVE_COMMAND_H__

#include "ICommand.h"
#include "../models/GameModel.h"
#include "cocos2d.h"
#include <functional>
#include <algorithm>

class CardMoveCommand : public ICommand {
public:
    typedef std::function<void(int, cocos2d::Vec2, int)> MoveCallback;

    CardMoveCommand(GameModel* model, int cardId, cocos2d::Vec2 targetPos, MoveCallback moveFunc)
        : _model(model), _cardId(cardId), _targetPos(targetPos), _moveFunc(moveFunc)
    {
    }

    void execute() override {
        CardModel* card = _model->getCardById(_cardId);
        if (!card) return;

        // 记录历史状态 
        _prevLocation = card->location;
        _prevPos = card->initialPos;
        _prevFaceUp = card->isFaceUp; // 记录它原本是背面还是正面

       
        removeFromList(card, _prevLocation);

        card->location = CardModel::HAND;

       
        card->isFaceUp = true;

        _model->handPile.push_back(card);

       
        card->initialPos = _targetPos;

   
        if (_moveFunc) _moveFunc(_cardId, _targetPos, 100);
    }

    void undo() override {
        CardModel* card = _model->getCardById(_cardId);
        if (!card) return;

      
        if (!_model->handPile.empty() && _model->handPile.back() == card) {
            _model->handPile.pop_back();
        }

        addToList(card, _prevLocation);
        card->location = _prevLocation;

        // --- 恢复之前的状态 (如果是从牌堆回来的，就变回背面) ---
        card->isFaceUp = _prevFaceUp;

        card->initialPos = _prevPos;

     
        if (_moveFunc) _moveFunc(_cardId, _prevPos, 0);
    }

private:
    GameModel* _model;
    int _cardId;
    cocos2d::Vec2 _targetPos;
    MoveCallback _moveFunc;

    // 历史状态
    CardModel::Location _prevLocation;
    cocos2d::Vec2 _prevPos;
    bool _prevFaceUp;

    void removeFromList(CardModel* card, CardModel::Location loc) {
        std::vector<CardModel*>* list = nullptr;
        if (loc == CardModel::Location::PLAYFIELD) list = &(_model->playfieldCards);
        else if (loc == CardModel::Location::STACK) list = &(_model->stackCards);

        if (list) {
            auto it = std::find(list->begin(), list->end(), card);
            if (it != list->end()) list->erase(it);
        }
    }

    void addToList(CardModel* card, CardModel::Location loc) {
        if (loc == CardModel::Location::PLAYFIELD) _model->playfieldCards.push_back(card);
        else if (loc == CardModel::Location::STACK) _model->stackCards.push_back(card);
    }
};

#endif