#include "common.h"

extern s32 sum_flagged_entry_values(u8 *entry, s32 mode);
extern s32 script_status;

/* Store whether the record check returns a nonzero result. */
void store_record_check_result(void *record) {
    if (sum_flagged_entry_values(*(s32 *)((u8 *)record + 0x20), *(s32 *)((u8 *)record + 0x18)) != 0) {
        script_status = 1;
        return;
    }
    script_status = 0;
}
