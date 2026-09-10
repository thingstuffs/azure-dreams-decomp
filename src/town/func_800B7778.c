#include "common.h"

extern s32 func_80049004();
extern s32 func_800491CC();
extern s32 func_8004B404();
extern s32 D_8002E5E8[];

/* Initializes object resources and defaults, returning whether the auxiliary allocation succeeds. */
s32 func_800B4ED8(void *object, s32 resource_id) {
    s32 *default_values;
    register s32 call_arg ASM_REG("$4");
    s32 resource_handle;
    s32 buffer;
    s32 success;

    success = 0;
    resource_handle = func_80049004((s8 *)object + 0x60, resource_id, 0xC);
    *(s32 *)((s8 *)object + 0x5C) = resource_handle;
    if (resource_handle != 0) {
        call_arg = resource_handle;
        do {
        } while (0);
        default_values = D_8002E5E8;
        *(s32 *)((s8 *)object + 0x40) = D_8002E5E8[0];
        *(s32 *)((s8 *)object + 0x44) = default_values[1];
        *(s32 *)((s8 *)object + 0x48) = default_values[2];
        func_800491CC(call_arg, (s8 *)object + 0x40, 0x29);
        buffer = func_8004B404(0x48);
        success = buffer != 0;
        *(s32 *)((s8 *)object + 0x20) = buffer;
    }
    return success;
}
