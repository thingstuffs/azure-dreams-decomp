#include "common.h"
#include "shared/sound_state.h"
#include "engine/audio/sequence.h"
#include "engine/audio/slots.h"
#include "engine/audio/spu.h"
#include "slus.h"
#include "slus/data.h"

/* extern decls for callees; sizes/types from asm inspection */

/* Resets sound state and slot tables, then initializes the record list at D_80086CC0. */
void audio_reset_sequence_subsystem(void)
{
    reset_audio_sequence_state_default();
    audio_reset_all_voices();
    reset_sound_slots();
    initialize_sound_transfer_range(0x10, &spu_allocation_record_storage);
}
