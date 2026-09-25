#include "slus/cd_cohort_types.h"

/* Reset the global state fields and initialize the status bytes to 2 and 255. */
void func_8003E34C(void) {
    *(u8 *)0x800814D2 = 2;
    *(u8 *)0x800814D3 = 0xFF;
    D_80083958[0].unk0 = 0;
    D_800814D0 = 0;
    *(u8 *)0x800814D1 = 0;
    D_80083958[0].unk4 = 0;
    D_80083958[0].unk5 = 0;
    D_80080AD0 = 0;
    D_80080ADC = 0;
    D_80080AD4 = 0;
    D_80083958[0].counter1 = 0;
    D_80083958[0].counter2 = 0;
}
