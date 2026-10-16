#include "common.h"

extern s32 dungeonAdjustSourceValueAndFinalize(void *ptr, void *ptr2);
extern s32 dungeonRollThresholdEffectVariantB(void *entity, s16 chance, s16 effect_value);
extern s32 dungeonWrapPositionAndSetStateValue(s32 state_value);
extern s32 D_800DCF14;
extern u8 D_800E191B[];
extern u8 D_800E1A44[];

/* Attempt to apply a status effect and display the result. */
s32 func_800C8B84(void *entity, s16 chance, s16 effect_value) {
    if (dungeonRollThresholdEffectVariantB(entity, chance, effect_value) != 0) {
        dungeonAdjustSourceValueAndFinalize(entity, D_800E1A44);
        if (*(u8 *)((u8 *)entity + 0x13) == 0) {
            dungeonWrapPositionAndSetStateValue(D_800DCF14);
        }
        return 1;
    }
    if ((*(s32 *)((u8 *)entity + 0x1C) & 0x10) == 0) {
        dungeonAdjustSourceValueAndFinalize(entity, D_800E191B);
    }
    return 0;
}
