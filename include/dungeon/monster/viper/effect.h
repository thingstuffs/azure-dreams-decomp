#ifndef INCLUDE_DUNGEON_MONSTER_VIPER_EFFECT_H
#define INCLUDE_DUNGEON_MONSTER_VIPER_EFFECT_H

#include "common.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "records/Rec_func_800AA258_arg2.h"

/* Timed visual state shared by the item-grab effect creator and its callback. */
typedef struct ViperTimedEffectBody {
    u8 pad_00[0x96];
    union { u16 s; s16 u; } timer;
    u8 pad_98[0x3];
    u8 state;
} ViperTimedEffectBody;

typedef struct ViperTimedEffectNode {
    ObjectNodeHeader header;
    ViperTimedEffectBody body;
} ViperTimedEffectNode;

void update_timed_effect_size_and_position(ViperTimedEffectBody *effect, ObjectPosition *position, Rec_func_800AA258_arg2 *visual, void *unused_actor);

#endif
