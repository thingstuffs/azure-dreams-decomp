#ifndef TOWN_SHOP_TWIN_STORAGE_INITIALIZATION_G00618_H
#define TOWN_SHOP_TWIN_STORAGE_INITIALIZATION_G00618_H
/* Twin storage initialization declarations (G00618). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B5270, CL:town/func_800B52D8, CL:town/func_800B5400, CL:town/func_800B550C. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "town/shop/resource_entry_initialization_g01156.h"

/* extern */
struct TownB4C60;

/* extern */
typedef struct S_800B2B60_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0x10];
    u32 unk_3C;
} S_800B2B60_0;

typedef struct S_800B2BA0_0_pre {
    s32 * unk_00;
    u8 pad_04[0xC];
} S_800B2BA0_0_pre;

typedef struct S_800B2BA0_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x3C];
    s32 unk_48;
} S_800B2BA0_0;

typedef struct S_800B2BA0_1 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_800B2BA0_1;

s32 func_800B0718();
void get_zero_based_group_index(struct TownB4C60 *);
/* extern */
void store_table_index_and_entry_bytes();
/* extern */
/* extern */
s32 func_800B3924();
/* extern */
s32 func_800B4588();
/* extern */
s32 func_800B4F60();
/* extern */
void handle_item_menu_input_2(u8 *menu);
extern void fill_item_value_buffer(void *);
extern void func_800B3A80(s32);
extern void refresh_object_components_and_high_flag(u8 *object);
extern void process_object_resources_and_high_flag(u8 *object);

s32 obj_disp23_cancel_sw_set(s32 cancel_switch);
void came_bright_set(u32 brightness);

/* Functions defined in this translation unit. */
void initialize_record_table_and_group(void *record);
s32 open_twin_souko(s32 option);
void apply_record_values_and_process_record(void *record);

#endif
