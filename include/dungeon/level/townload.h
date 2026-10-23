#ifndef DUNGEON_TOWN_LOAD_H
#define DUNGEON_TOWN_LOAD_H
#include "common.h"
#include "m2c_compat.h"
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
extern s32 town_resource_ids[];
extern u8 town_resource_queue[16];
extern s32 town_resource_descriptors[16];
extern u8 D_80080EA8[];
extern void file_load_com(s32);
s32 resource_value_table_contains(s32 value);
s32 has_listed_resource_in_slots(void);
s32 find_slot_for_resource_entry(void);
void reserve_twch_load(s32 entry_id);
void load_reserved_slot_resources(void);
#endif
