#include "modules/dungeon_resource12_slot0.h"

void update_turning_fade_effect_and_model(void *record_data) {
    u16 remaining_count;

    remaining_count = ((R12_801749A8_S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_1C - 1;
    ((R12_801749A8_S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_1C = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        ((R12_801749A8_S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((R12_801749A8_S_801748F0_0 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
