/* Sound sequence load (G00649). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C3E04, PD:town/engine:800D4244. */
#include "town/map/sound_sequence_load_g00649.h"
#include "town/map.h"

/* tw_sd_sq_ld_call_sub: load a nonzero sequence and submit the flagged load ID. */
s32 tw_sd_sq_ld_call_sub(s32 sequence_id, s32 load_id, s32 load_flags) {
    if (sequence_id != 0) {
        select_sound_stream(sequence_id, 0);
    }
    if (load_id != 0) {
        SD_Call((load_id | load_flags) & 0xFFFF);
    }
    return 1;
}

/* tw_sd_sq_ld_call: apply town sequence effects without additional flags. */
void tw_sd_sq_ld_call(s32 effect_id, s32 effect_flags) {
    tw_sd_sq_ld_call_sub(effect_id, effect_flags, 0);
}
