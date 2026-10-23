#include "common.h"
#include "shared/sound_state.h"
#include "engine/audio/sequence.h"
#include "engine/audio/slots.h"
#include "engine/audio/spu.h"
#include "slus.h"
#include "slus/data.h"

/*
 * Resets sound state and slot tables, then initializes the record list at
 * spu_allocation_record_storage.
 *
 * extern decls for callees; sizes/types from asm inspection
 */
void audio_reset_sequence_subsystem(void)
{
    reset_audio_sequence_state_default();
    audio_reset_all_voices();
    reset_sound_slots();
    SpuInitMalloc(0x10, &spu_allocation_record_storage);
}
