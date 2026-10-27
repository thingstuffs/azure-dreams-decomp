#ifndef TOWN_SHOP_ITEM_MENU_ACTIONS_H
#define TOWN_SHOP_ITEM_MENU_ACTIONS_H

#include "common.h"
#include "shared/item_menu.h"

typedef struct ItemMenuInput {
    u8 pad_00[4];
    ObjectNodeHeader *object;
    ItemMenuStateNode *owner;
    s32 callback_arg;
    s32 repeat_ticks;
} ItemMenuInput;

void set_item_menu_data_pointer(ItemMenuStateNode *owner);
void set_item_menu_secondary_handler(ItemMenuStateNode *owner);
void release_item_menu_object(ItemMenuParameters *parameters);
void run_item_menu_record_handlers(void *record_payload);
/* Code-address alias installed by set_item_menu_secondary_handler. */
void D_800AE494(void *record_payload);

#endif
