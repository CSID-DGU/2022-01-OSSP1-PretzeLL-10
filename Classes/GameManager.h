#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <cocos2d.h>
#include <utility>
#include "GameMapManager.h"
#include "GameMap.h"
#include "Hero.h"
#include "GameStateLayer.h"

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

    GameMapManager mapManager;
    void goNextStage();
    static GameManager* sharedGameMapManager;
    TMXTiledMap* doLoadGameMap(int w, int h);

    void createMonster();
    void makeGameMap();
    void deleteGameMap();

    cocos2d::Layer* _layer;
    GameStateLayer* _state_layer;
    GameMap*** _gameMap;  // Must make data structure form;
    std::pair<int, int> currentPosition;

    Hero* _hero;

    int gameStage;
    int mapWidth, mapHeight;
};

#endif
