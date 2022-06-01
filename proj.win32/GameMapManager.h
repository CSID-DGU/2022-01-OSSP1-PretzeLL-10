#ifndef __GAME_MAP_MANAGER_H__
#define __GAME_MAP_MANAGER_H__

#include <cocos2d.h>
#include "GameMap.h"

class GameMapManager
{
public:
    void loadGameMap();
private:
    //explicit GameMapManager(const b2Vec2& gravity);

    // Internal function - NOT safe if used with CallbackManager!
    // Used by GameMap::loadGameMap().
    GameMap* doLoadGameMap(const std::string& tmxMapFileName);

    cocos2d::Layer* _layer;
    //std::unique_ptr<WorldContactListener> _worldContactListener;
    //std::unique_ptr<b2World> _world;
    //std::unique_ptr<GameMap> _gameMap;
    //std::unique_ptr<Player> _player;

    int gameFloor;
    GameMap* _gamemap;
};

#endif