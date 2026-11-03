#include "common.h"
#include "town/scene/entry_requests.h"
#include "town/scene/flags.h"
#include "town.h"

extern void func_80016CD8(void);

/* If flag 7 is set, call func_80016CD8 first; then get_helper_result(target, value). */
void run_value_handler_after_flag_check(s32 target, s32 value) {
    if (town_table_contains_first_byte_b(7) != 0) {
        func_80016CD8();
    }
    process_checked_entry(target, value);
}
