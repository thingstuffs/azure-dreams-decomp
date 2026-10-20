#include "common.h"
#include "shared/sound_state.h"

/* extern decls for callees; sizes/types from asm inspection */
extern void func_8005CA70(void);
extern void audio_reset_all_voices(void);
extern void reset_sound_slots(void);
extern void func_8005D838(int count, void *record);


extern SoundSequenceListState D_80086CC0;

/* Resets sound state and slot tables, then initializes the record list at D_80086CC0. */
void audio_reset_sequence_subsystem(void)
{
    func_8005CA70();
    audio_reset_all_voices();
    reset_sound_slots();
    func_8005D838(0x10, &D_80086CC0);
}
