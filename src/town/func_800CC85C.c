#include "common.h"

typedef struct {
    u8 pad0[0x6C];
    u16 timer;
    u16 value;
    u16 pad70;
    u16 output;
} TownObject;

extern void func_800CA60C(TownObject *obj, s32 arg1, s32 arg2);

void func_800C9FBC(TownObject *obj, s32 arg1, s32 arg2) {
    u16 timer;
    u16 value;

    timer = obj->timer - 1;
    obj->timer = timer;
    if ((timer << 16) <= 0) {
        func_800CA60C(obj, arg1, arg2);
        value = obj->value + 0x800;
    } else {
        value = obj->output + 0x100;
    }
    obj->output = value;
}

/* MECHANISM: The seed's 24-byte frame and s0-held object base were already exact.
   A guarded v0 value plus ASM_TAILSLOT_PIN_TIED lets LEAD 28 sink value+0x800
   into LEAD 22's tail-j delay; the live output RMW uses +0x100. */
