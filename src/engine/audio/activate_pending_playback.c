#include "shared/sound_state.h"
#include "common.h"
#include "engine/audio.h"




/* Activates and clears pending state, rearms the counter and timer, and clears status flags. */
void activate_pending_playback(void) {
    SoundPlaybackState *state = &sound_playback_state;
    u32 pending_word_a = state->pending_start_sector;
    u32 pending_word_b = state->pending_end_sector;
    u8 pending_byte_a = ((u8)state->pending_xa_channel);
    u8 pending_byte_b = ((u8)state->pending_xa_file);

    state->pending_start_sector = 0;
    state->pending_end_sector = 0;
    state->pending_xa_channel = 0;
    state->pending_xa_file = 0;

    sound_stream_task.ramp_mode = 3;
    sound_stream_task.ramp_level = 0x80;

    state->stream_start_sector = pending_word_a;
    state->stream_end_sector = pending_word_b;
    state->stream_xa_channel = pending_byte_a;
    state->stream_xa_file = pending_byte_b;

    state->flags00 &= ~0x400;
    state->flags00 &= ~0x4000;
    state->flags04 &= ~0x200;
}
