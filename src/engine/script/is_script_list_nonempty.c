#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/script.h"

extern u8 runtime_script_state[];

/* Passes the global state to is_list_nonempty. */
void is_script_list_nonempty(void) {
    is_list_nonempty(&runtime_script_state);
}
