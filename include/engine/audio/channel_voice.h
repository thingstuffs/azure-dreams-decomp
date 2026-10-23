#ifndef INCLUDE_ENGINE_AUDIO_CHANNEL_VOICE_H
#define INCLUDE_ENGINE_AUDIO_CHANNEL_VOICE_H

#include "common.h"

/* The K&R definition consumes halfwords; its public argument types are
 * the default-promoted int types. The slot allocator narrows the return. */
s32 start_voice_on_channel(s32 channel, s32 bank, s32 program, s32 tone, s32 note, s32 fine_note, s32 left_gain, s32 right_gain);

#endif
