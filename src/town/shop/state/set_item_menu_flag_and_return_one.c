#include "common.h"
#include "town/shop/state.h"

/* Writes one through the signed-byte flag pointer and returns one. */
s32 set_item_menu_flag_and_return_one(void *state, s32 unused_config) {
    s8 *flag;

    flag = state;
    *flag = 1;
    return 1;
}
