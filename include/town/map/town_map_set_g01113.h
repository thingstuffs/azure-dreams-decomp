#ifndef TOWN_MAP_TOWN_MAP_SET_G01113_H
#define TOWN_MAP_TOWN_MAP_SET_G01113_H

struct ObjectNodeHeader;
/* Town map set. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01113 - CL:town/func_8008E0B8. */

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
struct ObjectNodeHeader;

struct Rec_D_80081FDC;

struct Container;

struct Source;

extern s32 runtime_find_unused_pool_slot(void);
extern void runtime_clear_value(s32 *);
extern void *allocate_flagged_object_node(s32);
extern void unlink_active_node(s32);
extern void push_node_onto_free_list(struct ObjectNodeHeader *);
extern s8 town_map_link_slots[11];
void unlink_node_if_registered(void *block_data);
void copy_window_params(struct Container *, struct Source *);
void select_record_entry_and_value(void *, void *, s16);
s32 register_node(struct ObjectNodeHeader *entry, void *registration_id);
extern u8 town_map_tag;
extern u8 D_80037714;
extern u8 D_800794AC;
extern s32 town_map_selection;
extern M2C_UNK D_8008B9D8;
extern M2C_UNK D_8008BA00;
extern s32 D_800CFB74[];
extern u8 D_800CFC38[];
extern s32 D_800CFC44[];

/* Shared import declarations; data casts preserve each measured view. */
void runtime_initialize_state_value(struct Rec_D_80081FDC *, s32);
extern u8 town_map_status[];

/* Functions defined in this translation unit. */
s32 town_map_set(s32 value_7c, s32 value_78);
s32 town_map_del(void);
s32 clear_town_map_status(void);
void initialize_town_map_object_state(s32 type_id, s32 *init_value_ptr, void *object, void *context);

#endif
