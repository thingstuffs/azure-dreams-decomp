#include "modules/dungeon_ovl_18c4828.h"

s32 func_800244A0(Row_818A4CA0_S_818A4CA0_1 *effect_data, Row_818A4CA0_S_818A4CA0_2 *origin, s16 effect_param, s16 frame_index) {
    s32 result;
    s16 angle;
    u16 height;
    s32 shifted_frame;
    s32 random_value;
    s32 biased_random;

    Row_818A4CA0_S_818A4CA0_3 *sprite;
    Row_818A4CA0_S_818A4CA0_4 *position;
    void *effect;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        random_value = (s32)func_80024340;
        ((Row_818A4CA0_S_818A4CA0_0 *)effect)->unk_20 = effect_data;
        effect_data = effect + 0x20;
        ((Row_818A4CA0_S_818A4CA0_0 *)effect)->unk_10 = (void *)random_value;
        effect_data->unk_04 = effect_param;
        effect_data->unk_06 = (s16) (-6 - (rand() % 5));
        effect_data->unk_08 = (u16) origin->unk_02;
        effect_data->unk_0A = (u16) origin->unk_06;
        effect_data->unk_0C = (u16) (origin->unk_0A + 0x20);
        sprite = ((Row_818A4CA0_S_818A4CA0_0 *)effect)->unk_0C;
        sprite->unk_0E = 0x60;
        sprite->unk_0D = 0x60;
        sprite->unk_0C = 0x60;
        sprite->unk_12 = 0x7E07;
        sprite->unk_10 = (u16) (sprite->unk_10 | 0x60);
        sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
        shifted_frame = (s32)frame_index << 0x10;
        func_8003DB94(sprite, &D_800DECF8, (s16) ((shifted_frame >> 0x10) % 5));
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        func_8004491C(effect, func_80045340);
        position = ((Row_818A4CA0_S_818A4CA0_0 *)effect)->unk_08;
        random_value = rand();
        biased_random = random_value;
        angle = (random_value % 4096);
        position->unk_02 = (s16) (effect_data->unk_08 + ((s32) (func_800644B8(angle) * 2) >> 8));
        position->unk_06 = (s16) (effect_data->unk_0A + ((s32) (func_80064584(angle) * 2) >> 8));
        height = effect_data->unk_0C;
        result = (s32)effect;
        position->unk_0A = (s16)height;
        return result;
    }
    result = 0;
    return result;
}

