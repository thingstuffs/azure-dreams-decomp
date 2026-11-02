#include "common.h"
#include "engine/menu.h"
#include "town/shop/item.h"

extern s32 D_800D15B0;

/* Pass the data pointer and D_800D15B0 to func_80049D80. */
void dispatch_item_menu_data_update(void *data) {
    init_sub_record_pair(data, &D_800D15B0);
}
