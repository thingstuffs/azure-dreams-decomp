#include "common.h"

extern void func_8009F2A0(void *arg0);
extern void *D_800CFCC4[];

/* get_target_itemp: Prepares the target item and returns its item data pointer, or zero. */
s32 get_target_itemp(void) {
    register u8 *target_object ASM_REG("$4") = (u8 *)D_800CFCC4[0];   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    if (target_object != 0) {
        s32 item_type = 4;

        if (target_object[0x14] == item_type) {
            func_8009F2A0(target_object);
            return (s32)(target_object + 0x4C);
        }
        return 0;
    }
    return 0;
}
