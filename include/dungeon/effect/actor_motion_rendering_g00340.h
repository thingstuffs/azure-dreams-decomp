#ifndef DUNGEON_EFFECT_ACTOR_MOTION_RENDERING_G00340_H
#define DUNGEON_EFFECT_ACTOR_MOTION_RENDERING_G00340_H
/* Actor motion rendering shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800ACDDC. */

#include "common.h"
#include "dungeon/actor.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

#include "dungeon/actor/callback.h"

#include "dungeon/player/object/action_state.h"

extern void initialize_actor_object_action(void *object_state, s32 unused_context, s32 properties, void *status);
extern s16 pending_marked_actor_count;
extern ActorCallback actor_render_callbacks[];
extern void apply_monster_koyaw_data(void *, void *);
extern s16 sample_terrain_surface_height(u16, u16, s16);

/* Functions defined in this translation unit. */
void update_pending_entity_action(Rec_func_800A9E70_arg0 *actor, s32 update_arg1, s32 update_arg2, EntityRec *entity);
void update_actor_motion_and_rendering(u8 *actor, u8 *motion, u8 *render);

#endif
