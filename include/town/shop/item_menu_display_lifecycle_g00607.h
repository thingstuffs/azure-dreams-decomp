#ifndef TOWN_SHOP_ITEM_MENU_DISPLAY_LIFECYCLE_G00607_H
#define TOWN_SHOP_ITEM_MENU_DISPLAY_LIFECYCLE_G00607_H
/* Item menu display lifecycle declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B2F64. */

#include "common.h"
#include "shared/object_node.h"
#include "shared/item_menu.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "town/shop/state.h"

typedef struct S_800B05DC_0 {
    u8 entry_ids[4];
    ObjectNodeHeader *child; /* 0x04 */
    ItemMenuStateNode *owner; /* 0x08 */
    void *init_config; /* 0x0C */
    u8 pad_10[0x4];
    s32 display_config; /* 0x14 */
    s32 init_result; /* 0x18 */
} S_800B05DC_0;

/* the 0x2 bytes before arg0 in release_item_menu_display, addressed as arg0[-1] */
typedef struct S_800B06C4_0 {
    u8 pad_00[0x4];
    ObjectNodeHeader *child; /* 0x04 */
} S_800B06C4_0;

void bzero(void *, s32);
/* extern */
ObjectNodeHeader *create_item_menu_child_at_position(ObjectNodeHeader *parent, s32 x, s32 y, s32 resource_id,
                                                  s32 resource_data, u8 *entry_ids);
/* extern */
extern M2C_UNK D_800B0490;
/* arg0 in release_item_menu_display */
void release_item_menu_list_object(ObjectNodeHeader *object);
/* extern */
extern struct { s32 v; s32 pad[2]; } object_flag_block;

/* Functions defined in this translation unit. */
ObjectNodeHeader *create_item_menu_display_controller(ItemMenuStateNode *owner, s32 display_config, s32 x, s32 y, void *init_config);
void release_item_menu_display(S_800B05DC_0 *record);

#endif
