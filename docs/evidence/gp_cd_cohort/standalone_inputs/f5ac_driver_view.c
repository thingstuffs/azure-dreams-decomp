#include "slus/cd_cohort_types.h"
u8 D_800814D0 = 0;
u8 D_800814D4 = 0;
u32 D_800814CC = 0;
SlusCdResult D_80081450 = {0};
u8 D_80080AD0 = 0;
u16 D_80080AD2 = 0;
u16 D_80080AD4 = 0;
s32 D_80080AD8 = 0;
void *D_80080ADC = 0;
s32 D_800814B0 = 0;
s32 D_800814B4 = 0;


/* Returns the stored flags with bit 2 set when D_80080AD4 is nonzero. */
s32 func_8003F5AC(void) {
    s32 flags = D_80083958[0].unk4;

    if (D_80080AD4 != 0) {
        flags |= 4;
    } else {
        flags &= 0xFF;
    }
    return flags;
}
