#ifndef __GAME_MAP_MANAGER_H__
#define __GAME_MAP_MANAGER_H__

#include <cocos2d.h>
#include <utility>
#include "GameMap.h"
#include "Hero.h"

class GameMapManager
{
public:
    static GameMapManager* getInstance();
    void init();

    cocos2d::Layer* getLayer() const;

    void startNewGame();
    
    void clearLayer();
    void removeAllGameMap();
    void loadGameMap(int w, int h);

    void loadUpMap();
    void loadDownMap();
    void loadRightMap();
    void loadLeftMap();

    void update(float dt);
private:
    GameMapManager();
    void goNextStage();
    static GameMapManager* sharedGameMapManager;
    TMXTiledMap* doLoadGameMap(int w, int h);

    void createMonster();
    void makeGameMap();
    void deleteGameMap();

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); // copy & paste for test. by TACS
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); // copy & paste for test. by TACS

    cocos2d::Layer* _layer;
    GameMap*** _gameMap;  // Must make data structure form;
    std::pair<int, int> currentPosition;

    Hero* __player;
    b2World* __world;
    std::array<bool, 5> __key;
    //SlotMachine* __slot_layer;

    int gameStage;
    int mapWidth, mapHeight;
};

#endif