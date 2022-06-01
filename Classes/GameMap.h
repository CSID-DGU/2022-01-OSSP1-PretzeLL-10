#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include <cocos2d.h>
#include "Object.h"

using cocos2d::TMXTiledMap;

class GameMap
{
public:
    GameMap(const std::string& tmxMapFileName);
    GameMap();      // for test
    virtual ~GameMap() = default;

    cocos2d::TMXTiledMap* getTmxTiledMap();
    cocos2d::TMXTiledMap* getTmxTiledMap() const;
    const std::string& getTmxTiledMapFileName() const;

    void setClear();
    bool getIsClear();
    
    b2Body* _wall = nullptr;

private:
    void createTriggers();
    void createPortals();
    void createNpcs();
    void createChests();

    TMXTiledMap* _tmxTiledMap;
    std::string _tmxTiledMapFileName;

    //std::unordered_set<std::shared_ptr<DynamicActor>> _dynamicActors;
    //std::vector<std::unique_ptr<GameMap::Trigger>> _triggers;
    //std::vector<std::unique_ptr<GameMap::Portal>> _portals;

    bool isClear;
    friend class GameManager;
};

#endif
