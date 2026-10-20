#include "common.h"

extern s32 D_800834B8;
extern s32 D_80097D2C;
extern void *D_800CFCC4;

/* True when the active object shares its 0x60 field with `other` and the global hook is the default. */
s32 check_active_transform_object(void *other) {
    s32 result;

    if (D_800CFCC4 != 0) {
        result = 0;
        if (*(s32 *)((u8 *)D_800CFCC4 + 0x60) ==
            *(s32 *)((u8 *)other + 0x60)) {
            result = D_800834B8 == (s32)&D_80097D2C;
        }
        return result;
    }
    return 0;
}

