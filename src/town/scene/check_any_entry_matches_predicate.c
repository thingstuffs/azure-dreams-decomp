#include "modules/town_ovl_3ef1c8.h"

s32 check_any_entry_matches_predicate(void) {
    u8 *entry = &D_8001A92C;

    if (D_8001A92C != 0) {
        do {
            if (town_table_contains_first_byte_b(*entry) != 0) {
                return 1;
            }
            entry++;
        } while (*entry != 0);
    }
    return 0;
}
