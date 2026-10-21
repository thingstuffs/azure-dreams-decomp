#include "common.h"

#include "common.h"
#include "engine/script.h"

extern u8 runtime_script_state[];

/* Passes the global object D_80082A38 to set_flag_if_list_nonempty. */
void flag_script_list_nonempty(void) {
    set_flag_if_list_nonempty(&runtime_script_state);
}
