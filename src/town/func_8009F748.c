#include "modules/town_town_windows.h"

/* Run both update routines on the shared state and clear the global flag. */
void update_shared_state_and_clear_flag(void) {
    void *state = D_80100900;

    init_and_publish_script_state(state);
    process_zero_terminated_entry_lists(state);
    D_801007F8[0] = 0;
}
