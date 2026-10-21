#include "common.h"
#include "shared/sys_flags.h"
#include "shared/transition_slots.h"
#include "engine/audio.h"
#include "engine/scene.h"
#include "slus.h"
#include "slus/data.h"

extern int sprite_resource_pointer_slots[4];

/* Clears global state blocks and a flag, then reinitializes subsystem defaults. */
void reset_runtime_slot_state(void)
{
    s32 word_index;

    zero_words((int *)runtime_transition_slots, 0x10);
    zero_words(vram_row_upload_cache, 0x80);

    {
        int *state_words = sprite_resource_pointer_slots;
        for (word_index = 3; word_index >= 0; word_index--) {
            *(state_words + word_index) = 0;
        }
    }

    system_update_flags = 0;

    invalidate_four_sprite_resource_slots();
    select_sound_stream(0x2A, 0);
    audio_load_sound_effect_bank(0);
}
