#include "common.h"

typedef struct {
    short field_0;
    char pad4[6];
    unsigned short field_8;
    unsigned short field_A;
} S_8005B2C8_D80086C00;

extern S_8005B2C8_D80086C00 D_80086C00[8];

/* Looks up the 12-byte D_80086C00[index] struct entry and copies its
   two u16 fields (offsets 0x8 and 0xA) out through the two output
   pointers. */
void func_8005B2C8(short a0, int a1, unsigned short *a2, unsigned short *a3)
{
    S_8005B2C8_D80086C00 *base = D_80086C00;
    S_8005B2C8_D80086C00 *v0 = &base[a0];
    *a2 = v0->field_8;
    *a3 = v0->field_A;
}
