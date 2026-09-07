#include "common.h"

extern s32 func_8009A350(s32, s32, s32, s16 *);
extern void func_800A466C(void);
extern s32 func_800BCB04(s32, s32, s16);

s32 func_800A45D8(s32 arg0, s32 arg1, s32 arg2)
{
    s16 height;
    register s32 x_now ASM_REG("$2");
    register s32 y_now ASM_REG("$5");
    register s32 call_x ASM_REG("$4");
    register s32 call_kind ASM_REG("$6");
    register s32 held_x ASM_REG("$16");
    register s32 held_y ASM_REG("$17");
    register s32 held_z ASM_REG("$18");
    register s32 result ASM_REG("$2");
    register s32 limit ASM_REG("$3");

    held_z = arg2;
    x_now = (u16)arg0 >> 6;
    call_x = x_now - 1;
    y_now = (u16)arg1 >> 6;
    call_kind = 0;
    held_x = x_now;
    held_y = y_now;
    ASM_KEEP(held_z);
    ASM_KEEP(call_x);
    ASM_KEEP(call_kind);
    ASM_KEEP(held_x);
    ASM_KEEP(held_y);
    ASM_KEEP(x_now);
    ASM_KEEP(y_now);

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
    ASM_KEEP(result);
    ASM_KEEP(limit);
    func_800A466C();
    return limit < result;
}

/* MECHANISM: Separate call-argument temporaries from held s0/s1 coordinates to reproduce
   the 0x28 frame and interleaved s2/s0/s1 saves. Keep the s32 helper result in v0/v1
   so LEAD-22 moves the final slt into func_800A466C's sibcall delay slot. */
