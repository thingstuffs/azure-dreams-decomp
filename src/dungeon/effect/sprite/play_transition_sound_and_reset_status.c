#include "shared/audio_commands.h"
#include "common.h"

extern void play_sound_if_enabled(s32);
extern s8 spell_effect_selector_cache;

/* Requests AUDIO_FADE_CD_FAST and invalidates spell_effect_selector_cache with -1. */
void play_transition_sound_and_reset_status(void)
{
    play_sound_if_enabled(AUDIO_FADE_CD_FAST);
    spell_effect_selector_cache = -1;
}
