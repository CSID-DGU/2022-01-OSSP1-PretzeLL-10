#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <cocos2d.h>
#include <utility>
#include "GameMap.h"
#include "Hero.h"

class GameManager
{
public:
    static GameManager* getInstance();
    void init();

    cocos2d::Layer* getLayer() const;
    Hero* getHero() const;      // for test

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
    GameManager();
    void goNextStage();
    static GameManager* sharedGameMapManager;
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

    int gameStage;
    int mapWidth, mapHeight;
};

#endif