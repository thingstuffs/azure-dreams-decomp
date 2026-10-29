/* Sound selection (G00648). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C3884, CL:town/func_800C38D4, PD:town/engine:800D4244, PD:town/engine:800D4260. */
#include "town/map/sound_selection_g00648.h"
#include "town/map.h"

/* Copy the selected table pair into output halfwords 2 and 3. */
void copy_selected_sound_pair(void *output) {
    s32 pair_index;
    u16 *pair_table;
    u16 *pair;

    pair_index = find_target_byte_index_in_list();
    pair_table = fallback_sound_pairs;
    pair = pair_table + (pair_index * 2);
    ((u16 *)output)[2] = pair[0];
    ((u16 *)output)[3] = pair[1];
}

/* Builds a four-value town entry result using table data or a fallback lookup. */
s16 *build_four_value_entry_result(s32 unused, s32 index) {
    s32 entry_index;
    s16 entry_code;
    s16 *output;
    TownEntry *copy_entries;
    u16 *copy_dest;

    D_80113200[0] = -1;
    output = D_80113200;
    output[1] = -1;
    output[2] = -1;
    output[3] = -1;

    if (map_scene_selector_alias != 12) {
        entry_index = index;
    } else {
        TownEntry *entries;
        TownEntry *entry;

        entry_index = find_sound_entry_or_terminator_index(index);
        entries = map_sound_settings;

        entry = (TownEntry *)((u32)(entry_index * 10) + (u8 *)entries);
        if (entry->unk0 != 0) {
            D_80113200[0] = entry->unk2;
            output[1] = entry->unk4;
            entry_code = entry->unk8;
            switch (entry_code) {
            case -4:
                output[2] = town_saved_sound[2];
                output[3] = town_saved_sound[3];
                break;
            case -2:
                copy_selected_sound_pair(output);
                break;
            default:
            {
                TownEntry *found_entry;

                copy_dest = (u16 *)&D_80110004[0x31FC];
                copy_entries = (TownEntry *)&D_800D0004[0x4090];
                found_entry = (TownEntry *)((u8 *)copy_entries + entry_index * 10);
                copy_dest[2] = found_entry->unk6;
                copy_dest[3] = found_entry->unk8;
            }
                break;
            }
            return D_80113200;
        }
    }
    copy_selected_sound_pair(output);
    return D_80113200;
}

/* Loads a four-value record and applies the pending override to its first value. */
void load_pending_sound_record(void) {
    u16 *record_values;
    u16 *current_values;

    SD_Call(0x72);
    drain_audio_commands_and_service_channels();
    SD_Call(0x74);
    drain_audio_commands_and_service_channels();
    audio_load_sound_effect_bank(2);
    load_sound_set(0);

    record_values = (u16 *)build_four_value_entry_result((s16)map_runtime_state.field18, (s16)map_runtime_state.field1A);
    town_sound_selection[0] = record_values[0];
    current_values = town_sound_selection;
    current_values[1] = record_values[1];
    current_values[2] = record_values[2];
    current_values[3] = record_values[3];

    if (town_pending_sound[0] == -5) {
        town_pending_sound[0] = -1;
        town_sound_selection[0] = -1;
    }
    if (town_pending_sound[0] != -1) {
        town_sound_selection[0] = town_pending_sound[0];
    }
    if ((s16) town_sound_selection[0] != -1) {
        audio_load_sound_effect_bank((s16) town_sound_selection[0]);
    }
}

/* Apply pending selections, update playback, and save the active state. */
void apply_sound_selections_and_update(void)
{
    s16 *pending;
    s16 *active;
    s16 *previous;
    s16 *snapshot;
    s32 selection;
    s16 unset;
    u16 saved_slot_0;

    pending = town_pending_sound;
    if (pending[1] == -5) {
        pending[1] = -1;
        town_sound_command[0] = -1;
    }
    if (pending[2] == -5) {
        pending[2] = -1;
        town_stream_index[0] = -1;
    }
    if (pending[3] == -5) {
        pending[3] = -1;
        town_sequence_command[0] = -1;
    }
    unset = -1;
    if (pending[1] != unset)
        town_sound_command[0] = (u16)pending[1];
    if (pending[2] != unset)
        town_stream_index[0] = (u16)pending[2];
    if (pending[3] != unset)
        town_sequence_command[0] = (u16)pending[3];

    active = town_sound_selection;
    selection = active[2];
    if (selection != unset) {
        previous = town_saved_sound;
        if (previous[2] != selection) {
            SD_Call(0x71);
            drain_audio_commands_and_service_channels();
            select_sound_stream(active[2], 0);
            if (active[3] != unset) {
                selection = (u16)active[3];
                SD_Call(selection);
            }
        } else if (active[3] != unset) {
            if (previous[3] != active[3]) {
                SD_Call(0x71);
                drain_audio_commands_and_service_channels();
                selection = (u16)active[3];
                SD_Call(selection);
            } else if (scene_music_hold[0] == 0) {
                SD_Call(0x71);
                drain_audio_commands_and_service_channels();
                selection = (u16)active[3];
                SD_Call(selection);
            }
        } else {
            SD_Call(0x71);
            drain_audio_commands_and_service_channels();
        }
    } else {
        SD_Call(0x71);
        drain_audio_commands_and_service_channels();
        if (active[3] != selection) {
            selection = (u16)active[3];
            SD_Call(selection);
        }
    }

    active = town_sound_selection;
    unset = -1;
    if (active[1] != unset)
        SD_Call((u16)active[1]);
    town_pending_sound[0] = unset;
    {
        s16 *pending_reset = town_pending_sound;
        pending_reset[1] = unset;
        pending_reset[2] = unset;
        pending_reset[3] = unset;
    }
    saved_slot_0 = town_sound_selection[0];
    scene_music_hold[0] = 0;
    town_saved_sound[0] = saved_slot_0;
    {
        u16 saved_slot_1 = active[1];
        u16 saved_selection = active[2];
        u16 saved_floor = active[3];
        snapshot = town_saved_sound;
        snapshot[1] = saved_slot_1;
        snapshot[2] = saved_selection;
        snapshot[3] = saved_floor;
    }
}
