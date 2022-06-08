#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include <cocos2d.h>
#include "Object.h"

using cocos2d::TMXTiledMap;

class GameMap
{
public:
    GameMap(const std::string& tmxMapFileName);
    GameMap(const std::string& tmxMapFileName, bool boss);
    GameMap(const std::string& tmxMapFileName, bool start, bool boss);
    GameMap();      // for test
    virtual ~GameMap() = default;

    cocos2d::TMXTiledMap* getTmxTiledMap();
    cocos2d::TMXTiledMap* getTmxTiledMap() const;
    const std::string& getTmxTiledMapFileName() const;

    void setClear();
    bool getIsClear();

    bool getIsBossRoom();
    
    b2Body* _wall = nullptr;

private:
    void createTriggers();
    void createPortals();
    void createNpcs();
    void createChests();

    TMXTiledMap* _tmxTiledMap;
    std::string _tmxTiledMapFileName;

    bool isClear;
    bool isBoss;
};

#endif
