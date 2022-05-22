#ifndef __GAME_MAP_MANAGER_H__
#define __GAME_MAP_MANAGER_H__

#include <cocos2d.h>
#include <utility>
#include "GameMap.h"

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
private:
    GameMapManager();
    void goNextStage();
    static GameMapManager* sharedGameMapManager;
    TMXTiledMap* doLoadGameMap(int w, int h);
    

    void createMonster();
    void makeGameMap();
    void deleteGameMap();



    cocos2d::Layer* _layer;
    GameMap*** _gameMap;  // Must make data structure form;
    std::pair<int, int> currentPosition;

    int gameStage;
    int mapWidth, mapHeight;
};

#endif