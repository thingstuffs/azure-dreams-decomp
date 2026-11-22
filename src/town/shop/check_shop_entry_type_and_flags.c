#include "common.h"
#include "town/shop.h"

/* Check whether the entry passes the type and flag filter. */
s32 check_shop_entry_type_and_flags(DungeonItemEntry *entry) {
    u8 flags;
    u8 value;

    value = entry->kind;
    if (value == 0x16) {
        return 0;
    }
    if (value == 0x19) {
        flags = entry->unk_03;
        if (flags & 8) {
            return 0;
        }
    }
    return 1;
}
