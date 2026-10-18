#include "common.h"

extern u8 D_80700000[];
extern s32 D_80701DC8[3];

/* Return the table value indexed by the current signed byte entry. */
s32 shop_get_current_entry_value(void) {
    return *(s32 *)((u8 *)D_80700000 +
                    (*(s8 *)((u8 *)D_80700000 + D_80701DC8[0] + 0x1F94) << 2) +
                    0x1F88);
}
