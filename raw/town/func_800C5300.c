#include "common.h"

extern s32 func_800C2AAC(s32 arg0);
extern s32 D_800834B8;
extern s32 D_80097D2C;
extern void *D_800CFCC4;

s32 func_800C2A60(void *arg0) {
    s32 result;
    s32 return_value;

    ASM_SCHED_BARRIER();
    if (D_800CFCC4 != 0) {
        result = 0;
        if (*(s32 *)((u8 *)D_800CFCC4 + 0x60) ==
            *(s32 *)((u8 *)arg0 + 0x60)) {
            result = D_800834B8 == (s32)&D_80097D2C;
        }
        return_value = result;
        ASM_TAILSLOT_PIN(return_value);
        return func_800C2AAC(result);
    }
    return 0;
}

/* MECHANISM: An entry ASM_SCHED_BARRIER keeps GCC's frame alloc/save ahead of the first global load;
   LEAD 19 then elides them while preserving the retail load and branch delay nops.
   A short-lived pinned $v0 copy plus ASM_TAILSLOT_PIN lets LEAD 28 sink move v0,a0
   into LEAD 22's converted func_800C2AAC tail-jump delay slot. */
