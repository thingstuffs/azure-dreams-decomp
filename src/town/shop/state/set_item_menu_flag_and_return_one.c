#include "common.h"

/* Writes one through the signed-byte flag pointer and returns one. */
s32 set_item_menu_flag_and_return_one(s8 *flag) {
    *flag = 1;
    return 1;
}
