#ifndef DUNGEON_OVL_199C800_H
#define DUNGEON_OVL_199C800_H
#include "modules/dungeon_native_abi.h"
#include "dungeon/actor/motion.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
struct Actor;
void build_and_enqueue_five_translucent_quads_between_interpolated_points(struct Actor *, ObjectPosition *, SpriteFrameState *);
void move_sprite_until_animation_ends(void *, ObjectPosition *, SpriteFrameState *);

#endif
