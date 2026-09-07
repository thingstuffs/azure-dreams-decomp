#include "common.h"

typedef struct {
    u16 value;
    u8 pad[8];
} Counter;

typedef struct {
    s32 value;
    u8 pad[8];
} Flags;

extern Counter D_80026472;
extern Flags D_800814A0;

void func_8188CFAC(u16 *arg0)
{
    u16 value;
    u16 counter;

    counter = D_80026472.value;
    ASM_KEEP(counter);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    value = arg0[13] + 1;
    counter++;
    arg0[13] = value;
    D_80026472.value = counter;
    if ((s16)value >= 0x101) {
        arg0[-1] |= 0x8000;
        D_800814A0.value |= 0x8000;
    }
}
