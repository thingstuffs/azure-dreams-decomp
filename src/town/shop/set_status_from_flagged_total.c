#include "common.h"
#include "town/shop.h"
#include "town/system.h"

extern s32 script_status;

/* Store whether the record check returns a nonzero result. */
void set_status_from_flagged_total(void *record) {
    if (sum_flagged_entry_prices(*(u8 **)((u8 *)record + 0x20), *(s32 *)((u8 *)record + 0x18)) != 0) {
        script_status = 1;
        return;
    }
    script_status = 0;
}
