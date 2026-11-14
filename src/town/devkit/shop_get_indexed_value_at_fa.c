#include "common.h"
#include "town/devkit.h"
#include "town/devkit/shop_selection_data.h"

extern u8 devkit_globals_page[];

/* Return the value at 0x1FA8 selected by the current signed index at 0x1FB4. */
s32 get_shop_third_table_value(void) {
    return *(s32 *)(devkit_globals_page +
                    (*(s8 *)(devkit_globals_page + devkit_shop_selection + 0x1FB4) << 2) +
                    0x1FA8);
}
