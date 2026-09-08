#include "common.h"

extern s32 func_80049004(s32 *a0, s32 a1, s32 a2);
extern s32 func_800491CC(s32 a0, void *a1, s32 a2);
extern s32 D_8002E5E8[];

/* Initializes the object handle and applies the default configuration on success. */
s32 func_800AEF5C(void *object, s32 resource_id) {
    s32 success = 0;
    s32 handle = func_80049004((s32 *)((s8 *)object + 0xDC), resource_id, 8);

    *(s32 *)((s8 *)object + 0xD8) = handle;
    if (handle != 0) {
        *(s32 *)((s8 *)object + 0xBC) = D_8002E5E8[0];
        *(s32 *)((s8 *)object + 0xC0) = D_8002E5E8[1];
        *(s32 *)((s8 *)object + 0xC4) = D_8002E5E8[2];
        func_800491CC(handle, (s8 *)object + 0xBC, 0x1A);
        success = 1;
    }
    return success;
}
