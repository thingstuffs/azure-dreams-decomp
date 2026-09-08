#include "common.h"

extern s32 func_800251F4();
extern s32 func_800419EC();
extern s32 func_800A56E0();
extern s16 func_800BCB04();

void func_80025648(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 x = arg1;
    s32 y = arg2;
    register s32 call_x ASM_REG("$3") = x;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 call_y ASM_REG("$5") = y;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 base ASM_REG("$20") = arg0 + 0x20;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 limit = (s16)arg3;
    register s32 raw_lower ASM_REG("$6") = arg4;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 shifted_lower ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 lower ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 first_arg;
    s32 second_arg;
    s16 result;

    if (limit < 0x200) {
        ASM_KEEP(call_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        first_arg = call_x & 0xFFFF;
        second_arg = call_y & 0xFFFF;
        ASM_KEEP(raw_lower);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        shifted_lower = raw_lower << 16;
        lower = shifted_lower >> 16;
        result = func_800BCB04(first_arg, second_arg, lower, arg3 << 16);
        if (result < limit && result >= lower) {
            func_800251F4(base, (s16)x, (s16)y, limit);
            ASM_KEEP(lower);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            func_800419EC(6, 12);
            func_800A56E0(0x50B);
        }
    }
}

/* MECHANISM: Wide incoming values narrow only at use sites; guarded pins hold the retail s2/s3/s4 roles.
   Split first-call x/y live ranges produce the early v1/a1 copies, while raw arg4 remains in a2.
   A pinned v0 shift intermediate prevents destructive a2 sign-extension and closes words 19-20. */
