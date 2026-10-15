#include "common.h"

extern s32 func_800C8980(void *, s16, s16);
extern void func_80099844(void *, const u8 *);
extern void func_800DC1B8(s32);
extern u8 D_800E19E8[];
extern u8 D_800E1A01[];
extern s32 D_800DCF18;

/* Apply the chance-based status and select its success or failure message. */
s32 func_800C8900(void *actor, s32 chance, s32 action)
{
    if (func_800C8980(actor, (s16)chance, (s16)action)) {
        func_80099844(actor, D_800E19E8);
        if (((u8 *)actor)[0x13] == 0) {
            func_800DC1B8(D_800DCF18);
        }
        return 1;
    }
    func_80099844(actor, D_800E1A01);
    return 0;
}
