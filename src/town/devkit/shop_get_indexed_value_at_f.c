#include "common.h"
#include "town/devkit.h"
#include "town/devkit/shop_selection_data.h"

extern u8 devkit_globals_page[];

/* Return the value at 0x1F98 selected by the current signed index at 0x1FA4. */
s32 get_shop_second_table_value(void) {
    return *(s32 *)(devkit_globals_page +
                    (*(s8 *)(devkit_globals_page + devkit_shop_selection + 0x1FA4) << 2) +
                    0x1F98);
}
