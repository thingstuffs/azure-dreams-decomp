#include "common.h"

extern void *D_800CFCC4[];

/* get_target_itemp: Prepares the target item and returns its item data pointer, or zero. */
s32 get_target_itemp(void) {
    u8 *target_object = (u8 *)D_800CFCC4[0];

    if (target_object != 0) {
        s32 item_type = 4;

        if (target_object[0x14] == item_type) {
            return (s32)(target_object + 0x4C);
        }
        return 0;
    }
    return 0;
}
