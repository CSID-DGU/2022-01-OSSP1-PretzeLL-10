#ifndef __BASE_BULLET_H__
#define __BASE_BULLET_H__

#include "ProjectileObject.h"


class BaseBullet : public ProjectileObject {
protected:
    BaseBullet(std::string name);
    virtual ~BaseBullet();
    
public:
//    CREATE_FUNC(BaseBullet);
    
    bool init() override;
};

#endif /* __BASE_BULLET_H__ */
