#include "common.h"

extern u16 D_8007142C[];
extern u8 D_8007147C[];

u8 func_8004D828(s32 key)
{
    u16 value;
    s32 i;

    i = 0;
    value = D_8007142C[0];
    if (value != 0) {
        while (D_8007142C[i] != (key & 0xFFFF)) {
            ASM_SCHED_BARRIER();
            i++;
            if (D_8007142C[i] == 0) {
                break;
            }
        }
    }
    return D_8007147C[i];
}
