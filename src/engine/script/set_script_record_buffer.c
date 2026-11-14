#include "common.h"
#include "m2c_compat.h"

#include "engine/object.h"
#include "engine/script.h"

extern u8 runtime_script_state[];

/* Passes the value and the shared object to set_script_text_pointer. */
void set_script_record_buffer(s32 value) {
    set_script_text_pointer(&runtime_script_state, value);
}
