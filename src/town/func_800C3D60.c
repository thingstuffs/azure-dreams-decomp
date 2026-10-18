#include "common.h"

typedef struct {
    u8 pad0[0x18];
    s16 state;
    s16 index;
} TownState;

typedef struct {
    s16 unk0;
    s16 effect;
    u16 sound;
    s16 unk6;
    s16 unk8;
} TownEntry;

extern TownState D_8006ADBC;
extern TownEntry D_800D4094[];

extern s32 find_sound_entry_or_terminator_index(s16 target_value);
extern void func_800540A8(void);
extern void audio_load_sound_effect_bank(s32 effect);
extern s16 SD_Call(s32 sound);

/* town_sd_se_callagain: replay the selected town entry's effect and sound when the town state is 12. */
s32 town_sd_se_callagain(void) {
    TownState *town_state;
    s32 entry_index;
    TownEntry *entries;
    TownEntry *entry;

    town_state = &D_8006ADBC;
    entry_index = find_sound_entry_or_terminator_index(town_state->index);
    func_800540A8();
    if (town_state->state == 12) {
        entries = D_800D4094;
        entry = &entries[entry_index];
        if (entry->effect != -1) {
            audio_load_sound_effect_bank(entry->effect);
        }
        if ((s16)entry->sound != -1) {
            SD_Call(entry->sound);
        }
    }
    return 1;
}
