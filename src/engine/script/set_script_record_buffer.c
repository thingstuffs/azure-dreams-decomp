#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void runtime_set_record_value_and_buffer();              /* extern */
extern u8 D_80082A38[];

/* Passes the value and the shared object to runtime_set_record_value_and_buffer. */
void set_script_record_buffer(s32 value) {
    runtime_set_record_value_and_buffer(&D_80082A38, value);
}
