#ifndef TOWN_SHOP_ITEM_MENU_DISPLAY_LIFECYCLE_G00607_H
#define TOWN_SHOP_ITEM_MENU_DISPLAY_LIFECYCLE_G00607_H
/* Item menu display lifecycle declarations (G00607). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B2F64. */

#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "shared/object_links.h"

typedef struct S_800B05DC_0 {
    u8 pad_00[0x4];
    s32 child; /* 0x04 */
    s32 owner; /* 0x08 */
    s32 init_config; /* 0x0C */
    u8 pad_10[0x4];
    s32 display_config; /* 0x14 */
    s32 init_result; /* 0x18 */
} S_800B05DC_0;

/* the 0x2 bytes before arg0 in finish_item_menu_child_and_release_list, addressed as arg0[-1] */
typedef struct S_800B06C4_0 {
    u8 pad_00[0x4];
    s32 child; /* 0x04 */
} S_800B06C4_0;

void bzero(void *, s32);
s32 set_item_menu_flag_and_return_one();
/* extern */
s32 create_item_menu_child_at_position();
/* extern */
extern M2C_UNK D_800B0490;
/* arg0 in finish_item_menu_child_and_release_list */
void release_item_menu_list_object(s32);
/* extern */
extern struct { s32 v; s32 pad[2]; } D_800814A0;

/* Functions defined in this translation unit. */
void *create_item_menu_display_controller(s32 owner, s32 display_config, s32 x, s32 y, s32 init_config);
void finish_item_menu_child_and_release_list(void *record);

#endif
