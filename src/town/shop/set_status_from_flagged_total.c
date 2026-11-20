#include "common.h"
#include "engine/script.h"
#include "town/shop.h"
#include "town/system.h"
#include "engine/message/data.h"
#include "engine/message.h"

/* Store whether the record check returns a nonzero result. */
void set_status_from_flagged_total(void *record) {
    if (sum_flagged_entry_prices(*(u8 **)((u8 *)record + 0x20), *(s32 *)((u8 *)record + 0x18)) != 0) {
        runtime_script_state.variables[14] = 1;
        return;
    }
    runtime_script_state.variables[14] = 0;
}
