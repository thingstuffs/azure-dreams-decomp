#ifndef TOWN_SHOP_OBJECT_H
#define TOWN_SHOP_OBJECT_H
/* Prototypes of the functions defined in src/town/shop/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/item_menu.h"
#include "shared/object_node.h"

struct Copy4;
struct ItemMenuTransition;
struct Obj;
struct S_800B1718_0;
struct S_800B1730_0;
struct S_800B2CE8_0;

/* Body of the shop object that delegates its update to the first method. */
typedef struct ShopFirstCallbackObject {
    /* 0x00 */ s32 (*first_callback)(void *object);
    /* 0x04 */ u8 pad_04[0x90];
    /* 0x94 */ void *status_display_entries;
    /* 0x98 */ s32 resource_id;
} ShopFirstCallbackObject;

/* allocate_object_and_mark_failed_setup_for_cleanup.c */
void *allocate_object_and_mark_failed_setup_for_cleanup(s32 resource_id, s32 slot_index, s32 x, s32 y, s32 z);

/* create_item_menu_handler_object.c */
ItemMenuObjectNode *create_item_menu_handler_object(ItemMenuStateNode *owner);

/* initialize_four_slot_object_variant.c */
void initialize_four_slot_object_variant(struct Obj *object);

/* initialize_item_menu_object_slots.c */
void initialize_item_menu_object_slots(ItemMenuObject *object);

/* initialize_object_resources.c */
s32 func_800B4ED8(void *object, s32 resource_id);
s32 initialize_object_resources(void *object, s32 resource_id);

/* interpolate_paired_object_positions_and_shades.c */
void interpolate_paired_object_positions_and_shades(void **pair_state);

/* invoke_item_menu_node_callback.c */
void invoke_item_menu_node_callback(struct ItemMenuTransition *state);

/* invoke_object_first_callback.c */
void invoke_object_first_callback(ShopFirstCallbackObject *obj);

/* link_item_menu_object_entries.c */
ItemMenuPart *link_item_menu_object_entries(ItemMenuPart **parts);

/* lshop_g00008.c */
void clear_shop_object_and_link(u8 *object_ref);
void release_lshop_entry(s32 slotIndex);
void compact_lshop_entry_list(void);
void *find_unused_item_slot(void **slot_list);
void append_town_item(const struct Copy4 *input);

/* process_shop_object_data.c */
void process_shop_object_data(s32 object_addr);

/* set_object_data_pointer.c */
void set_object_data_pointer_2(ObjectNodeHeader *object);

/* set_object_data_pointer_if_present.c */
void set_object_data_pointer_if_present(struct S_800B2CE8_0 *object);

/* set_shop_object_data_if_present.c */
void set_shop_object_data_if_present(struct S_800B1718_0 *object);

/* set_shop_object_ready.c */
void set_shop_object_ready(struct S_800B1730_0 *object);

#endif
