#include "modules/dungeon_ovl_18a6800.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"

extern s32 dungeonTryTriggerTargetRecordEffect(s32, s32);
extern s32 func_800A48F0(s32, s32, s32);
extern void dungeonAdjustSourceValueAndFinalize(s32, void *);
extern u8 D_800E1D01[9];

/* Checks the target using a scaled low-byte value and conditionally applies D_800E1D01. */
void dungeonCheckTheTargetUsingScaledLowByteConditionallyAppliesGlobal800E1D01(s32 target, s32 value, void *unused) {
    u8 pinnedValue = value;
    if (dungeonTryTriggerTargetRecordEffect(target, 2) == 0) {
        u32 scaledLowByte = pinnedValue;
        scaledLowByte >>= 2;
        if ((func_800A48F0(target, 0x16, scaledLowByte + 4) << 16) != 0) {
            dungeonAdjustSourceValueAndFinalize(target, D_800E1D01);
        }
    }
}
