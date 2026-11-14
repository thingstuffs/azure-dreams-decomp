#include "common.h"
#include "engine/menu.h"
#include "town/shop/item.h"

extern s32 D_800D15B0;

/* Pass the data pointer and D_800D15B0 to func_80049D80. */
void init_item_menu_sub_record_pair(void *data) {
    init_packet_pair_and_gradient(data, &D_800D15B0);
}
