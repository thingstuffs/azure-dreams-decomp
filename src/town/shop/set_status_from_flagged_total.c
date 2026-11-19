#include "common.h"
#include "engine/script.h"
#include "town/shop.h"
#include "town/system.h"


/* Store whether the record check returns a nonzero result. */
void set_status_from_flagged_total(void *record) {
    if (sum_flagged_entry_prices(*(u8 **)((u8 *)record + 0x20), *(s32 *)((u8 *)record + 0x18)) != 0) {
        script_status[0] = 1;
        return;
    }
    script_status[0] = 0;
}
