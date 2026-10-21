#ifndef TOWN_MAP_SOUND_SEQUENCE_REPLAY_G00650_H
#define TOWN_MAP_SOUND_SEQUENCE_REPLAY_G00650_H
/* Sound sequence replay (G00650). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C3E80. */

#include "common.h"

typedef struct {
    u8 pad0[0x18];
    s16 state;
    s16 index;
} TownState;

extern TownState D_8006ADBC;
extern u8 D_800D4094[];
extern u16 D_800D4244[];
extern u16 D_800D4268[];
extern s32 find_sound_entry_or_terminator_index(s16 target_value);
extern s32 find_target_byte_index_in_list(void);
extern void select_sound_stream(s32 effect, s32 value);
extern s16 SD_Call(s32);


/* Functions defined in this translation unit. */
s32 town_sd_sq_callagain_sub(s32 sequence_flags);
void town_sd_sq_callagain(void);

#endif
