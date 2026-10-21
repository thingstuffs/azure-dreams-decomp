#include "common.h"

extern s32 scene_price;

/* Return the value of D_8001B210. */
s32 get_stored_price(void) {
    return scene_price;
}
