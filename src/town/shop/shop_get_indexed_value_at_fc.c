#include "common.h"
#include "town/shop.h"
#include "town/devkit/shop_selection_data.h"

extern u8 devkit_globals_page[];

/* Return the value at 0x1FC0 selected by the current unsigned index at 0x1FC8. */
s32 shop_get_indexed_value_at_1_fc_0(void) {
    return *(s32 *)(devkit_globals_page +
                    (*(devkit_globals_page + devkit_shop_selection + 0x1FC8) << 2) +
                    0x1FC0);
}
