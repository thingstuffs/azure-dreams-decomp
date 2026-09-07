#include "common.h"

extern s32 func_800251F4();
extern s32 func_800419EC();
extern s32 func_800A56E0();
extern s16 func_800BCB04();

void func_80025648(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 x = arg1;
    s32 y = arg2;
    register s32 call_x ASM_REG("$3") = x;   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 call_y ASM_REG("$5") = y;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 base ASM_REG("$20") = arg0 + 0x20;   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 limit = (s16)arg3;
    register s32 raw_lower ASM_REG("$6") = arg4;   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 shifted_lower ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 lower ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 first_arg;
    s32 second_arg;
    s16 result;

    if (limit < 0x200) {
        ASM_KEEP(call_x);   /* MATCH pin: retail schedule: same instructions, different order without it */
        first_arg = call_x & 0xFFFF;
        second_arg = call_y & 0xFFFF;
        ASM_KEEP(raw_lower);   /* MATCH pin: retail schedule: same instructions, different order without it */
        shifted_lower = raw_lower << 16;
        lower = shifted_lower >> 16;
        result = func_800BCB04(first_arg, second_arg, lower, arg3 << 16);
        if (result < limit && result >= lower) {
            func_800251F4(base, (s16)x, (s16)y, limit);
            ASM_KEEP(lower);   /* MATCH pin: load-bearing for the whole function shape */
            func_800419EC(6, 12);
            func_800A56E0(0x50B);
        }
    }
}

/* MECHANISM: Wide incoming values narrow only at use sites; guarded pins hold the retail s2/s3/s4 roles.
   Split first-call x/y live ranges produce the early v1/a1 copies, while raw arg4 remains in a2.
   A pinned v0 shift intermediate prevents destructive a2 sign-extension and closes words 19-20. */
