#ifndef SLUS_SAVED_VOLUME_SCALES_DATA_H
#define SLUS_SAVED_VOLUME_SCALES_DATA_H

#include "common.h"

/* Resident saved settings occupy consecutive words at 0x80080A94..0x80080A9F. */
extern s32 saved_cd_playback_volume_scale;
extern s32 saved_sequence_volume_scale;
extern s32 saved_voice_gain_scale;

#endif
