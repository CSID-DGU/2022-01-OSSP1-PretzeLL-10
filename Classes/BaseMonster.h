#ifndef __BASE_MONSTER_H__
#define __BASE_MONSTER_H__

#include "DynamicObject.h"
#include "Bullet.h"


class BaseMonster : public DynamicObject {
protected:
    BaseMonster(std::string name, int hp = 0);          // Constructor, initialize variables
    virtual ~BaseMonster();                             // Destructor
    
public:
//    CREATE_FUNC(Monster);                          
    
    virtual bool init() override;                       // Initialize
    
    virtual void attack() override {}                   // Need update!
    virtual void onContact(b2Contact* contact) override;
};

#endif /* __MONSTER_H__ */
