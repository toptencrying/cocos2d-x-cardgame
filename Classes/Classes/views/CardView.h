#ifndef __CARD_VIEW_H__
#define __CARD_VIEW_H__

#include "cocos2d.h"
#include "../models/CardModel.h"
#include <string>

class CardView : public cocos2d::Node {
public:
    static CardView* create(const CardModel* model);
    virtual bool init(const CardModel* model);

    // Ë¢ÐÂÏÔÊ¾×´Ì¬
    void refreshView(const CardModel* model);


    void runFlipAnimation(bool toFaceUp);

    int getCardId() const { return _cardId; }

private:
    int _cardId;
    cocos2d::Sprite* _bgSprite;


    cocos2d::Node* _faceContent;   
    cocos2d::Sprite* _backSprite; 

    std::string getRankString(CardFaceType face);
    std::string getColorString(CardSuitType suit);
    std::string getSuitFilename(CardSuitType suit);
};

#endif