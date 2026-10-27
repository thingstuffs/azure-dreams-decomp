#ifndef TOWN_SHOP_STATE_H
#define TOWN_SHOP_STATE_H

#include "common.h"


struct S_800B6580_0;
/* set_monster_status_panel_height.c */
void set_monster_status_panel_height(struct S_800B6580_0 *object, s16 height);

s32 set_item_menu_flag_and_return_one(void *state, s32 unused_config);

s32 test_linked_flag(s32 flag_index);

#endif
