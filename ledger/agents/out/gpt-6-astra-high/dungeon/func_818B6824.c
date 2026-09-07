#include "common.h"
#include "m2c_compat.h"

extern s32 func_8009D218(void *, s32);
extern s32 func_800A6870(s32);
extern void func_800AD4D0(void *);
extern s16 func_800AD568(void *, s32);
extern M2C_UNK func_800B4C7C(s32, void *, s32, s32);

typedef struct S_818B6824_0 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[0x3B];
    u16 unk_64;
} S_818B6824_0;   /* arg0 in func_818B6824 */

/* Adds a computed gain to the target's stored value, doubling it when flagged. */
void func_818B6824(S_818B6824_0 *target, s32 gain_param) {
    register s32 base_gain ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 gain;

    if (func_8009D218(target, 1) == 0) {
        base_gain = func_800A6870(gain_param & 0xFF) + 8;
        gain = base_gain;
        if (target->unk_28 & 1) {
            gain = base_gain << 1;
        }
        target->unk_64 = (u16) (target->unk_64 + gain);
        func_800AD568(target, gain);
        func_800B4C7C(0x8004, target, (s16) target->unk_64, 1);
        func_800AD4D0(target);
    }
}
