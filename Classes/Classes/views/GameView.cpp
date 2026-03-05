#include "GameView.h"

USING_NS_CC;

bool GameView::init() {
    if (!Layer::init()) return false;

    // 添加 Undo 按钮
    auto undoLabel = Label::createWithSystemFont("UNDO", "Arial", 60);
    auto undoItem = MenuItemLabel::create(undoLabel, [=](Ref*) {
        if (_onUndoClicked) _onUndoClicked();
        });
    auto menu = Menu::create(undoItem, nullptr);
    menu->setPosition(Vec2(1800, 150));
    this->addChild(menu, 1000);

    return true;
}

void GameView::setupUI(GameModel* model) {
    
    for (auto& pair : _cardNodes) {
        pair.second->removeFromParent();
    }
    _cardNodes.clear();

    for (auto& pair : model->allCards) {
        auto cardData = pair.second;
        auto cardView = CardView::create(cardData.get());

        if (cardView) {
            cardView->setPosition(cardData->initialPos);
            this->addChild(cardView);
            _cardNodes[cardData->id] = cardView;

            // 绑定点击
            auto listener = EventListenerTouchOneByOne::create();
            listener->setSwallowTouches(true);
            listener->onTouchBegan = [=](Touch* t, Event* e) {
                Vec2 local = cardView->convertToNodeSpace(t->getLocation());
                Size s = cardView->getContentSize();
                Rect r = Rect(0, 0, s.width, s.height);
                if (r.containsPoint(local)) {
                    if (_onCardClicked) _onCardClicked(cardData->id);
                    return true;
                }
                return false;
            };
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, cardView);
        }
    }
}

void GameView::moveCard(int cardId, cocos2d::Vec2 targetPos, int zOrder) {
    if (_cardNodes.find(cardId) == _cardNodes.end()) return;
    auto card = _cardNodes[cardId];
    card->setLocalZOrder(zOrder);
    card->stopAllActions();
    auto move = MoveTo::create(0.3f, targetPos);
    auto ease = EaseBackOut::create(move);
    card->runAction(ease);
}




void GameView::updateCardState(int cardId, const CardModel* model) {
    if (_cardNodes.find(cardId) != _cardNodes.end()) {
        _cardNodes[cardId]->refreshView(model);
    }
}