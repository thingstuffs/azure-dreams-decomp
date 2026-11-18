#ifndef DUNGEON_MONSTER_BELDO_COMMAND_TICKS_DATA_H
#define DUNGEON_MONSTER_BELDO_COMMAND_TICKS_DATA_H

#include "common.h"

struct ObjectNodeHeader;

typedef struct BeldoEffectScriptState {
    u8 pad_00[0xB8];
    s16 script_index;
    u8 script_active;
} BeldoEffectScriptState;

extern struct ObjectNodeHeader *beldo_active_entity;
extern u16 beldo_command_ticks;
extern u8 *beldo_effect_stream;
extern u8 *beldo_effect_scripts[3];

#endif
