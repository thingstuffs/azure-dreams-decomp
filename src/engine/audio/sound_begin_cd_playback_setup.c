#include "shared/sound_state.h"
#include "common.h"
#include "engine/audio.h"
#include "slus.h"

/* Canonical status-block struct shared across the D_800847D0 family (see
   w_800552C8.c, w_80054C58.c, w_800540A8.c, w_80054E00.c). field2C/field2D
   are added here (previously unnamed pad bytes) since this function is the
   one that reads/writes them directly. */

/* Opaque scalar flag; only its value is ever stored (never dereferenced
   beyond a single s32 write elsewhere). Padded >8 bytes to force %hi/%lo
   addressing (matches src/w_80054E00.c's S_80084904). */
typedef struct S_80084904 {
    /* 0x00 */ s32 v;
    /* 0x04 */ u8 pad4[8];
} S_80084904;

extern S_80084904 audio_sequence_task_mode;

/* Enters mode 2, activates pending status fields, resets subsystems, and registers status callbacks. */
void sound_begin_cd_playback_setup(void) {
    SoundPlaybackState *status;
    u8 pending_2c;
    u8 pending_2d;

    audio_sequence_task_mode.v = 2;

    status = &sound_playback_state;
    pending_2c = status->unk_32;
    pending_2d = status->unk_30;

    status->unk_2C = pending_2c;
    status->unk_2D = pending_2d;
    status->flags04 |= 0x200;

    submit_tagged_driver_byte(0, 0, 0);
    submit_scaled_driver_halfword_pair(0, 0, 0);
    Control_CD(0xE, 0, &status->unk_28);
    Control_CD(0xD, (void *)(s32) status->unk_08, &status->unk_2C);
}
