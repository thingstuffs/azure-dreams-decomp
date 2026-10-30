#ifndef TOWN_SHOP_RESOURCE_ENTRY_INITIALIZATION_G01156_H
#define TOWN_SHOP_RESOURCE_ENTRY_INITIALIZATION_G01156_H
/* resource entry initialization g01156. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01156 - CL:town/func_800B5204, CL:town/func_800B5270, CL:town/func_800B52D8, CL:town/func_800B5400, CL:town/func_800B550C. */

/* Resource entry initialization (G00617). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B5204. */
/* Resource entry initialization declarations (G00617). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B5204. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "shared/item_menu.h"
#include "town/shop/storage_menu.h"
#include "town/shop/item_menu_actions.h"

typedef struct S_800B2964_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800B2964_0;

/* extern */
struct TownB4C60;

/* extern */
typedef struct S_800B29D0_0 {
    u8 pad_00[0x38];
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
} S_800B29D0_0;

typedef struct {
    u32 value;
} __attribute__((packed)) UA32;

typedef struct {
    u8 pad[0x40];
    UA32 **items;
    s32 count;
} S_800B52D8;

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


typedef struct S_800B2BA0_1 {
    u8 pad_00[0x20];
    ItemMenuObjectNode *unk_20;
} S_800B2BA0_1;

typedef struct ItemMenuInputObject {
    ItemMenuObjectNode *item_menu_object;
    StorageMenuNode *source_menu;
    StorageMenuNode *destination_menu;
    u8 pad_0C[0x4];
    s32 input_repeat_ticks;
    u8 pad_14[0x34];
    s32 option;
} ItemMenuInputObject;

s32 create_callback_pair_default();
void get_zero_based_group_index(struct TownB4C60 *);
/* extern */
extern void flag_object_for_removal(unsigned short *object);
s32 func_800B0718(void);
/* extern */
/* extern */
/* extern */
/* extern */
/* extern */
void handle_item_menu_input_2(u8 *menu);
extern void func_800B3A80(s32);
extern void refresh_object_components_and_high_flag(u8 *object);
extern void process_object_resources_and_high_flag(u8 *object);
s32 obj_disp23_cancel_sw_set(s32 cancel_switch);
void came_bright_set(u32 brightness);

/* Functions defined in this translation unit. */
void collect_enabled_entry_pointers(s32 *entries, s32 entry_count);
s32 count_nonzero_entries(s32 *entries);
s32 acquire_resource_and_initialize_state(void *state);
void fill_item_value_buffer(S_800B52D8 *table);
void initialize_record_table_and_group(void *record);
void * open_twin_souko(s32 option);
void apply_record_values_and_process_record(void *record);

#endif
