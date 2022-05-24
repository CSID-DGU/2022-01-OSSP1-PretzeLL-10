#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include <cocos2d.h>

using cocos2d::TMXTiledMap;

class GameMap
{
public:
    GameMap(const std::string& tmxMapFileName);
    GameMap();      // for test
    virtual ~GameMap() = default;

    void createObjects();
    void deleteObjects();
    //std::unique_ptr<Player> createPlayer() const;
    //Item* createItem(const std::string & itemJson, float x, float y, int amount = 1);


    //template <typename ReturnType = DynamicActor>
    //ReturnType* showDynamicActor(std::shared_ptr<DynamicActor> actor, float x, float y);

    //template <typename ReturnType = DynamicActor>
    //std::shared_ptr<ReturnType> removeDynamicActor(DynamicActor * actor);

    cocos2d::TMXTiledMap* getTmxTiledMap();
    cocos2d::TMXTiledMap* getTmxTiledMap() const;
    const std::string& getTmxTiledMapFileName() const;

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