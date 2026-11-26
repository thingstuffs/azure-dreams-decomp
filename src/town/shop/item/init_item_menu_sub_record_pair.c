#include "common.h"
#include "engine/menu.h"
#include "town/shop/item.h"

extern const RECT D_800D15B0;

/* Initialize the packet pair using the shop rectangle. */
void init_item_menu_sub_record_pair(void *data) {
    init_packet_pair_and_gradient(data, &D_800D15B0);
}
