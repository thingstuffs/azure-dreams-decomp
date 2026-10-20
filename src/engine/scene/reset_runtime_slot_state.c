#include "common.h"
#include "shared/sys_flags.h"
#include "shared/transition_slots.h"

extern int vram_row_upload_cache[128];
extern int D_80083110[4];

extern void zero_words(int *p, int n);
extern void invalidate_four_sprite_resource_slots(void);
extern void select_sound_stream(s32 a0, s32 a1);
extern void audio_load_sound_effect_bank(s32 a0);

/* Clears global state blocks and a flag, then reinitializes subsystem defaults. */
void reset_runtime_slot_state(void)
{
    s32 word_index;

    zero_words((int *)runtime_transition_slots, 0x10);
    zero_words(vram_row_upload_cache, 0x80);

    {
        int *state_words = D_80083110;
        for (word_index = 3; word_index >= 0; word_index--) {
            *(state_words + word_index) = 0;
        }
    }

    D_80013714 = 0;

    invalidate_four_sprite_resource_slots();
    select_sound_stream(0x2A, 0);
    audio_load_sound_effect_bank(0);
}
