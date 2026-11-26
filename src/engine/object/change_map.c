#include "common.h"

#include "engine/message/data.h"
#include "engine/object.h"
#include "slus/data.h"
#include "slus/map_state.h"
#include "slus/gp_d92c_owned.h"
#include "slus.h"
#include "town/map/variant_data.h"
#include "town/map.h"
#include "town/shop/position_object_initialization_g01134.h"

typedef struct InputRecord {
    s16 field_00;
    s16 field_02;
    u16 field_04;
    u16 field_06;
    void *descriptor;
    MapChangeCallback callback;
    u16 field_10;
    u16 field_12;
} InputRecord;

extern u16 system_update_flags[5];


/* Updates the runtime state from an input record and invokes its callback. */
void change_map(InputRecord *input)
{
    TownRectangle *entry;
    s16 *sound_selection;
    MapRuntimeState *state;
    void *descriptor;
    MapChangeCallback callback;
    u16 entry_index;

    enqueue_unlinked_item_entries();
    map_runtime_state.previous_scene_selector = map_runtime_state.scene_selector;
    map_change_state.previous_scene_selector = map_runtime_state.scene_selector;
    map_runtime_state.previous_map_index = map_runtime_state.map_index;
    map_change_state.previous_map_index = map_runtime_state.map_index;
    map_change_state.scene_selector = input->field_00;
    entry_index = input->field_02;
    map_change_state.map_index = entry_index;
    town_map_variant = entry_index;
    /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence). */
    do {
    } while (0);

    if (input->field_00 == 11) {
        entry = &town_building_records[input->field_02].position_entry;
    } else {
        entry = &town_map_variants[input->field_02].position_entry;
    }

    sound_selection = build_town_sound_selection(map_change_state.scene_selector,
                                                 map_change_state.map_index);
    if (sound_selection[2] == town_saved_stream_index &&
        sound_selection[3] == town_saved_sequence_command) {
        scene_music_hold = 1;
    }

    state = &map_change_state;
    callback = input->callback;
    state->position = entry;
    state->callback = callback;
    state->x_offset = input->field_04;
    state->y_offset = input->field_06;
    state->facing_angle = town_facing_angles[input->field_10 & 3];
    state->alternate = input->field_12;
    descriptor = input->descriptor;
    if (descriptor != 0) {
        if (state->scene_selector != 12) {
            state->next_descriptor = &D_800812F8;
        } else {
            state->next_descriptor = descriptor;
        }
    }

    if (map_change_state.callback != 0) {
        map_change_state.callback(state, descriptor);
    }

    request_scene_state_with_parameters(input->field_00,
                  (s16)(entry->x_offset +
                        (input->field_04 + entry->origin_x)),
                  (s16)(entry->y_offset +
                        (input->field_06 + entry->origin_y)),
                  0, runtime_transition_flags_alias[0] ^ 1);

    system_update_flags[0] &= 0xFFFD;
    {
        s32 check_result = has_active_script_handler(&runtime_script_state);
        if (check_result != 0) {
            map_change_pending[0] = 1;
        } else {
            map_change_pending[0] = 0;
        }
        D_8006AE18[0] = 0;
    }
}
