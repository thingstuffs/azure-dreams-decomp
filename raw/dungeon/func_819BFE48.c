#include "common.h"

extern s32 func_800251F4();
extern s32 func_800419EC();
extern s32 func_800A56E0();
extern s16 func_800BCB04();

void func_80025648(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    register s32 x ASM_REG("$18") = arg1;
    register s32 y ASM_REG("$19") = arg2;
    register s32 call_x ASM_REG("$3") = x;
    register s32 call_y ASM_REG("$5") = y;
    register s32 base ASM_REG("$20") = arg0 + 0x20;
    register s32 limit ASM_REG("$16") = (s16)arg3;
    register s32 raw_lower ASM_REG("$6") = arg4;
    register s32 shifted_lower ASM_REG("$2");
    register s32 lower ASM_REG("$17");
    s32 first_arg;
    s32 second_arg;
    s16 result;

    if (limit < 0x200) {
        ASM_KEEP(call_x);
        ASM_KEEP(call_y);
        first_arg = call_x & 0xFFFF;
        second_arg = call_y & 0xFFFF;
        ASM_KEEP(raw_lower);
        shifted_lower = raw_lower << 16;
        ASM_KEEP(shifted_lower);
        lower = shifted_lower >> 16;
        result = func_800BCB04(first_arg, second_arg, lower, arg3 << 16);
        if (result < limit && result >= lower) {
            func_800251F4(base, (s16)x, (s16)y, limit);
            ASM_KEEP(base);
            ASM_KEEP(x);
            ASM_KEEP(y);
            ASM_KEEP(limit);
            ASM_KEEP(lower);
            func_800419EC(6, 12);
            func_800A56E0(0x50B);
        }
    }
}

/* MECHANISM: Wide incoming values narrow only at use sites; guarded pins hold the retail s2/s3/s4 roles.
   Split first-call x/y live ranges produce the early v1/a1 copies, while raw arg4 remains in a2.
   A pinned v0 shift intermediate prevents destructive a2 sign-extension and closes words 19-20. */
