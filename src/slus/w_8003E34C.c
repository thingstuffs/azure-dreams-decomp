#include "common.h"

#include "common.h"

typedef struct {
    s32 unk0;
    u8 unk4;
    u8 unk5;
    s16 unk6;
    s16 unk8;
} S_80083958;

extern s8 D_80080AD0;
extern s16 D_80080AD4;
extern s32 D_80080ADC;
extern s8 D_800814D0;
extern S_80083958 D_80083958;

/* Reset the global state fields and initialize the status bytes to 2 and 255. */
void func_8003E34C(void) {
    *(u8 *)0x800814D2 = 2;
    *(u8 *)0x800814D3 = 0xFF;
    D_80083958.unk0 = 0;
    D_800814D0 = 0;
    *(u8 *)0x800814D1 = 0;
    D_80083958.unk4 = 0;
    D_80083958.unk5 = 0;
    D_80080AD0 = 0;
    D_80080ADC = 0;
    D_80080AD4 = 0;
    D_80083958.unk6 = 0;
    D_80083958.unk8 = 0;
}
