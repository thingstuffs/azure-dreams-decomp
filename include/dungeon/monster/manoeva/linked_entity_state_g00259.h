#ifndef DUNGEON_MONSTER_MANOEVA_LINKED_ENTITY_STATE_G00259_H
#define DUNGEON_MONSTER_MANOEVA_LINKED_ENTITY_STATE_G00259_H
#include "dungeon/player/object.h"
#include "engine/entity.h"

struct ObjectNodeHeader;
/* Transfers state between linked objects and initializes or resets Manoeva's action state. */

#include "common.h"
#include "dungeon/item/actor_target.h"
#include "dungeon/actor.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/game_work.h"

/* arg0 in reset_linked_entity_state */

extern void copy_entity_record(void *, void *);
extern void insert_node_before_primary_actor(struct ObjectNodeHeader *);
extern u8 *find_monster_entry_by_type_and_id(s32, s32); /* Unprototyped: retail call narrows its arguments to this declaration; no shared prototype keeps it */

extern void select_sprite_entry(void *object, s16 table_index, s16 entry_index);
#include "dungeon/player/object/action_state.h"
#include "shared/sprite_frame_state.h"
extern u8 D_80176670[16];

/* Functions defined in this translation unit. */
void transfer_linked_object_state(ActorRecord *owner, ObjectPosition *object_id, SpriteFrameState *dest_object, ActorRecord *dest_state);
void initialize_object_and_clear_state(ActorRecord *action, ObjectPosition *unused, SpriteFrameState *animation, ActorRecord *entity);
void reset_linked_entity_state(ActorRecord *state, ObjectPosition *unused, SpriteFrameState *flag_record, ActorRecord *record);

#endif
