#ifndef DUNGEON_MONSTER_MANOEVA_LINKED_ENTITY_STATE_G00259_H
#define DUNGEON_MONSTER_MANOEVA_LINKED_ENTITY_STATE_G00259_H
#include "dungeon/player/object.h"
#include "engine/entity.h"

struct ObjectNodeHeader;
/* Linked entity state shared declarations (G00259). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00259 - CL:dungeon/func_80E3A540@dungeon/bank_e56c58, CL:dungeon/func_80E3A540@dungeon/bank_e5d000, CL:dungeon/func_80E3A540@dungeon/bank_e63000, CL:dungeon/func_80E3A540@dungeon/bank_e69000, CL:dungeon/func_80E3A540@dungeon/bank_e6f000, CL:dungeon/func_80E3A540@dungeon/bank_e75000. */

#include "common.h"
#include "dungeon/actor.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/game_work.h"

/* arg0 in reset_linked_entity_state */

extern void copy_entity_record(void *, void *);
extern void clear_entry_flag_and_link_owner(struct ObjectNodeHeader *);
extern u8 *find_monster_entry_by_type_and_id(s32, s32); /* Unprototyped: retail call narrows its arguments to this declaration; no shared prototype keeps it */
extern s32 find_linked_object_slot_index(void *);

extern void select_sprite_entry(void *object, s16 table_index, s16 entry_index);
#include "dungeon/player/object/action_state.h"
#include "shared/sprite_frame_state.h"
extern u8 D_80176670[16];

/* Functions defined in this translation unit. */
void transfer_linked_object_state(ActorRecord *owner, ObjectPosition *object_id, SpriteFrameState *dest_object, ActorRecord *dest_state);
void initialize_object_and_clear_state(ActorRecord *action, ObjectPosition *unused, SpriteFrameState *animation, ActorRecord *entity);
void reset_linked_entity_state(ActorRecord *state, ObjectPosition *unused, SpriteFrameState *flag_record, ActorRecord *record);

#endif
