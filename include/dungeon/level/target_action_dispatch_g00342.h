#ifndef DUNGEON_LEVEL_TARGET_ACTION_DISPATCH_G00342_H
#define DUNGEON_LEVEL_TARGET_ACTION_DISPATCH_G00342_H
/* Target action dispatch shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:dungeon/engine:800DF258. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct {
    u8 field0;
    u8 field1;
    u8 field2;
    u8 field3;
} D_800E3648_entry;

typedef struct {
    u8 pad0[6];
    s8 field6;
    s8 field7;
    u32 field8;
    s32 fieldC;
    s16 field10;
    u8 pad12[2];
    s16 field14;
    u8 pad16[2];
} D_800E39C8_entry;

typedef s32 (*D_800DF2A8_fn)(void *, s16, s32);

typedef struct {
    u8 pad[0x14];
    u16 flags;
    u8 pad2[2];
} StatusEntry;

typedef struct {
    u8 pad[0x5C];
    s32 unk5C;
} Arg1Struct;

s32 find_entry_at_tile_coordinates(s16 x, s16 y, s16 z);
/* extern */
/* extern */
void clear_slot_and_detach_entity(s32 slot_index);
/* extern */
#include "dungeon/actor/status.h"
extern s32 get_entity_effect_value(void *entry, s32 effect_id);
extern void clear_slots_of_type(void *object, s32 value);
extern void adjust_source_value_and_finalize(void *context, const void *source);
extern s8 D_800E0DF5[];
extern D_800DF2A8_fn D_800DF2A8[];
extern u8 trap_request_blocked[16];
extern void process_unflagged_linked_entries_alt(s32);
extern void process_unflagged_linked_entries(s32);
extern void select_record_entry_and_value(void *state, void *entries, short index);

extern u8 floor_objects[16];
extern s32 floor_object_sprite_sources[16];
extern D_800E39C8_entry dungeon_floor_object_positions[];

/* Functions defined in this translation unit. */
s32 select_and_initialize_entry_at_position(s16 x, s16 y, s16 z, s32 type_id, s32 entry_value);
s32 process_target_with_action_seven(void *target);
s32 handle_type_two_query_result(void *object);
s32 call_slot_handler_and_update_status(s32 handler_id, void *object_ptr, s32 slot_id, s8 update_state);

#endif
