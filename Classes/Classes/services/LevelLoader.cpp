#include "LevelLoader.h"
#include "cocos2d.h"
#include "json/document.h" 

using namespace cocos2d;


void LevelLoader::loadLevel(GameModel* model, int levelId) {

    model->allCards.clear();
    model->playfieldCards.clear();
    model->stackCards.clear();
    model->handPile.clear();

    
    std::string filename = StringUtils::format("res/levels/level_%d.json", levelId);
    std::string content = FileUtils::getInstance()->getStringFromFile(filename);

    if (content.empty()) {
        CCLOG("Error: Level file not found: %s", filename.c_str());
        return;
    }

    
    rapidjson::Document doc;
    doc.Parse(content.c_str());
    if (doc.HasParseError()) { CCLOG("JSON Parse Error"); return; }

  
    if (doc.HasMember("Playfield")) {
        const rapidjson::Value& arr = doc["Playfield"]; 
        for (rapidjson::SizeType i = 0; i < arr.Size(); i++) {
            const rapidjson::Value& item = arr[i];
            createCard(model, "Playfield",
                item["CardFace"].GetInt(), item["CardSuit"].GetInt(),
                item["pos"]["x"].GetFloat(), item["pos"]["y"].GetFloat(),
                item.HasMember("z") ? item["z"].GetInt() : 0);
        }
    }


    if (doc.HasMember("Stack")) {
        const rapidjson::Value& arr = doc["Stack"];
        for (rapidjson::SizeType i = 0; i < arr.Size(); i++) {
            const rapidjson::Value& item = arr[i];

         

        
            float startX = 200.0f;
            float startY = 200.0f;

         
            float offset = 30.0f;

            
            float currentX = startX + (i * offset);

          
            createCard(model, "Stack",
                item["CardFace"].GetInt(), item["CardSuit"].GetInt(),
                currentX, startY, i);
        }
    }

    
    if (doc.HasMember("Hand")) {
        const rapidjson::Value& item = doc["Hand"];
        createCard(model, "Hand",
            item["CardFace"].GetInt(), item["CardSuit"].GetInt(),
            1040, 200, 100);
    }
}

void LevelLoader::createCard(GameModel* model, const std::string& type,
    int face, int suit, float x, float y, int z) {
    static int s_idGen = 100;
    auto card = std::make_shared<CardModel>(s_idGen++, (CardFaceType)face, (CardSuitType)suit);
    card->initialPos = Vec2(x, y);

    if (type == "Playfield") {
        card->location = CardModel::PLAYFIELD;
        card->isFaceUp = true;
        model->playfieldCards.push_back(card.get());
    }
    else if (type == "Stack") {
        card->location = CardModel::STACK;
        card->isFaceUp = false;
        model->stackCards.push_back(card.get());
    }
    else if (type == "Hand") {
        card->location = CardModel::HAND;
        card->isFaceUp = true;
        model->handPile.push_back(card.get());
    }
    model->allCards[card->id] = card;
}