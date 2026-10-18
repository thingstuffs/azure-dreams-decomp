#include "modules/dungeon_ovl_7e71d800.h"

void copy_selected_table_pair(void *record_field, s32 pair_index) {
    u16 value_pairs[12];
    s32 shifted_index;
    Row_818E786C_S_8002506C_1 *linked_record;
    Row_818E786C_S_8002506C_2 *pair;

    __builtin_memcpy(value_pairs, D_80024004, 24);
    if ((u32)(pair_index & 0xFFFF) >= 6U) {
        pair_index = 0;
    }
    shifted_index = pair_index << 0x10;
    pair = (u8 *)value_pairs + (shifted_index >> 0xE);
    linked_record = ((Row_818E786C_S_8002506C_0 *)((u8 *)record_field - 0x14))->unk_00;
    linked_record->unk_1C = (u16)pair->unk_00;
    linked_record->unk_1E = (u16)pair->unk_02;
}
