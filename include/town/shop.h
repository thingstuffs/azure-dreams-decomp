#ifndef TOWN_SHOP_H
#define TOWN_SHOP_H

#include "common.h"


/* get_player_homerank.c */
s32 get_player_homerank(void);

struct S_800AE56C_0;
void dispatch_item_menu_entry_callback(struct S_800AE56C_0 *state, s32 callback_arg);
void invoke_item_menu_offset_handler(u8 *object, s32 callback_arg);

#endif
