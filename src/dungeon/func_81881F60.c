#include "modules/dungeon_ovl_18a0800.h"
#include "common.h"

extern s32 func_8009D218(s32, s32);
extern s32 func_800A48F0(s32, s32, s32);
extern void func_80099844(s32, void *);
extern u8 D_800E1CD5[9];

/* Conditionally applies D_800E1CD5 using a check indexed by the supplied value's low byte. */
void func_80025760(s32 target, u8 packedValue, void *owner_context) {
    if (func_8009D218(target, 1) == 0) {
        s32 valueGroupIndex = packedValue >> 2;
        valueGroupIndex += 2;
        if ((func_800A48F0(target, 0x15, valueGroupIndex) << 16) != 0) {
            func_80099844(target, D_800E1CD5);
        }
    }
}
