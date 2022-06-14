#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <cocos2d.h>
#include <utility>
#include "GameMap.h"
#include "GameStateLayer.h"
#include "BaseMonster.h"
#include "EventHandler.h"
#include "GameMapManager.h"
#include "MonsterManager.h"
#include "Timer.h"

struct GameOverInfo
{
    float run_time;
    bool all_clear;
    int stage;
    int slot_run;
    int gold_earn;
    int damage;

    GameOverInfo();
    void clear();
};

class GameManager
{
public:
    static GameManager* getInstance();
    void init();

    cocos2d::Layer* getLayer() const;
    Hero* getHero() const;      // for test
    std::vector<BaseMonster*> monsterVec;

    std::string string_format(const std::string& format, int a, int b);

    void startNewGame();

    void deleteMonster(BaseMonster* dM);
    
    void clearLayer();
    void removeAllGameMap();
    void loadGameMap(int w, int h);

    void loadUpMap();
    void loadDownMap();
    void loadRightMap();
    void loadLeftMap();

    void update(float dt);

    void addMonsters2(BaseMonster* monster);

    void goNextStage(cocos2d::Ref* pSender); // must move to private
    
    void pauseGame();
    bool isPausedByUser;

    GameOverInfo runningInfo;
private:
    GameManager();
    
    static GameManager* sharedGameMapManager;
    TMXTiledMap* doLoadGameMap(int w, int h);

    void allocateGameMap();
    void makeGameMap();
    void deleteGameMap();
    void updateMapClear();
    void addStageUpLayer();

    void gameOver(bool allclear);
    void menuGotoSummarySceneCallback(cocos2d::Ref* pSender);
    void menuResumeGameCallback(cocos2d::Ref* pSender);

    cocos2d::Layer* _layer;
    GameStateLayer* _state_layer;
    GameMapManager mapManager;
    MonsterManager monsterManager;
    int numberMonster;

    GameMap*** _gameMap;  // Must make data structure form;
    std::pair<int, int> currentPosition;

    Hero* _hero;
    _Timer* __timer;

    bool isGameOver;

    int gameStage;
    int mapWidth, mapHeight;
};

#endif
