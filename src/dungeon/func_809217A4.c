#include "common.h"

extern void play_sound_if_enabled(s32);
extern s8 D_800DCF4D;

/* Calls play_sound_if_enabled with 180 and sets D_800DCF4D to -1. */
void play_transition_sound_and_reset_status(void)
{
    play_sound_if_enabled(0xB4);
    D_800DCF4D = -1;
}
