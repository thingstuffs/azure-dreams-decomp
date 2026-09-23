#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

extern s32 func_8009D218(void *, s32);
extern s32 func_800A6870(s32);
extern void func_800AD4D0(void *);
extern s16 func_800AD568(void *, s32);
extern M2C_UNK func_800B4C7C(s32, void *, s32, s32);


/* Adds a computed gain to the target's stored value, doubling it when flagged. */
void func_818B6824(Rec_D_800E3D7C *target, s32 gain_param) {
    s32 base_gain;
    register s32 gain;

    if (func_8009D218(target, 1) == 0) {
        base_gain = func_800A6870(gain_param & 0xFF) + 8;
        gain = base_gain;
        if (target->unk_28 & 1) {
            gain = base_gain << 1;
        }
        target->unk_64.as_u16 = (u16) (target->unk_64.as_u16 + gain);
        func_800AD568(target, gain);
        base_gain = 0x8004;
        func_800B4C7C(base_gain, target, (s16) target->unk_64.as_u16, 1);
        func_800AD4D0(target);
    }
}
