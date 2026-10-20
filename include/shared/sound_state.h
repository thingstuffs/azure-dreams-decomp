#ifndef SHARED_SOUND_STATE_H
#define SHARED_SOUND_STATE_H
#include "shared/sound_volume.h"
/* Opt-in declarations: older source views can coexist during partial apply.
 * Interior symbol aliases D_80084864 / D_80084904 are not allocation evidence. */
extern SoundPlaybackState sound_playback_state;
extern SoundTask sound_stream_task;
extern SoundTask sound_sequence_task;
/* The standalone +0x0C alias keeps its own relocation identity. Only word 0
 * is observed. An unsized word declaration preserves absolute addressing;
 * no array/allocation extent is claimed. */
extern int sound_stream_task_word[];

/* Exact access views shared across registered binary consumers. */
/* Three-word sound sequence list state rooted at D_80086CC0. */
typedef struct SoundSequenceListState {
    int unk0;
    int unk4;
    int unk8; /* Retains the original third word and twelve-byte extent. */
} SoundSequenceListState;

#endif
