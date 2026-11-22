#ifndef TOWN_SHOP_RESOURCE_ENTRY_INITIALIZATION_G01156_H
#define TOWN_SHOP_RESOURCE_ENTRY_INITIALIZATION_G01156_H
/* resource entry initialization g01156. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_800B5204, CL:town/func_800B5270, CL:town/func_800B52D8, CL:town/func_800B5400, CL:town/func_800B550C. */

/* Resource entry initialization. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B5204. */
/* Resource entry initialization declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B5204. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "shared/item_menu.h"
#include "town/shop/storage_menu.h"
#include "town/shop/item_menu_actions.h"
#include "town/shop/group_index.h"

typedef struct S_800B2BA0_1 {
    u8 pad_00[0x20];
    ItemMenuObjectNode *unk_20;
} S_800B2BA0_1;

typedef struct ItemMenuInputObject {
    ItemMenuObjectNode *item_menu_object;
    StorageMenuNode *source_menu;
    StorageMenuNode *destination_menu;
    s32 preset;
    s32 input_repeat_ticks;
    s32 source_index;
    s32 destination_index;
    TownGroupIndex groups[2];
    DungeonItemEntry **lists[2]; /* carried slots followed by the storage pointer list */
    s32 count;
    s32 option;
} ItemMenuInputObject;

/* extern */
extern void flag_object_for_removal(unsigned short *object);
s32 func_800B0718(void);
/* extern */
/* extern */
/* extern */
/* extern */
/* extern */
void handle_item_move_menu_input(ItemMenuInputObject *menu);
extern void func_800B3A80(s32);
extern void release_storage_item_menu(StorageMenuNode *object);
extern void release_storage_owner_menu(StorageMenuNode *object);
s32 obj_disp23_cancel_sw_set(s32 cancel_switch);
void came_bright_set(u32 brightness);

/* Functions defined in this translation unit. */
void collect_enabled_entry_pointers(DungeonItemEntry **entries, s32 entry_count);
s32 count_nonzero_entries(DungeonItemEntry **entries);
DungeonItemEntry **allocate_item_pointer_list(ItemMenuInputObject *state);
void write_back_item_table(ItemMenuInputObject *table);
void init_item_list_group(ItemMenuInputObject *record);
void * open_twin_souko(s32 option);

#endif
