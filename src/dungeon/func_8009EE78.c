#include "common.h"

extern s32 func_8009A350(s32, s32, s32, s16 *);
extern void func_800A466C(void);
extern s32 func_800BCB04(s32, s32, s16);

s32 func_800A45D8(s32 arg0, s32 arg1, s32 arg2)
{
    s16 height;
    s32 x_now;
    s32 y_now;
    register s32 call_x ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 call_kind;
    s32 held_x;
    s32 held_y;
    s32 held_z;
    s32 result;
    s32 limit;

    held_z = arg2;
    x_now = (u16)arg0 >> 6;
    call_x = x_now - 1;
    y_now = (u16)arg1 >> 6;
    call_kind = 0;
    held_x = x_now;
    held_y = y_now;
    ASM_KEEP(held_z);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ASM_KEEP(call_kind);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(held_x);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_KEEP(held_y);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP(y_now);   /* MATCH pin: keeps a statement from moving across a call/branch */

    if ((func_8009A350(call_x, y_now, call_kind, &height) << 16) == 0) {
        return 0;
    }
    if (height & 0x8000) {
        return 1;
    }

    result = func_800BCB04((held_x << 6) | 0x20,
                           (held_y << 6) | 0x20,
                           (s16)(held_z - 0x20));
    height = result;
    result <<= 16;
    limit = 0x02000000;
    return limit < result;
}

/* MECHANISM: Separate call-argument temporaries from held s0/s1 coordinates to reproduce
   the 0x28 frame and interleaved s2/s0/s1 saves. Keep the s32 helper result in v0/v1
   so LEAD-22 moves the final slt into func_800A466C's sibcall delay slot. */
