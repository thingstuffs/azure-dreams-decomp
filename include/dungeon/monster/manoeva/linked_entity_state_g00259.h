#ifndef DUNGEON_MONSTER_MANOEVA_LINKED_ENTITY_STATE_G00259_H
#define DUNGEON_MONSTER_MANOEVA_LINKED_ENTITY_STATE_G00259_H

struct ObjectNodeHeader;
/* Linked entity state shared declarations (G00259). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00259 - CL:dungeon/func_80E3A540@dungeon/bank_e56c58, CL:dungeon/func_80E3A540@dungeon/bank_e5d000, CL:dungeon/func_80E3A540@dungeon/bank_e63000, CL:dungeon/func_80E3A540@dungeon/bank_e69000, CL:dungeon/func_80E3A540@dungeon/bank_e6f000, CL:dungeon/func_80E3A540@dungeon/bank_e75000. */

#include "common.h"
#include "dungeon/actor.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/game_work.h"

typedef struct S_80173C40_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_80173C40_2;

typedef struct S_80173D40_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_80173D40_0;

/* arg0 in reset_linked_entity_state */
typedef struct S_80173D40_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80173D40_1;

extern void copy_entity_record(void *, void *);
extern s32 get_entity_effect_value(void *, s32);
extern void clear_entry_flag_and_link_owner(struct ObjectNodeHeader *);
extern u8 *find_monster_entry_by_type_and_id(s32, s32);
extern s32 find_entity_slot_by_field_ac(void *);
extern void set_record_integer_tile_center(s32, s32, s32);

extern void select_sprite_entry();
#include "dungeon/player/object/action_state.h"
extern u8 D_80176670[16];

/* Functions defined in this translation unit. */
void transfer_linked_object_state(u8 *owner, s32 object_id, u8 *dest_object, u8 *dest_state);
void initialize_object_and_clear_state(void *action, void *unused, void *animation, EntityRec *entity);
void reset_linked_entity_state(S_80173D40_0 *state, s32 unused, S_80173D40_1 *flag_record, EntityRec *record);

#endif
