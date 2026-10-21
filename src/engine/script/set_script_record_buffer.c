#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/object.h"
#include "engine/script.h"

extern u8 runtime_script_state[];

/* Passes the value and the shared object to runtime_set_record_value_and_buffer. */
void set_script_record_buffer(s32 value) {
    runtime_set_record_value_and_buffer(&runtime_script_state, value);
}
