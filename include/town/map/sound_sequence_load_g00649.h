#ifndef TOWN_MAP_SOUND_SEQUENCE_LOAD_G00649_H
#define TOWN_MAP_SOUND_SEQUENCE_LOAD_G00649_H
/* Sound sequence load (G00649). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C3E04, PD:town/engine:800D4244. */

#include "common.h"
#include "engine/audio.h"

extern s16 SD_Call(s32);


/* Functions defined in this translation unit. */
s32 tw_sd_sq_ld_call_sub(s32 sequence_id, s32 load_id, s32 load_flags);
void tw_sd_sq_ld_call(void *effect_id, void *effect_flags);

#endif
