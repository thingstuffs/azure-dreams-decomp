#ifndef DUNGEON_OVL_18FA800_H
#define DUNGEON_OVL_18FA800_H
struct ObjectPosition;
#include "dungeon/effect.h"
#include "modules/dungeon_native_abi.h"
#include "shared/sprite_frame_state.h"
struct Unk818DAD38Owner;
struct Unk818DAD38Target;
void advance_target_growth_and_fade(struct Unk818DAD38Owner *, struct ObjectPosition *, SpriteFrameState *);
struct S_818DAE84_0;
void ramp_progress_value_over_countdown(struct S_818DAE84_0 *);
#endif
