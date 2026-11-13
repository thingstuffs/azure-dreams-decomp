#ifndef SLUS_GP_AF3_PAIR_H
#define SLUS_GP_AF3_PAIR_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "slus/gpu_scratch_data.h"

/* S_8006E704: array of pointers to a small struct whose only field this
 * function touches is a packed 32-bit "color/mode" word at offset 0 (top 9
 * bits = category, low 23 bits = an id taken from the ADDRESS of one of two
 * marker tables D_801C4640 / D_801BEE40, mirroring the func_8003F6D4 pack
 * idiom: (cat<<23) | (id & 0x7FFFFF)). */
typedef struct S_8006E704 {
    s32 field_0;
} S_8006E704;

extern S_8006E704 *sound_stream_resource_entries[];
/* S_80080AF3 : a single scalar byte, gp-relative (<=8B). Kept a plain scalar
 * (not wrapped in a struct) because this function's only access is a bare
 * lb of the symbol itself, with no offset. */
extern s8 sound_stream_state_index;
/* D_80080AF4: 2-entry array of pointers into D_8006E704's entries, indexed by
 * the "current"/"toggled" slot selector D_80080AFC (0 or 1). Its TRUE finite
 * size (2, not an oversized/incomplete decl) is load-bearing for codegen --
 * see globals/learnings. */
extern S_8006E704 *sound_stream_buffer_entries[2];
/* Declared oversized (>8B) so their ADDRESS is taken via %hi/%lo, matching
 * the target's lui/addiu pair (their contents are never dereferenced --
 * only the low 23 bits of the address itself are used as a packed id). */
extern s32 sound_stream_secondary_marker_address[4];
extern s32 sound_stream_primary_marker_address[4];

extern void drain_audio_commands_and_service_channels(void);
extern void wait_until_sound_idle(void);
extern s32 load_sound_set(s16 state_index);

/* Selects a buffered entry, registering it with the slot marker and applying the requested mode. */

/* S_8006E6F4: array of 8-byte entries, indexed by state; forces %hi/%lo
 * addressing (accessed with a computed base + reused offsets). */
typedef struct {
    void *field0; /* first sound-set CD descriptor */
    void *field4; /* companion sound-set CD descriptor */
} S_8006E6F4;
extern S_8006E6F4 sound_set_resources[];

extern s16 test_sound_channel_availability(s16 n);

/* Register callbacks and complete a state transition, returning 1 if already current. */

s32 select_sound_stream(s16 entry_index, s16 mode);
s32 func_8004437C(s16 entry_index, s16 mode);

#endif
