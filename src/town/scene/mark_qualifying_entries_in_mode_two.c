#include "common.h"
#include "town/scene/state_data.h"
#include "town/scene/choice_data.h"
#include "town/scene.h"
#include "town/player/state.h"
#include "town/scene/indexed_values_data.h"

typedef struct S_80017DBC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80017DBC_1;

typedef struct S_80017DBC_2 {
    u8 pad_00[0xA2];
    s16 unk_A2;
    u8 pad_A4[0x12];
    s16 unk_B6;
} S_80017DBC_2;

extern s32 D_80016608;

/* Marks qualifying entries and their associated state with 0x400 in mode 2. */
s32 mark_qualifying_entries_in_mode_two(void)
{
    s32 entry_index;
    TownIndexedValueRecord *source_entry;
    S_80017DBC_1 *dest_entry;
    S_80017DBC_2 *dest_state;

    if (scene_update_state == 2) {
        dest_state = (S_80017DBC_2 *)&D_80016608;
        for (entry_index = 1; entry_index < 8; entry_index++) {
            source_entry = &town_indexed_values[entry_index];
            dest_entry = (S_80017DBC_1 *)((u8 *)dest_state + entry_index * 0x14);
            if (get_script_flag_mask(source_entry->flag) != 0) {
                if (source_entry->condition != 0) {
                    dest_entry->unk_02 = 0x400;
                    if (entry_index == 1) {
                        dest_state->unk_A2 = 0x400;
                    } else {
                        dest_state->unk_B6 = 0x400;
                    }
                } else if (scene_choice_index == entry_index) {
                    dest_entry->unk_02 = 0x400;
                }
            }
        }
        return 0;
    }
    return 1;
}
