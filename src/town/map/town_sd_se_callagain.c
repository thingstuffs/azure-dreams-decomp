#include "common.h"
#include "engine/audio.h"
#include "slus.h"
#include "town/map.h"
#include "town/map/sound_selection_g00648.h"

/* town_sd_se_callagain: replay the selected town entry's effect and sound when the town state is 12. */
s32 town_sd_se_callagain(void) {
    GlobalState *town_state;
    s32 entry_index;
    TownEntry *entries;
    TownEntry *entry;

    town_state = &map_runtime_state;
    entry_index = find_sound_entry_or_terminator_index(town_state->field1A);
    reset_audio_command_state();
    if (town_state->field18 == 12) {
        entries = map_sound_settings;
        entry = &entries[entry_index];
        if ((s16)entry->unk2 != -1) {
            audio_load_sound_effect_bank((s16)entry->unk2);
        }
        if ((s16)entry->unk4 != -1) {
            SD_Call(entry->unk4);
        }
    }
    return 1;
}
