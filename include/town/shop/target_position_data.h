#ifndef TOWN_SHOP_TARGET_POSITION_DATA_H
#define TOWN_SHOP_TARGET_POSITION_DATA_H

#include "shared/entity.h"

/* Target of the shop item motion, in signed 16.16 world coordinates. */
typedef struct ShopTargetPosition {
    Fixed1616 x;
    Fixed1616 y;
    Fixed1616 z;
} ShopTargetPosition;

extern ShopTargetPosition shop_target_position;
extern s32 shop_target_entry_index;

#endif
