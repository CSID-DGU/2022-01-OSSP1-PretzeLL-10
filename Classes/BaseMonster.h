#ifndef __BASE_MONSTER_H__
#define __BASE_MONSTER_H__

#include "DynamicObject.h"


class BaseMonster : public DynamicObject {
protected:
    BaseMonster(std::string name);                     // Constructor, initialize variables
    virtual ~BaseMonster();                            // Destructor
    
public:
//    CREATE_FUNC(Monster);                          
    
    virtual bool init() override;                  // Initialize
    
    virtual void attack() override {}            // Need update!
};

#endif /* __MONSTER_H__ */
