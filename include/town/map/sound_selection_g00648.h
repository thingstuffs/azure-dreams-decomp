#ifndef TOWN_MAP_SOUND_SELECTION_G00648_H
#define TOWN_MAP_SOUND_SELECTION_G00648_H
/* Sound selection. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C3884, CL:town/func_800C38D4, PD:town/engine:800D4244, PD:town/engine:800D4260. */

#include "common.h"
#include "town/map/saved_sound_data.h"
#include "town/map/sound_settings_data.h"

typedef struct {
    u8 pad[0x18];
    s16 field18;
    s16 field1A;
} GlobalState;

extern u16 fallback_sound_pairs[];
extern s16 map_scene_selector_alias;
extern u8 D_800D0004[];
extern u8 D_80110004[];
extern s16 D_80113200[];
extern s32 find_sound_entry_or_terminator_index(s32 target_value);
extern GlobalState map_runtime_state;
extern s16 town_pending_sound[];
extern s16 town_sound_selection[];
extern s8 scene_music_hold[];
extern s16 town_sound_command[];
extern s16 town_stream_index[];
extern s16 town_sequence_command[];

extern s16 SD_Call(s32 flags);
/* Functions defined in this translation unit. */
void copy_selected_sound_pair(void *output);
void load_town_sound_selection(void);
void apply_town_sound_selection(void);

#endif
