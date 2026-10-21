/* Sound selection (G00648). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C3884, CL:town/func_800C38D4, PD:town/engine:800D4244, PD:town/engine:800D4260. */
#include "town/map/sound_selection_g00648.h"

/* Copy the selected table pair into output halfwords 2 and 3. */
void copy_selected_sound_pair(void *output) {
    s32 pair_index;
    u16 *pair_table;
    u16 *pair;

    pair_index = find_target_byte_index_in_list();
    pair_table = D_800D4244;
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

    if (D_8006ADD4 != 12) {
        entry_index = index;
    } else {
        TownEntry *entries;
        TownEntry *entry;

        entry_index = find_sound_entry_or_terminator_index(index);
        entries = (TownEntry *)&D_800D4094;

        entry = (TownEntry *)((u32)(entry_index * 10) + (u32)entries);
        if (entry->unk0 != 0) {
            D_80113200[0] = entry->unk2;
            output[1] = entry->unk4;
            entry_code = entry->unk8;
            switch (entry_code) {
            case -4:
                output[2] = D_800D4268[2];
                output[3] = D_800D4268[3];
                break;
            case -2:
                copy_selected_sound_pair(output);
                break;
            default:
            {
                TownEntry *entry;

                copy_dest = (u16 *)&D_80110004[0x31FC];
                copy_entries = (TownEntry *)&D_800D0004[0x4090];
                entry = (TownEntry *)((u8 *)copy_entries + entry_index * 10);
                copy_dest[2] = entry->unk6;
                copy_dest[3] = entry->unk8;
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

    record_values = (u16 *)build_four_value_entry_result((s16)D_8006ADBC.field18, (s16)D_8006ADBC.field1A);
    D_800D4260[0] = record_values[0];
    current_values = D_800D4260;
    current_values[1] = record_values[1];
    current_values[2] = record_values[2];
    current_values[3] = record_values[3];

    if (D_800D4258[0] == -5) {
        D_800D4258[0] = -1;
        D_800D4260[0] = -1;
    }
    if (D_800D4258[0] != -1) {
        D_800D4260[0] = D_800D4258[0];
    }
    if ((s16) D_800D4260[0] != -1) {
        audio_load_sound_effect_bank((s16) D_800D4260[0]);
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

    pending = D_800D4258;
    if (pending[1] == -5) {
        pending[1] = -1;
        D_800D4262[0] = -1;
    }
    if (pending[2] == -5) {
        pending[2] = -1;
        D_800D4264[0] = -1;
    }
    if (pending[3] == -5) {
        pending[3] = -1;
        D_800D4266[0] = -1;
    }
    unset = -1;
    if (pending[1] != unset)
        D_800D4262[0] = (u16)pending[1];
    if (pending[2] != unset)
        D_800D4264[0] = (u16)pending[2];
    if (pending[3] != unset)
        D_800D4266[0] = (u16)pending[3];

    active = D_800D4260;
    selection = active[2];
    if (selection != unset) {
        previous = D_800D4268;
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
            } else if (D_80080A88[0] == 0) {
                ((void (*)(s32))SD_Call)(0x71);
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

    active = D_800D4260;
    unset = -1;
    if (active[1] != unset)
        SD_Call((u16)active[1]);
    D_800D4258[0] = unset;
    {
        s16 *pending_reset = D_800D4258;
        pending_reset[1] = unset;
        pending_reset[2] = unset;
        pending_reset[3] = unset;
    }
    saved_slot_0 = D_800D4260[0];
    D_80080A88[0] = 0;
    D_800D4268[0] = saved_slot_0;
    {
        u16 saved_slot_1 = active[1];
        u16 saved_selection = active[2];
        u16 saved_floor = active[3];
        snapshot = D_800D4268;
        snapshot[1] = saved_slot_1;
        snapshot[2] = saved_selection;
        snapshot[3] = saved_floor;
    }
}
