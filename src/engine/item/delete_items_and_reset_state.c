#include "common.h"

#include "common.h"

void func_8003B7C8(void);
void delete_all_town_items(void);
void reset_entry_flags();                            /* extern */

/* Runs the three Konami runtime routines in sequence. */
void delete_items_and_reset_state(void) {
    reset_entry_flags();
    delete_all_town_items();
    func_8003B7C8();
}
