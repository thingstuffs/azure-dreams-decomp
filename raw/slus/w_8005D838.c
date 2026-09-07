#include "common.h"

/* If a0 <= 0, returns 0 (no side effects). Otherwise initializes the
 * record *a1 (field0 = 0x40001010, field4 = (0x10000 << D_80079980[0]) - 0x1010),
 * publishes a1 as the global record-list head D_800799BC, clears D_800799B8,
 * stores a0 into D_800799B4, and returns a0. */
typedef struct S_800799BC {
    u32 field0;
    s32 field4;
} S_800799BC;

extern s32 D_80079980[3];
extern s32 D_800799B4[3];
extern s32 D_800799B8[3];
extern S_800799BC *D_800799BC[3];

s32 func_8005D838(s32 a0, S_800799BC *a1) {
    register s32 v0 ASM_REG("v0") = a0;
    if (v0 <= 0) {
        v0 = 0;
    } else {
        s32 shift = D_80079980[0];
        a1->field0 = 0x40001010;
        D_800799BC[0] = a1;
        D_800799B8[0] = 0;
        D_800799B4[0] = v0;
        a1->field4 = (0x10000 << shift) - 0x1010;
    }
    return v0;
}
