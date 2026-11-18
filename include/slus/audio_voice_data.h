#ifndef SLUS_AUDIO_VOICE_DATA_H
#define SLUS_AUDIO_VOICE_DATA_H

#include "common.h"
#include "shared/spu_voice.h"

/* Resident SLUS voice counts, masks, and current SPU request. */
extern s32 audio_voice_count[4];
extern s32 audio_voice_masks[24];
extern SpuVoiceAttr_ audio_voice_request;

#endif
