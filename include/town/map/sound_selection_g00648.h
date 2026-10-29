#ifndef TOWN_MAP_SOUND_SELECTION_G00648_H
#define TOWN_MAP_SOUND_SELECTION_G00648_H
/* Sound selection (G00648). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C3884, CL:town/func_800C38D4, PD:town/engine:800D4244, PD:town/engine:800D4260. */

#include "common.h"

typedef struct {
    s16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    s16 unk8;
} TownEntry;

typedef struct {
    u8 pad[0x18];
    s16 field18;
    s16 field1A;
} GlobalState;

extern u16 fallback_sound_pairs[];
extern s16 map_scene_selector_alias;
extern u8 D_800D0004[];
/* Ten-byte records terminated by a zero key; upper bound is not inferred. */
extern TownEntry map_sound_settings[];
extern s16 town_saved_sound[];
extern u8 D_80110004[];
extern s16 D_80113200[];
extern s32 find_sound_entry_or_terminator_index(s32 target_value);
extern GlobalState map_runtime_state;
extern s16 town_pending_sound[];
extern s16 town_sound_selection[];
extern void audio_load_sound_effect_bank(s32 record_id);
extern void load_sound_set(s32 state_index);
extern void drain_audio_commands_and_service_channels(void);
extern s32 select_sound_stream(s16 entry_index, s16 mode);
extern s8 scene_music_hold[];
extern s16 town_sound_command[];
extern s16 town_stream_index[];
extern s16 town_sequence_command[];

extern s16 SD_Call(s32 flags);
/* Functions defined in this translation unit. */
void copy_selected_sound_pair(void *output);
s16 *build_four_value_entry_result(s32 unused, s32 index);
void load_pending_sound_record(void);
void apply_sound_selections_and_update(void);

#endif
