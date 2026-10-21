#include "common.h"

#include "common.h"
#include "engine/object.h"
#include "slus/data.h"

typedef struct InputRecord {
    s16 field_00;
    s16 field_02;
    u16 field_04;
    u16 field_06;
    void *field_08;
    void *field_0C;
    u16 field_10;
    u16 field_12;
} InputRecord;

typedef struct RuntimeState {
    u8 pad_00[4];
    void *field_04;
    u8 pad_08[4];
    u16 field_0C;
    u16 field_0E;
    void *field_10;
    u16 field_14;
    u16 field_16;
    s16 field_18;
    s16 field_1A;
    u8 pad_1C[8];
    void *field_24;
    u16 field_28;
    u16 field_2A;
} RuntimeState;

typedef struct TableEntry {
    u16 field_00;
    u16 field_02;
    u16 field_04;
    u16 field_06;
    u8 pad_08[0x18];
} TableEntry;

typedef struct PairRecord {
    u8 pad_00[4];
    s16 field_04;
    s16 field_06;
} PairRecord;

typedef void (*RuntimeCallback)(RuntimeState *, void *);

extern void process_unlinked_type_four_entries(void);
extern PairRecord *build_four_value_entry_result(s16, s16);
extern void request_scene_state_with_parameters(u16, s16, s16, s32, s32);

extern RuntimeState map_runtime_state;
extern RuntimeState map_change_state;
extern RuntimeCallback map_change_callback[3];
extern u8 scene_music_hold;
extern u8 runtime_script_state[9];
extern TableEntry D_800D2650[];
extern TableEntry D_800D2FC0[];
extern u8 town_map_variant;
extern u16 system_update_flags[5];


/* Updates the runtime state from an input record and invokes its callback. */
void change_map(InputRecord *input)
{
    TableEntry *entry;
    PairRecord *pair;
    RuntimeState *state;
    void *callback_data;
    void *state_data;
    u16 entry_index;

    process_unlinked_type_four_entries();
    map_runtime_state.field_28 = map_runtime_state.field_18;
    map_change_state.field_28 = map_runtime_state.field_18;
    map_runtime_state.field_2A = map_runtime_state.field_1A;
    map_change_state.field_2A = map_runtime_state.field_1A;
    map_change_state.field_18 = input->field_00;
    entry_index = input->field_02;
    map_change_state.field_1A = entry_index;
    town_map_variant = entry_index;
    do {
    } while (0);

    if (input->field_00 == 11) {
        entry = (TableEntry *)((u8 *)D_800D2650 +
                               (input->field_02 << 5));
    } else {
        entry = (TableEntry *)((u8 *)D_800D2FC0 +
                               (input->field_02 << 5));
    }

    pair = build_four_value_entry_result(map_change_state.field_18,
                         map_change_state.field_1A);
    if (pair->field_04 == town_saved_stream_index &&
        pair->field_06 == town_saved_sequence_command) {
        scene_music_hold = 1;
    }

    state = &map_change_state;
    state_data = input->field_0C;
    state->field_10 = entry;
    state->field_24 = state_data;
    state->field_14 = input->field_04;
    state->field_16 = input->field_06;
    state->field_0C = town_facing_angles[input->field_10 & 3];
    state->field_0E = input->field_12;
    callback_data = input->field_08;
    if (callback_data != 0) {
        if (state->field_18 != 12) {
            state->field_04 = &D_800812F8;
        } else {
            state->field_04 = callback_data;
        }
    }

    if (map_change_callback[0] != 0) {
        map_change_callback[0](state, callback_data);
    }

    request_scene_state_with_parameters(input->field_00,
                  (s16)(entry->field_04 +
                        (input->field_04 + entry->field_00)),
                  (s16)(entry->field_06 +
                        (input->field_06 + entry->field_02)),
                  0, runtime_transition_flags_alias[0] ^ 1);

    system_update_flags[0] &= 0xFFFD;
    {
        s32 check_result = runtime_is_record_handler_changed(runtime_script_state);
        if (check_result != 0) {
            map_change_pending[0] = 1;
        } else {
            map_change_pending[0] = 0;
        }
        D_8006AE18[0] = 0;
    }
}
