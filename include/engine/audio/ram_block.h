#ifndef ENGINE_AUDIO_RAM_BLOCK_H
#define ENGINE_AUDIO_RAM_BLOCK_H

#include "common.h"

/* Sixteen SPU RAM reservations, sorted by byte address. The table has an
 * eight-byte stride; address zero marks the end of the occupied prefix. */
typedef struct SoundRamBlock {
    union { s32 s; u32 u; } address;
    s32 size;
} SoundRamBlock;

extern SoundRamBlock audio_ram_blocks[16];

#endif
