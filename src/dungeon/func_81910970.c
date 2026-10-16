#include "modules/dungeon_ovl_1930844.h"

s32 dungeonCreateAnEffectPositionRandomizedSpriteAngle(Rec_func_80024170_arg0 *owner, void *source_position)
{
    s32 random_value;
    s32 initial_z;
    s32 rounded_random;
    ovl_1930844_81910970_S_80024170_3 *sprite;
    ovl_1930844_81910970_S_80024170_1 *effect_state;
    void *effect;
    ovl_1930844_81910970_S_80024170_4 *position;

    effect = func_8003FC64(0x212);
    if (effect != 0) {
        effect_state = effect + 0x20;
        ((ovl_1930844_81910970_S_80024170_0 *)effect)->unk_10 = (void *)func_80024044;
        ((ovl_1930844_81910970_S_80024170_0 *)effect)->unk_20 = owner;
        effect_state->unk_06 = 0;
        effect_state->unk_08 = owner->unk_12.as_u16;
        sprite = ((ovl_1930844_81910970_S_80024170_0 *)effect)->unk_0C;
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        sprite->unk_08 = D_800DE720;
        sprite->unk_12 = 0x7E00;
        sprite->unk_14 |= 0x100;
        rounded_random = rand();
        random_value = rounded_random;
        if (random_value < 0) {
            rounded_random = random_value + 0xFFF;
        }
        sprite->unk_1A = (random_value % 4096);
        sprite->unk_1E = 0x400;
        sprite->unk_1C = 0x400;
        func_8004491C(effect, func_80045340);
        position = ((ovl_1930844_81910970_S_80024170_0 *)effect)->unk_08;
        *(ovl_1930844_81910970_Copy6 *)position = *(ovl_1930844_81910970_Copy6 *)source_position;
        initial_z = position->unk_08;
        effect_state->unk_0C = initial_z;
        return (s32)effect;
    }
    return 0;
}
