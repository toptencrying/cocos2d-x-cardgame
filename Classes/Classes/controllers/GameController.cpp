#include "GameController.h"
#include "../commands/CardMoveCommand.h"
#include "../services/LevelLoader.h"
#include <cmath>

using namespace cocos2d;
using namespace std;

void GameController::init(cocos2d::Node* parentLayer) {
    _model = new GameModel();
    _undoManager = new UndoManager();
    _view = GameView::create();
    parentLayer->addChild(_view);

    _view->setOnCardClicked([this](int id) { this->onCardClicked(id); });
    _view->setOnUndoClicked([this]() { this->onUndoClicked(); });

    //加载 JSON 数据 
    LevelLoader::loadLevel(_model, 1);

    //遮挡关系
    calculateBlockers();

  
    for (auto card : _model->playfieldCards) {
        if (card->isLocked()) {
            card->isFaceUp = false; 
        }
    }

  
    _view->setupUI(_model);
}

void GameController::refreshBoardState() {
  
    calculateBlockers();

    //  刷新所有卡牌的显示
    for (auto& pair : _model->allCards) {
        
        auto card = pair.second;
        if (card->location == CardModel::PLAYFIELD) {
            bool oldState = card->isFaceUp;
            card->isFaceUp = !card->isLocked();
           
            if (oldState != card->isFaceUp) {
                _view->updateCardState(card->id, card.get());
            }
        }
    }
}

void GameController::calculateBlockers() {
    auto& cards = _model->playfieldCards;

    
    for (auto c : cards) c->blockers.clear();

   
    for (auto cardA : cards) {
        for (auto cardB : cards) {
            if (cardA == cardB) continue;

           
            float yDiff = cardA->initialPos.y - cardB->initialPos.y;

            // 条件2：水平距离
            float xDist = std::abs(cardA->initialPos.x - cardB->initialPos.x);

           
            if (yDiff > 0 && yDiff < 150 && xDist < 120) {

               

                cardA->blockers.push_back(cardB->id);

        
            }
        }
    }
}



void GameController::onCardClicked(int cardId) {
    CardModel* clickedCard = _model->getCardById(cardId);
    CardModel* topHandCard = _model->getTopHandCard();

    if (!clickedCard || !topHandCard) return;

    if (clickedCard->location == CardModel::PLAYFIELD && clickedCard->isLocked()) {
        CCLOG("Card is blocked!");
        return;
    }

    bool canMove = false;

 
    if (clickedCard->location == CardModel::STACK) {
        // 只能点最后一张
        if (!_model->stackCards.empty() && clickedCard == _model->stackCards.back()) {
            canMove = true;
        }
    }
  
    else if (clickedCard->location == CardModel::PLAYFIELD) {
        if (isMatch(clickedCard->face, topHandCard->face)) canMove = true;
    }

    if (canMove) {
      
        auto moveCallback = [this](int id, Vec2 target, int z) {
            // 移动
            _view->moveCard(id, target, z);

          
            CardModel* c = _model->getCardById(id);
            _view->updateCardState(id, c);
        };

        Vec2 targetPos = Vec2(1040, 200);

        auto cmd = make_shared<CardMoveCommand>(_model, cardId, targetPos, moveCallback);
        _undoManager->executeCommand(cmd);

        refreshBoardState();
    }
}

void GameController::onUndoClicked() {
    if (_undoManager->canUndo()) {
        _undoManager->undo();
    
        refreshBoardState();
    }
}

bool GameController::isMatch(int face1, int face2) {
    int diff = abs(face1 - face2);
    return (diff == 1) || (diff == 12);
}