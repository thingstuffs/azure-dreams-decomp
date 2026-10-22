#ifndef DUNGEON_ACTOR_MOVEMENT_OVERLAP_WAIT_G00334_H
#define DUNGEON_ACTOR_MOVEMENT_OVERLAP_WAIT_G00334_H

struct SpriteFrameState;
/* Movement overlap wait shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800A4DA8. */

#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern u32 has_pending_dungeon_activity(void *entity);
extern s32 update_object_coordinates_if_valid(struct SpriteFrameState *object, void *context);
extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, s32 flag_mask);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void begin_actor_random_warp(void *entity, void *unused, void *position, void *entity_state);

/* Functions defined in this translation unit. */
s32 try_move_actor_to_valid_position(void *action, void *context, void *position, void *entity);
void begin_actor_overlap_wait(void *entity, void *unused_1, void *unused_2, void *unused_3);

#endif
