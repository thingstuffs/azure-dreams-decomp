#include "common.h"

extern void dungeonAdjustSourceValueAndFinalize(void *target, const void *data);
extern s32 dungeonRollThresholdEffectVariantA(void *target, s16 chance, s16 duration);
extern void dungeonWrapPositionAndSetStateValue(s32 state_value);

extern s32 D_800DCF1C[];
extern u8 D_800E19C2[];
extern u8 D_800E19D3[];

/* Attempt to apply a status effect to the target and report success or failure. */
s32 dungeonTryApplyStatusEffect(void *target, s16 chance, s16 duration) {
    if (dungeonRollThresholdEffectVariantA(target, chance, duration) != 0) {
        dungeonAdjustSourceValueAndFinalize(target, D_800E19C2);
        if (*(u8 *)((u8 *)target + 0x13) == 0) {
            dungeonWrapPositionAndSetStateValue(D_800DCF1C[0]);
        }
        return 1;
    }

    dungeonAdjustSourceValueAndFinalize(target, D_800E19D3);
    return 0;
}
