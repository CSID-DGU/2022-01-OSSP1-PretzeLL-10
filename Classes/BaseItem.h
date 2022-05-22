#ifndef __BASE_ITEM_H__
#define __BASE_ITEM_H__

#include "StaticObject.h"


class BaseItem : public StaticObject {
protected:
    float duration_time;
    
protected:
    BaseItem(std::string name);
    virtual ~BaseItem();
    
public:
//    CREATE_FUNC(BaseItem);
    
    virtual bool init() override;
};

#endif /* __BASE_ITEM_H__ */
