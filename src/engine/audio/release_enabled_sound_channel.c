#include "shared/sound_state.h"
#include "common.h"

/* Canonical status-block struct at D_800847D0 (established elsewhere in the codebase:
   w_800540A8.c / w_80054C58.c / w_8005405C.c / w_800559B4.c / w_800552C8.c). */


extern void handle_audio_status_code(s32 a0);
extern void free_sound_slot(s16 a0);

/* Releases an available channel, stopping channel zero's note when its status requires it. */
void release_enabled_sound_channel(s16 channel) {
    s16 channel_index = channel;
    SoundPlaybackState *status = &D_800847D0;
    if (status->flags00 & (0x10000 << channel_index)) {
        if (channel_index == 0) {
            if (status->flags00 & 0x100) {
                handle_audio_status_code(0x71);
                status->unk_26 = -1;
            }
        }
        free_sound_slot((s16) channel);
        D_800847D0.flags00 &= ~(0x10000 << ((s16) channel));
    }
}
