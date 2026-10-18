#include "modules/dungeon_ovl_7f511800_p04.h"

/* Advance state and decrement the record count, setting record and global flags at completion. */
void advance_record_state_and_set_completion_flags(void *record_data, T_80173FF4_S_80173FF4_0 *state, s32 update_arg) {
    u16 remaining_count;

    state->unk_08 = (s32) (state->unk_08 + 0x10000);
    func_800478B8(update_arg);
    remaining_count = ((T_80173FF4_S_80173FF4_1 *)((u8 *)record_data - 0x2))->unk_1C - 1;
    ((T_80173FF4_S_80173FF4_1 *)((u8 *)record_data - 0x2))->unk_1C = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        ((T_80173FF4_S_80173FF4_1 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((T_80173FF4_S_80173FF4_1 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
