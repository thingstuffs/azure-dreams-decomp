#include "common.h"
#include "shared/sys_flags.h"
#include "shared/transition_slots.h"

extern int D_80082EC0[128];
extern int D_80083110[4];

extern void zero_words(int *p, int n);
extern void func_800499BC(void);
extern void func_8004437C(s32 a0, s32 a1);
extern void audio_load_sound_effect_bank(s32 a0);

/* Clears global state blocks and a flag, then reinitializes subsystem defaults. */
void reset_runtime_slot_state(void)
{
    s32 word_index;

    zero_words((int *)D_80083120, 0x10);
    zero_words(D_80082EC0, 0x80);

    {
        int *state_words = D_80083110;
        for (word_index = 3; word_index >= 0; word_index--) {
            *(state_words + word_index) = 0;
        }
    }

    D_80013714 = 0;

    func_800499BC();
    func_8004437C(0x2A, 0);
    audio_load_sound_effect_bank(0);
}
