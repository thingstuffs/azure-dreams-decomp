#include "common.h"
#include "m2c_compat.h"
#include "town/scene/money.h"
#include "town/scene/primary_price_data.h"

s32 get_primary_price(void) {
    return town_primary_price;
}
