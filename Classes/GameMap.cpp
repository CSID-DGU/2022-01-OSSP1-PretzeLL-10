#include "GameMap.h"

GameMap::GameMap(const std::string& tmxMapFileName)
    : _tmxTiledMap(cocos2d::TMXTiledMap::create(tmxMapFileName)), _tmxTiledMapFileName(tmxMapFileName), isClear(false)
{
    _tmxTiledMap->retain();
}

TMXTiledMap* GameMap::getTmxTiledMap() {
    return _tmxTiledMap;
}

TMXTiledMap* GameMap::getTmxTiledMap() const
{
    return _tmxTiledMap;
}

void GameMap::setClear()
{
    isClear = true;
}

bool GameMap::getIsClear()
{
    return isClear;
}