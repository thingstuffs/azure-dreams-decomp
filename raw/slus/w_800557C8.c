#include "common.h"

/* FIFO pop from u16 queue at D_80084778: [0]=count (clamped to 0x20),
 * [1..]=entries. Shifts remaining entries left and decrements count. */
extern u16 D_80084778[0x21];

u16 func_800557C8(void)
{
    s32 temp_v1;
    s32 var_a0;
    s32 var_v1;
    s32 one;
    u16 var_a3;

    if ((u16)D_80084778[0] >= 0x21U) {
        D_80084778[0] = 0x20U;
    }

    var_v1 = D_80084778[0];
    var_a3 = 0;
    if (var_v1 != 0) {
        var_a3 = D_80084778[1];
        one = 1;
        if ((u32)one < (u32)var_v1) {
            var_a0 = one;
            do {
                var_v1 = var_a0 & 0xFFFF;
                var_a0 += 1;
                temp_v1 = var_v1 * 2;
                *(u16 *)((u8 *)D_80084778 + temp_v1) =
                    *(u16 *)((u8 *)D_80084778 + temp_v1 + 2);
            } while ((u32)(var_a0 & 0xFFFF) < (u16)D_80084778[0]);
        }
        D_80084778[0] = (u16)(D_80084778[0] - 1);
    }

    return var_a3;
}
