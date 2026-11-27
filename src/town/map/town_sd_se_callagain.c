#include "slus/map_state.h"
#include "common.h"
#include "engine/audio.h"
#include "slus.h"
#include "town/map.h"
#include "town/map/sound_selection_g00648.h"

/* town_sd_se_callagain: replay the selected town entry's effect and sound when the town state is 12. */
s32 town_sd_se_callagain(void) {
    MapRuntimeState *town_state;
    s32 entry_index;
    TownEntry *entries;
    TownEntry *entry;

    town_state = &map_runtime_state;
    entry_index = find_sound_entry_or_terminator_index(town_state->map_index);
    reset_audio_command_state();
    if (town_state->scene_selector == 12) {
        entries = map_sound_settings;
        entry = &entries[entry_index];
        if ((s16)entry->sound_effect_bank != -1) {
            audio_load_sound_effect_bank((s16)entry->sound_effect_bank);
        }
        if ((s16)entry->sound_command != -1) {
            SD_Call(entry->sound_command);
        }
    }
    return 1;
}
