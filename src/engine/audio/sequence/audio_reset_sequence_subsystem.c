#include "common.h"
#include "shared/sound_state.h"

/* extern decls for callees; sizes/types from asm inspection */
extern void reset_audio_sequence_state_default(void);
extern void audio_reset_all_voices(void);
extern void reset_sound_slots(void);
extern void initialize_sound_transfer_range(int count, void *record);


extern SoundSequenceListState spu_allocation_record_storage;

/* Resets sound state and slot tables, then initializes the record list at D_80086CC0. */
void audio_reset_sequence_subsystem(void)
{
    reset_audio_sequence_state_default();
    audio_reset_all_voices();
    reset_sound_slots();
    initialize_sound_transfer_range(0x10, &spu_allocation_record_storage);
}
