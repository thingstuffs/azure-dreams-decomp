#include "common.h"
#include "m2c_compat.h"

extern s32 func_8009D218(void *arg0, s32 arg1);
extern s32 func_800A6870(s32 arg0);
extern void func_800AD4D0(void *arg0);
extern void func_800AD568(void *arg0, s32 arg1);
extern void func_800B4C7C(s32 arg0, void *arg1, s32 arg2, s32 arg3);

typedef struct S_818B0850_0 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[0x3B];
    u16 unk_64;
} S_818B0850_0;   /* arg0 in func_818B0850 */

/* Applies a flag-adjusted value increase to an eligible entity and updates it. */
void func_818B0850(void *entity, s32 value_id) {
    if (func_8009D218(entity, 4) == 0) {
        register s32 base_gain ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
        s16 bonus;
        s32 gain;

        base_gain = func_800A6870(value_id & 0xFF) + 8;
        bonus = ((S_818B0850_0 *)entity)->unk_28 & 4;
        gain = base_gain;
        if (bonus) {
            bonus = (s32) (base_gain << 16) >> 18;
            gain = base_gain + bonus;
        }
        ((S_818B0850_0 *)entity)->unk_64 = (u16) (((S_818B0850_0 *)entity)->unk_64 + gain);
        func_800AD568(entity, gain);
        func_800B4C7C(0x8004, entity, (s16) ((S_818B0850_0 *)entity)->unk_64, 1);
        func_800AD4D0(entity);
    }
}
