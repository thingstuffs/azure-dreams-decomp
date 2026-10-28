#include "shared/sound_state.h"
#include "common.h"
#include "slus.h"

/* Canonical status block shared across the D_800847D0 family (see w_8005405C.c etc). */

extern void *audio_staging_destinations[];
extern u32 audio_staging_spu_offsets[];
extern void *audio_bank_owner_payloads[];

extern s32 init_sound_slot_from_header(void *header, s16 requested_slot, u32 spu_addr);
extern s32 bind_sound_slot_owner(void *a0, s32 a1);
extern void release_enabled_sound_channel(s32 a0);
extern void sound_check_or_wait_for_spu_transfer(s32 a0);

/* Initializes an entry, marking it available on success or reporting an error on failure. */
void sound_load_pending_bank_slot(s16 entry_id) {
    s32 entry_index = entry_id;
    s32 index_or_error;
    index_or_error = entry_index;
    if ((s16)init_sound_slot_from_header(audio_staging_destinations[index_or_error], index_or_error, audio_staging_spu_offsets[index_or_error]) == -1) {
        index_or_error = 0x01010000;
        identity_int(((entry_index << 8) & 0xFF00) | index_or_error);
    } else if ((s16)bind_sound_slot_owner(audio_bank_owner_payloads[index_or_error], entry_index) == -1) {
        release_enabled_sound_channel(index_or_error);
        index_or_error = 0x01020000;
        identity_int(((entry_index << 8) & 0xFF00) | index_or_error);
    } else {
        sound_check_or_wait_for_spu_transfer(1);
        sound_playback_state.flags00 |= (0x10000 << entry_index);
    }
}
