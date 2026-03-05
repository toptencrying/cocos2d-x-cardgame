#pragma once
#ifndef __LEVEL_LOADER_H__
#define __LEVEL_LOADER_H__

#include "../models/GameModel.h"
#include <string>

class LevelLoader {
public:
   
    static void loadLevel(GameModel* model, int levelId);

private:
   
    static void createCard(GameModel* model, const std::string& type,
        int face, int suit, float x, float y, int z);
};

#endif