#ifndef TOWN_SCENE_RESOURCE_RESOURCE_SLOTS_G00521_H
#define TOWN_SCENE_RESOURCE_RESOURCE_SLOTS_G00521_H
/* Resource slots shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8008DB84, CL:town/func_8008DBC8, CL:town/func_8008DC4C, PD:town/engine:800CF828, PD:town/engine:800CF838. */

#include "common.h"

extern u8 D_80080EA8[];
extern void file_load_com(void *object);

extern u8 town_resource_queue[15];
extern void *town_resource_descriptors[16];
s32 resource_value_table_contains(s32 target_value);

/* Functions defined in this translation unit. */
s32 has_listed_resource_in_slots(void);
s32 find_slot_for_resource_entry(void);
void reserve_twch_load(s32 character_id);
void func_8008B4B0(void);

#endif
