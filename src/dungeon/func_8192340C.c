#include "modules/dungeon_ovl_7e6e1800.h"

void advance_radial_effect_state(void *entity_data, s32 unused, Row_8192340C_DungeonEffect *effect_data) {
    u16 ticks_left;
    u16 updated_value;
    s32 fade_level;

    ticks_left = *(u16 *)(entity_data + 0x5A);
    *(s16 *)((u8 *)&(*(Row_8192340C_DungeonActive *)D_80025B60)) = 1;
    if (!(ticks_left & 3)) {
        func_800478B8(effect_data);
    }

    updated_value = effect_data->unk_1C + 0x32;
    effect_data->unk_1C = updated_value;
    if (updated_value >= 0x2001) {
        effect_data->unk_1C = 0x2000;
    }

    updated_value = effect_data->unk_1E + 0x32;
    effect_data->unk_1E = updated_value;
    if (updated_value >= 0x2001) {
        effect_data->unk_1E = 0x2000;
    }

    updated_value = *(u16 *)(entity_data + 0x5A) - 1;
    fade_level = ((s32)(updated_value << 16) >> 9) / *(s16 *)(entity_data + 0x5C);
    *(u16 *)(entity_data + 0x5A) = updated_value;
    effect_data->unk_E = fade_level;
    effect_data->unk_D = fade_level;
    effect_data->unk_C = fade_level;

    if (*(s16 *)(entity_data + 0x5A) <= 0) {
        *(u16 *)(entity_data - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
    if (effect_data->flags_14 & 0x8000) {
        *(u16 *)(entity_data - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
