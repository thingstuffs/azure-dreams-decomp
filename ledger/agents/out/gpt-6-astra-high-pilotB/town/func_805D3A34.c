#include "common.h"
#include "m2c_compat.h"

extern u8 D_800198A4[];
extern s32 D_80019B8C;

typedef struct S_805D3A34_0 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_805D3A34_0;   /* base + offset in func_805D3A34 */

/* Checks whether the selected entry's unk_14 field equals 0x5C. */
s32 func_805D3A34(void) {
    s32 offset;
    u8 *base;

    base = D_800198A4;
    offset = D_80019B8C * 0x18;
    return ((S_805D3A34_0 *)(base + offset))->unk_14 == 0x5C;
}
