/* Sound sequence replay. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C3E80. */
#include "town/map/sound_sequence_replay_g00650.h"
#include "town/map.h"
#include "town/shop.h"
#include "engine/audio.h"

/* town_sd_sq_callagain_sub: replay and record the town or fallback sequence with the supplied flags. */
s32 town_sd_sq_callagain_sub(s32 sequence_flags) {
    s32 entry_index;
    u16 town_effect;
    u16 town_sequence;
    u16 fallback_effect;
    u16 fallback_sequence;
    TownEntry *town_entry;
    TownEntry *town_entries;
    u16 *fallback_entries;
    u16 *fallback_entry;
    s32 fallback_index;
        /* MATCH: Keep the merged sequence argument in a0 through each arm. */
    s32 sequence;

    entry_index = find_sound_entry_or_terminator_index(map_runtime_state.index);
    if (map_runtime_state.state == 12) {
        s16 *current_sound;

        current_sound = town_saved_sound;
        town_entries = map_sound_settings;
        town_entry = town_entries + entry_index;
        town_effect = town_entry->unk6;
        current_sound[2] = town_effect;
        if ((s16)town_effect != -1) {
            select_sound_stream(town_entry->unk6, 0);
        }
        town_sequence = town_entry->unk8;
        current_sound[3] = town_sequence;
        if ((s16)town_sequence == -1) {
            return 1;
        }
        sequence = (u16)town_entry->unk8;
        sequence |= sequence_flags;
        sequence = (u16)sequence;
    } else {
        fallback_index = find_target_index_in_list();
        fallback_entries = fallback_sound_pairs;
        fallback_entry = fallback_entries + (fallback_index * 2);
        fallback_effect = fallback_entry[0];
        town_saved_sound[2] = fallback_effect;
        select_sound_stream((s16)fallback_effect, 0);
        fallback_sequence = fallback_entry[1];
        town_saved_sound[3] = fallback_sequence;
        sequence = fallback_sequence | sequence_flags;
        sequence = (u16)sequence;
                /* MATCH: Complete argument preparation before the shared call. */
    }
    SD_Call(sequence);
    return 1;
}

/* town_sd_sq_callagain: replay the town sequence with flags 0x9000. */
s32 town_sd_sq_callagain(void) {
    return town_sd_sq_callagain_sub(0x9000);
}
