#include "common.h"
#include "town/scene/money.h"

extern s32 scene_price;

/* Returns the current value of scene_price. */
s32 get_stored_price(void) {
    return scene_price;
}
