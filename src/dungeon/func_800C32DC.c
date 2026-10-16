#include "common.h"

extern s32 dungeonRollChanceAndRunAction(void *, s16, s16);
extern void dungeonAdjustSourceValueAndFinalize(void *, const u8 *);
extern void dungeonWrapPositionAndSetStateValue(s32);
extern u8 D_800E1A1D[];
extern u8 D_800E1A2D[];
extern s32 D_800DCF0C;

/* Apply the second chance-based status and select its result message. */
s32 func_800C8A3C(void *actor, s32 chance, s32 action)
{
    if (dungeonRollChanceAndRunAction(actor, (s16)chance, (s16)action)) {
        dungeonAdjustSourceValueAndFinalize(actor, D_800E1A1D);
        if (((u8 *)actor)[0x13] == 0) {
            dungeonWrapPositionAndSetStateValue(D_800DCF0C);
        }
        return 1;
    }
    dungeonAdjustSourceValueAndFinalize(actor, D_800E1A2D);
    return 0;
}
