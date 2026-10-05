#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

extern s32 func_8009D218(void *entity, s32 flags);
extern s32 func_800A6870(s16 input_value);
extern void func_800AD4D0(void *entity);
extern void func_800AD568(void *entry);
extern void func_800B4C7C(s32 flags, u8 *source_data, s16 value, u16 callback_mode);


/* Applies a flag-adjusted value increase to an eligible entity and updates it. */
void func_818B0850(EntityRec *entity, s32 value_id) {
    if (func_8009D218(entity, 4) == 0) {
        s32 base_gain;
        s16 bonus;
        s32 gain;

        base_gain = func_800A6870(value_id & 0xFF) + 8;
        bonus = entity->unk_28 & 4;
        gain = base_gain;
        if (bonus) {
            bonus = (s32) (base_gain << 16) >> 18;
            gain = base_gain + bonus;
        }
        entity->unk_64 = (u16) (((u16)entity->unk_64) + gain);
        func_800AD568(entity);
        base_gain = 0x8004;
        func_800B4C7C(base_gain, entity, (s16) ((u16)entity->unk_64), 1);
        func_800AD4D0(entity);
    }
}
