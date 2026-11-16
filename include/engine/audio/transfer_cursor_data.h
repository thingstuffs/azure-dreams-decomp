#ifndef ENGINE_AUDIO_TRANSFER_CURSOR_DATA_H
#define ENGINE_AUDIO_TRANSFER_CURSOR_DATA_H

#include "common.h"

/* The transfer offset occupies the first word of this 12-byte sound-slot state. */
typedef struct {
    s32 value;
    s32 reserved[2];
} SoundSlotTransferCursor;

extern SoundSlotTransferCursor sound_slot_transfer_cursor;

#endif
