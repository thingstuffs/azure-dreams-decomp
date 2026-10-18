#include "common.h"
void func_800B4B7C(s32);                         /* extern */

/* Calls func_800B4B7C with the offset advanced by 0x20. */
void forward_offset_to_effect_finalizer(s32 offset) {
    func_800B4B7C(offset + 0x20);
}
