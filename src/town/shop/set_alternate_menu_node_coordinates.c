#include "common.h"
#include "town/menu.h"
#include "town/shop.h"


/* Calls func_800B47BC with the value increased by 0x20. */
void set_alternate_menu_node_coordinates(s32 value) {
    func_800B47BC(value + 0x20);
}
