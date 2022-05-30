#ifndef __BASE_MONSTER_H__
#define __BASE_MONSTER_H__

#include "DynamicObject.h"
#include "BaseBullet.h"


class BaseMonster : public DynamicObject {
protected:
    BaseMonster(std::string name);                      // Constructor, initialize variables
    virtual ~BaseMonster();                             // Destructor
    
public:
//    CREATE_FUNC(Monster);                          
    
    virtual bool init() override;                       // Initialize
    
    virtual void attack() {}                            // Need update!
    virtual void damaged(int damage) override;
    
    virtual void onContact(b2Contact* contact) override;
};

typedef BaseMonster monster_t;

#endif /* __MONSTER_H__ */
