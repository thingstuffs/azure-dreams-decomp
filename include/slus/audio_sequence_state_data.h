#ifndef SLUS_AUDIO_SEQUENCE_STATE_DATA_H
#define SLUS_AUDIO_SEQUENCE_STATE_DATA_H

#include "common.h"

/* Resident count at 0x800869B4 and mode at 0x800869B8.
 * Their next link-map symbols are 0x800869B8 and 0x800869C0. */
extern s32 audio_sequence_track_count[];
extern s32 audio_sequence_multitrack_mode[];
/* Resident timing word at 0x800869A8; the mapped extent is not established. */
extern u32 audio_sequence_timing_division[];

#endif
