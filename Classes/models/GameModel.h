#ifndef __GAME_MODEL_H__
#define __GAME_MODEL_H__

#include "CardModel.h"
#include <vector>
#include <map>
#include <memory>

using namespace std;

class GameModel {
public:
    //卡牌数据
    map<int, shared_ptr<CardModel>> allCards;

   
    vector<CardModel*> playfieldCards; // 桌面上的牌 
    vector<CardModel*> stackCards;     // 备用牌堆
    vector<CardModel*> handPile;       // 手牌区 

    
    GameModel() {}


    CardModel* getCardById(int id) {
        if (allCards.find(id) != allCards.end()) {
            return allCards[id].get();
        }
        return nullptr;
    }

    
    CardModel* getTopHandCard() {
        if (handPile.empty()) return nullptr;
        return handPile.back();
    }
};

#endif