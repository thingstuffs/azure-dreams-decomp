#include "common.h"
#include "m2c_compat.h"
#include "town/scene/money.h"

extern s32 town_secondary_price;
s32 get_secondary_price(void) {
    return town_secondary_price;
}
