#ifndef TOWN_SHOP_ITEM_MENU_OBJECT_LIFECYCLE_G00600_H
#define TOWN_SHOP_ITEM_MENU_OBJECT_LIFECYCLE_G00600_H
/* Item menu object lifecycle declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B0CB4. */

#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "shared/item_menu.h"
#include "town/shop/item_menu_actions.h"

typedef struct S_800AE324_0 {
    u8 pad_00[0x8];
    void *unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    void * unk_20;
    u8 pad_24[0x50];
    s32 unk_74;
} S_800AE324_0;

/* state in create_item_menu_object */
typedef struct S_800AE324_1 {
    u8 pad_00[0x20];
    ItemMenuObjectNode *unk_20;
} S_800AE324_1;

extern void *allocate_list_node(s32 flags, s32 list_head);
extern void set_message_mode(s32 value);
extern void runtime_call_selected_mode_handler(void);
extern s32 func_800B0718(void);
extern void *create_floating_number_widget(void *setup_value, s32 x, s32 y);
extern void release_item_menu_child_object(s32 object); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void schedule_item_menu_child_release(ObjectNodeHeader *object);
extern void set_advance_inner_value_callback(s32 object); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void enqueue_script_message_command(void);
extern void create_selected_town_object(void);

/* Functions defined in this translation unit. */
void * create_item_menu_object(s32 selector);

#endif
