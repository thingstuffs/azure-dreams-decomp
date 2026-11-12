#include "common.h"
#include "town/devkit.h"
#include "town/devkit/shop_selection_data.h"

extern u8 devkit_globals_page[];

/* Return the table value indexed by the current signed byte entry. */
s32 shop_get_current_entry_value(void) {
    return *(s32 *)(devkit_globals_page +
                    (*(s8 *)(devkit_globals_page + devkit_shop_selection + 0x1F94) << 2) +
                    0x1F88);
}
