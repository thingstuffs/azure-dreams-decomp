#include "shared/entity.h"
#ifndef DUNGEON_OVL_7F43F800_P05_H
#define DUNGEON_OVL_7F43F800_P05_H
#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"











extern s32 rsin(s32 value);
struct SpriteFrameState;
extern void select_sprite_entry(void *, s16, s16);
extern void func_80047784(void *sprite, u8 value, s32 zero);
void set_record_integer_tile_center(ObjectPosition *record, s32 tile_x, s32 tile_y);
void spend_actor_mp(ActorRecord *entity, s32 base_reduction);
extern s16 get_rounded_facing_and_rounding_flag(u8 x0, u8 y0, u8 x1, u8 y1, s16 *scratch);

void on_actor_status_updated(void *actor);
void func_800A9A04(void *actor);
extern u8 D_80174EA8[];
extern u8 D_80174EB0[];
void update_timed_actor_movement_and_scale(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_behavior_and_direction(ActorRecord *motion, ObjectPosition *render_ctx, SpriteFrameState *map_entity, ActorRecord *actor);
#endif
