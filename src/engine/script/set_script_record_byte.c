#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/script.h"

void runtime_set_record_byte_three();              /* extern */
extern u8 runtime_script_state[];

/* Passes the value to runtime_set_record_byte_three with the shared state. */
void set_script_record_byte(s32 value) {
    runtime_set_record_byte_three(&runtime_script_state, value);
}
