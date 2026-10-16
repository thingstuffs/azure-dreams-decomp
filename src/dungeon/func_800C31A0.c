#include "common.h"

extern s32 dungeonRollChanceAndApplyEffectFour(void *, s16, s16);
extern void dungeonAdjustSourceValueAndFinalize(void *, const u8 *);
extern void dungeonWrapPositionAndSetStateValue(s32);
extern u8 D_800E19E8[];
extern u8 D_800E1A01[];
extern s32 D_800DCF18;

/* Apply the chance-based status and select its success or failure message. */
s32 func_800C8900(void *actor, s32 chance, s32 action)
{
    if (dungeonRollChanceAndApplyEffectFour(actor, (s16)chance, (s16)action)) {
        dungeonAdjustSourceValueAndFinalize(actor, D_800E19E8);
        if (((u8 *)actor)[0x13] == 0) {
            dungeonWrapPositionAndSetStateValue(D_800DCF18);
        }
        return 1;
    }
    dungeonAdjustSourceValueAndFinalize(actor, D_800E1A01);
    return 0;
}
