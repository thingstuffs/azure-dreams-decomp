#include "common.h"

#include "common.h"
#include "engine/script.h"

extern u8 runtime_script_state[];

/* Sets the list-present flag for runtime_script_state when its controller list is nonempty. */
void flag_script_list_nonempty(void) {
    set_flag_if_list_nonempty(&runtime_script_state);
}
