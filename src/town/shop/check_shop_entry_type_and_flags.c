#include "common.h"
#include "town/shop.h"

/* Check whether the entry passes the type and flag filter. */
s32 check_shop_entry_type_and_flags(void *entry) {
    u8 flags;
    u8 value;

    value = *((u8 *)entry + 1);
    if (value == 0x16) {
        return 0;
    }
    if (value == 0x19) {
        flags = *((u8 *)entry + 3);
        if (flags & 8) {
            return 0;
        }
    }
    return 1;
}
