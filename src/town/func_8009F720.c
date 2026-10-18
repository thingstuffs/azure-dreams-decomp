#include "modules/town_town_windows.h"

/* Runs build_entry_list_and_process_items followed by run_dual_context_callbacks. */
void build_entries_and_update_state(void) {
    build_entry_list_and_process_items();
    run_dual_context_callbacks();
}
