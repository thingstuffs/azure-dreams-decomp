#include "common.h"

extern u8 D_800178F8[8];
extern u8 D_800178FC[8];
extern u8 D_80017918[8];
extern u8 *D_8001E950;

u8 *func_80019AFC(s32 arg0, s32 arg1)
{
    u8 *result;

    if (arg1 == 9) {
        return D_800178FC;
    }
    if (arg1 == 10) {
        return D_800178FC;
    }
    if ((u32)(arg1 - 3) < 6U) {
        return D_80017918;
    }
    if (arg1 != 2) {
        result = D_800178F8;
    } else {
        result = D_800178F8 + (D_8001E950[4] * 4);
    }
    return result;
}

/* MECHANISM: Frameless leaf with the true ROWBASE name and a two-argument ABI
   keeps the selector in a1; shared pointer-return arms reproduce the CFG.
   Byte-scaled final indexing preserves the retail lbu/sll/addu sequence. */
