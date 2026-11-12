#ifndef DUNGEON_EFFECT_EMISSION_DATA_H
#define DUNGEON_EFFECT_EMISSION_DATA_H

#include "common.h"

/* Resident effect counter at 0x80094422. */
extern u16 emitted_effect_counter;

/* Byte lookup by emitter kind at 0x800E0F20; allocation extent is unconfirmed. */
extern u8 emitter_height_offsets[];

#endif
