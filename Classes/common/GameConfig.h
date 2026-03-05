// Classes/common/GameConfig.h
#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__

#include "cocos2d.h"

// 命名空间，防止和引擎冲突
using namespace cocos2d;

// 花色类型 (对应你的需求)
enum CardSuitType {
    CST_NONE = -1,
    CST_CLUBS = 0,      
    CST_DIAMONDS = 1,   
    CST_HEARTS = 2,     
    CST_SPADES = 3,     
    CST_NUM_CARD_SUIT_TYPES
};


enum CardFaceType {
    CFT_NONE = -1,
    CFT_ACE = 1,    // A
    CFT_TWO, CFT_THREE, CFT_FOUR, CFT_FIVE,
    CFT_SIX, CFT_SEVEN, CFT_EIGHT, CFT_NINE, CFT_TEN,
    CFT_JACK, CFT_QUEEN, CFT_KING, // K = 13
    CFT_NUM_CARD_FACE_TYPES
};


static const cocos2d::Size DESIGN_RES_SIZE(1080, 2080);

#endif // __GAME_CONFIG_H__