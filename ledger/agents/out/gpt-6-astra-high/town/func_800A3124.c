#include "common.h"

extern void func_800A0B74(void *arg0, s32 arg1);
extern void *D_800A08E8;

// Increase the object's ramp value, then finalize and change state at the limit.
void func_800A0884(void *object, void *context) {
    u16 rampValue;

    rampValue = *(u16 *)((u8 *)object + 0x6E) + 0x40;
    *(u16 *)((u8 *)object + 0x6E) = rampValue;
    if ((s16) rampValue >= 0x400) {
        *(u16 *)((u8 *)object + 0x6E) = 0x400U;
        func_800A0B74(object, *(s32 *)((u8 *)context + 0x48));
        *(void **)((u8 *)object + 0x50) = &D_800A08E8;
    }
}
