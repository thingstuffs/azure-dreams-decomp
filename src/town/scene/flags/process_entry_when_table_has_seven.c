#include "common.h"
#include "town/scene/entry_requests.h"
#include "town/scene/flags.h"
#include "town.h"

extern void func_80016CD8(void);

/* If flag 7 is set, call func_80016CD8 first; then get_linked_record_value(target, value). */
void process_entry_when_table_has_seven(s32 target, s32 value) {
    if (town_pair_table_has_first(7) != 0) {
        func_80016CD8();
    }
    process_checked_entry(target, value);
}
