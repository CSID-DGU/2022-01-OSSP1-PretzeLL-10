#ifndef __FLASK_BLUE_H__
#define __FLASK_BLUE_H__

#include "BaseItem.h"


class FlaskBlue : public BaseItem {
protected:
    FlaskBlue() : BaseItem("flask_blue") {}
    virtual ~FlaskBlue() {}
    
public:
    CREATE_FUNC(FlaskBlue);
};

#endif /* __FLASK_BLUE_H__ */
