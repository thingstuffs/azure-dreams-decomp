#include "common.h"

extern s32 func_8009F77C(s32, s32);
extern s32 func_8009F830();

/* serch_item_plown: Check both player item searches for the requested kind and type. */
s32 func_8009F88C(s32 item_kind, s32 item_type) {
    s32 found;

    found = 0;
    if (func_8009F77C(item_kind, item_type) != 0) {
        found = 1;
    } else if (func_8009F830(item_kind, item_type) != 0) {
        found = 1;
    }
    return found;
}
