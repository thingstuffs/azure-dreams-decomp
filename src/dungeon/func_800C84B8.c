#include "common.h"

extern s32 func_80042900(void *, s32);
extern s32 func_800A6508(void);
extern s32 func_800A6D30(void *, s32, s32, s32);

typedef struct {
    u8 pad[0xA];
    u16 value;
} CounterState;

extern CounterState D_80083460;
extern u8 D_800E3D40;
extern u8 *D_800E3D7C[];

s32 func_800CDC18(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 temp_a0;
    register s16 divisor;
    s32 remainder;
    s16 var_s0;

    if (*(u8 *)((u8 *)arg0 + 0x13) == 0) {
        var_s0 = 0;
        if (D_800E3D40 == 0) {
            temp_a0 = func_800A6D30(arg0, arg1, arg2, arg3) & 0xFFFF;
            if (((u8)(*(u8 *)((u8 *)arg0 + 3))) != 0) {
                remainder = temp_a0 % ((s16)((s32)((u8)(*(u8 *)((u8 *)arg0 + 3)))));
                var_s0 = remainder;
            }
        }

        if (func_80042900(arg0, 10) << 16) {
            var_s0 = 0xFF;
        }

        if (var_s0 < 0x30) {
            *(u16 *)(D_800E3D7C[0] + 0xA2) |= 0x100;
            D_80083460.value += 1;
        } else if (*(u8 *)((u8 *)arg0 + 0x13) == 0) {
            /* garbage-passthru: a3 is 10 left by func_80042900, not a caller-held C value. */
            func_800A6508();
        }
    }
    return 1;
}
