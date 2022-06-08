#include "GameMap.h"

GameMap::GameMap(const std::string& tmxMapFileName)
    : _tmxTiledMap(cocos2d::TMXTiledMap::create(tmxMapFileName)), _tmxTiledMapFileName(tmxMapFileName), isClear(false), isBoss(false)
{
    _tmxTiledMap->retain();
}

GameMap::GameMap(const std::string& tmxMapFileName, bool boss)
    : _tmxTiledMap(cocos2d::TMXTiledMap::create(tmxMapFileName)), _tmxTiledMapFileName(tmxMapFileName), isClear(false), isBoss(boss)
{
    _tmxTiledMap->retain();
}

GameMap::GameMap(const std::string& tmxMapFileName, bool start, bool boss)
    : _tmxTiledMap(cocos2d::TMXTiledMap::create(tmxMapFileName)), _tmxTiledMapFileName(tmxMapFileName), isClear(start), isBoss(boss)
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

bool GameMap::getIsBossRoom()
{
    return isBoss;
}