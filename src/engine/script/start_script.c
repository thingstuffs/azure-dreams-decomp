#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/object.h"
#include "engine/script.h"

extern M2C_UNK runtime_script_state;

/* Start a script in the global runtime with mode 1. */
void start_script(s32 script_addr) {
    prepare_script_controller_and_set_cursor(&runtime_script_state, script_addr, 1);
}
