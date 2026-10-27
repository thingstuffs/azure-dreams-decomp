#ifndef ENGINE_AUDIO_COMMANDS_H
#define ENGINE_AUDIO_COMMANDS_H

#include "common.h"

/* Count halfword followed by 32 queued command halfwords. */
extern u16 audio_command_queue[33];

s32 pop_audio_queue(void);
void clear_audio_command_queue(void);
void dispatch_audio_command(s32 code);

#endif
