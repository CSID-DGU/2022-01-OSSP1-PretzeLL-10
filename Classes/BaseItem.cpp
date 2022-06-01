#include "BaseItem.h"


BaseItem::BaseItem(std::string name)
: StaticObject("frames", name)
, duration_time(0.0f)
{}

BaseItem::~BaseItem() {}


bool BaseItem::init() {
    IF(!StaticObject::init());
    setCategory(CATEGORY_ITEM, MASK_ITEM);
    return true;
}
