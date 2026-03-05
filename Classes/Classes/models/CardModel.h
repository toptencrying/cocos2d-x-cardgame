#ifndef __CARD_MODEL_H__
#define __CARD_MODEL_H__

#include "../common/GameConfig.h"
#include <vector>

class CardModel {
public:
    enum Location { STACK, PLAYFIELD, HAND };

    int id;
    CardFaceType face;
    CardSuitType suit;
    Location location;
    Vec2 initialPos;
    bool isFaceUp;

    // ÕÚµ²
    std::vector<int> blockers; 
    bool isLocked() const { return !blockers.empty(); }

    CardModel(int _id, CardFaceType _face, CardSuitType _suit)
        : id(_id), face(_face), suit(_suit), location(STACK), isFaceUp(false)
    {
    }
};

#endif