#include "modules/dungeon_ovl_7e765800.h"

s32 create_randomized_transform_effect(s32 owner_id, Row_8189EBBC_S_800243BC_3 *transform)
{
    s32 random_value;
    s32 rounded_random;
    s32 return_value;
    Row_8189EBBC_S_800243BC_2 *sprite;
    void *object;
    Row_8189EBBC_S_800243BC_1 *state;
    Row_8189EBBC_S_800243BC_4 *object_transform;

    object = func_8003FC64(0x212);
    if (object != 0) {
        state = object + 0x20;
        ((Row_8189EBBC_S_800243BC_0 *)object)->unk_10 = &D_80024264;
        state->unk_08 = owner_id;
        ((Row_8189EBBC_S_800243BC_0 *)object)->unk_20 = 0;
        state->unk_02 = 0;
        state->unk_04 = 0x10;
        sprite = ((Row_8189EBBC_S_800243BC_0 *)object)->unk_0C;
        sprite->unk_12 = 0x7E02;
        sprite->unk_0E = 0;
        sprite->unk_0D = 0;
        sprite->unk_0C = 0;
        sprite->unk_1E = 0;
        sprite->unk_1C = 0;
        sprite->unk_14 = (s16)(sprite->unk_14 | 0xC);
        sprite->unk_10 = (u16)(sprite->unk_10 | 0x20);
        sprite->unk_14 = (u16)(sprite->unk_14 | 0x100);
        random_value = rand();
        rounded_random = random_value;
        if (random_value < 0) {
            rounded_random = random_value + 0xF;
        }
        func_8003DB94(sprite, &D_800DEF08,
                      (s16)(random_value - ((rounded_random >> 4) * 0x10)));
        func_8004491C(object, &D_800D36D0);
        object_transform = ((Row_8189EBBC_S_800243BC_0 *)object)->unk_08;
        return_value = (s32)object;
        *object_transform = *(Row_8189EBBC_S_800243BC_4 *)transform;
        return return_value;
    }
    return 0;
}
