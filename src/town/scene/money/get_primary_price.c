#include "common.h"
#include "m2c_compat.h"
#include "town/scene/money.h"

extern s32 town_primary_price;
s32 get_primary_price(void) {
    return town_primary_price;
}
