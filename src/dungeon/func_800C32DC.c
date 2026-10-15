#include "common.h"

extern s32 func_800C8ABC(void *, s16, s16);
extern void func_80099844(void *, const u8 *);
extern void func_800DC1B8(s32);
extern u8 D_800E1A1D[];
extern u8 D_800E1A2D[];
extern s32 D_800DCF0C;

/* Apply the second chance-based status and select its result message. */
s32 func_800C8A3C(void *actor, s32 chance, s32 action)
{
    if (func_800C8ABC(actor, (s16)chance, (s16)action)) {
        func_80099844(actor, D_800E1A1D);
        if (((u8 *)actor)[0x13] == 0) {
            func_800DC1B8(D_800DCF0C);
        }
        return 1;
    }
    func_80099844(actor, D_800E1A2D);
    return 0;
}
