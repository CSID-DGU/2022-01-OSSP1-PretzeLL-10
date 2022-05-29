#ifndef __BASE_BULLET_H__
#define __BASE_BULLET_H__

#include "ProjectileObject.h"


class BaseBullet : public ProjectileObject {
protected:
    int __damage;
    
protected:
    BaseBullet(std::string name, int damage);
    virtual ~BaseBullet();
    
public:
//    CREATE_FUNC(BaseBullet);
    
    virtual bool init() override;
    
    virtual void onContact(b2Contact* contact) override;
};

#endif /* __BASE_BULLET_H__ */
