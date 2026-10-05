#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

extern s32 func_8009D218(void *, s32);
extern s32 func_800A6870(s16 input_value);
extern void func_800AD4D0(void *);
extern s16 func_800AD568(void *);
extern void *func_800B4C7C(s32 flags, u8 *source_data, s16 value, u16 callback_mode);


/* Adds a computed gain to the target's stored value, doubling it when flagged. */
void func_818B6824(EntityRec *target, s32 gain_param) {
    s32 base_gain;
    register s32 gain;

    if (func_8009D218(target, 1) == 0) {
        base_gain = func_800A6870(gain_param & 0xFF) + 8;
        gain = base_gain;
        if (target->unk_28 & 1) {
            gain = base_gain << 1;
        }
        target->unk_64 = (u16) (((u16)target->unk_64) + gain);
        func_800AD568(target);
        base_gain = 0x8004;
        func_800B4C7C(base_gain, target, (s16) ((u16)target->unk_64), 1);
        func_800AD4D0(target);
    }
}
