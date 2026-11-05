#ifndef TOWN_SHOP_TWIN_STORAGE_INITIALIZATION_G00618_H
#define TOWN_SHOP_TWIN_STORAGE_INITIALIZATION_G00618_H
/* Twin storage initialization declarations (G00618). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B5270, CL:town/func_800B52D8, CL:town/func_800B5400, CL:town/func_800B550C. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "town/shop/resource_entry_initialization_g01156.h"
#include "town/shop/group_index.h"

/* extern */

typedef struct S_800B2BA0_1 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_800B2BA0_1;

s32 func_800B0718();
/* extern */
/* extern */
/* extern */
s32 func_800B3924();
/* extern */
StorageMenuNode *create_storage_item_menu();
/* extern */
StorageMenuNode *create_storage_owner_menu();
/* extern */
void handle_item_menu_input_2(u8 *menu);
extern void fill_item_value_buffer(ItemMenuInputObject *table);
extern void func_800B3A80(s32);
extern void refresh_object_components_and_high_flag(u8 *object);
extern void process_object_resources_and_high_flag(u8 *object);

s32 obj_disp23_cancel_sw_set(s32 cancel_switch);
void came_bright_set(u32 brightness);

/* Functions defined in this translation unit. */
void initialize_record_table_and_group(ItemMenuInputObject *record);
void *open_twin_souko(s32 option);
void apply_record_values_and_process_record(ItemMenuInputObject *record);

#endif
