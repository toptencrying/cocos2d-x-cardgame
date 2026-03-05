#include "CardView.h"

using namespace cocos2d;
using namespace std;

CardView* CardView::create(const CardModel* model) {
    CardView* pRet = new(std::nothrow) CardView();
    if (pRet && pRet->init(model)) {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    return nullptr;
}

bool CardView::init(const CardModel* model) {
    if (!Node::init()) return false;

    _cardId = model->id;


    _bgSprite = Sprite::create("res/card_general.png");
    if (!_bgSprite) {
      
        auto colorLayer = LayerColor::create(Color4B::RED, 200, 300);
        this->addChild(colorLayer);
        CCLOG("Error: card_general.png not found!");
        return true;
    }
    this->addChild(_bgSprite);

    Size size = _bgSprite->getContentSize();
    this->setContentSize(size);
    _bgSprite->setPosition(size.width / 2, size.height / 2);


    _faceContent = Node::create();
    _faceContent->setPosition(size.width / 2, size.height / 2);
    _bgSprite->addChild(_faceContent);


    _backSprite = Sprite::create("res/card_back.png");
    if (_backSprite) {
        _backSprite->setPosition(size.width / 2, size.height / 2);
        _bgSprite->addChild(_backSprite);
    }


    // 构建数字和花色

    string colorStr = getColorString(model->suit);
    string rankStr = getRankString(model->face);
    string suitFile = getSuitFilename(model->suit);


    // 小数字
    string smallNumName = StringUtils::format("res/number/small_%s_%s.png", colorStr.c_str(), rankStr.c_str());
    auto smallNum = Sprite::create(smallNumName);
    if (smallNum) {
        smallNum->setAnchorPoint(Vec2(0.5, 1.0));
        smallNum->setPosition(Vec2(-size.width * 0.35f, size.height * 0.42f));
        _faceContent->addChild(smallNum);
    }

    // 小花色
    auto smallSuit = Sprite::create(suitFile);
    if (smallSuit) {
        smallSuit->setAnchorPoint(Vec2(0.5, 1.0));
        smallSuit->setPosition(Vec2(-size.width * 0.35f, size.height * 0.22f));
        smallSuit->setScale(0.5f);
        _faceContent->addChild(smallSuit);
    }

    // 大数字
    string bigNumName = StringUtils::format("res/number/big_%s_%s.png", colorStr.c_str(), rankStr.c_str());
    auto bigNum = Sprite::create(bigNumName);
    if (bigNum) {
        bigNum->setPosition(Vec2(0, 0));
        _faceContent->addChild(bigNum);
    }


    refreshView(model);

    return true;
}

void CardView::refreshView(const CardModel* model) {
    if (model->isFaceUp) {
        if (_backSprite) _backSprite->setVisible(false); 
        if (_faceContent) _faceContent->setVisible(true); 
    }
    else {
        if (_backSprite) _backSprite->setVisible(true); 
        if (_faceContent) _faceContent->setVisible(false); 
    }
}

// 翻牌动画
void CardView::runFlipAnimation(bool toFaceUp) {
    this->stopAllActions();
    auto scaleDown = ScaleTo::create(0.1f, 0.0f, 1.0f);
    auto changeTexture = CallFunc::create([this, toFaceUp]() {
        if (toFaceUp) {
            if (_backSprite) _backSprite->setVisible(false);
            if (_faceContent) _faceContent->setVisible(true);
        }
        else {
            if (_backSprite) _backSprite->setVisible(true);
            if (_faceContent) _faceContent->setVisible(false);
        }
        });
    auto scaleUp = ScaleTo::create(0.1f, 1.0f, 1.0f);
    this->runAction(Sequence::create(scaleDown, changeTexture, scaleUp, nullptr));
}

string CardView::getColorString(CardSuitType suit) {
    return (suit == CST_DIAMONDS || suit == CST_HEARTS) ? "red" : "black";
}

string CardView::getRankString(CardFaceType face) {
    switch (face) {
    case CFT_ACE: return "A";
    case CFT_JACK: return "J";
    case CFT_QUEEN: return "Q";
    case CFT_KING: return "K";
    default: return StringUtils::format("%d", (int)face);
    }
}

string CardView::getSuitFilename(CardSuitType suit) {
    string name = "";
    switch (suit) {
    case CST_CLUBS: name = "club.png"; break;
    case CST_DIAMONDS: name = "diamond.png"; break;
    case CST_HEARTS: name = "heart.png"; break;
    case CST_SPADES: name = "spade.png"; break;
    default: return "";
    }
    return "res/suits/" + name;
}